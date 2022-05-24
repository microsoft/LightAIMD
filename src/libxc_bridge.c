/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "libxc_bridge.h"
#include "diagnostics.h"
#include "mm.h"

const u64 XC_TYPE_LDA = 1;
const u64 XC_TYPE_GGA = 3;
const u64 XC_TYPE_MGGA = 7;

struct libxc_registry
{
    u64 func_count;
    xc_func_type *funcs;
    f64 *hybrid_coeffs;
    u64 *xc_types;
    u64 *funcs_initialized; /* each number (0/1) is a flag indicating whether the current funcs slot is initialized */
};

static struct libxc_registry registry;

void print_xc_dimensions(xc_func_type *func)
{
    xc_dimensions *dim = &(func->dim);
    printf("rho: %d  ", dim->rho);
    printf("sigma: %d  ", dim->sigma);
    printf("lapl: %d  ", dim->lapl);
    printf("tau: %d\n", dim->tau);

    printf("zk: %d  ", dim->zk);
    printf("vrho: %d  ", dim->vrho);
    printf("vsigma: %d  ", dim->vsigma);
    printf("vlapl: %d  ", dim->vlapl);
    printf("vtau: %d\n", dim->vtau);
}

void libxc_initialize(i32 *func_ids, i32 *is_polarized, u64 func_count)
{
    i32 max_func_id = -1;
    for (u64 i = 0; i < func_count; ++i)
    {
        if (func_ids[i] > max_func_id)
        {
            max_func_id = func_ids[i];
        }
    }

    registry.func_count = max_func_id + 1;
    registry.funcs = x_malloc(registry.func_count * sizeof(xc_func_type));
    registry.hybrid_coeffs = x_calloc(registry.func_count, sizeof(f64));
    registry.xc_types = x_calloc(registry.func_count, sizeof(u64));
    registry.funcs_initialized = x_calloc(registry.func_count, sizeof(u64));

    for (u64 i = 0; i < func_count; ++i)
    {
        i32 func_id = func_ids[i];
        if (func_id == 0)
        {
            continue;
        }

        i32 nspin = XC_UNPOLARIZED;
        if (is_polarized[i])
        {
            nspin = XC_POLARIZED;
        }

        registry.funcs_initialized[func_id] = 0;

        xc_func_type *func = registry.funcs + func_id;
        /* 0 (OK) or -1 (ERROR) */
        if (xc_func_init(func, func_id, nspin))
        {
            fprintf(stderr, "Initializing %ld failed.\n", func_id);
            continue;
        }
        registry.hybrid_coeffs[func_id] = xc_hyb_exx_coef(func);
        switch (func->info->family)
        {
        case XC_FAMILY_LDA:
        case XC_FAMILY_HYB_LDA:
            registry.xc_types[func_id] = XC_TYPE_LDA;
            break;
        case XC_FAMILY_GGA:
        case XC_FAMILY_HYB_GGA:
            registry.xc_types[func_id] = XC_TYPE_GGA;
            break;
        case XC_FAMILY_MGGA:
        case XC_FAMILY_HYB_MGGA:
            registry.xc_types[func_id] = XC_TYPE_MGGA;
            break;
        default:
            fprintf(stderr, "Functional %ld: functional family is not recognized.\n", func_id);
        }
        console_printf(1, "Functional %d %s has been initialized.\n", func->info->number, func->info->name);
        registry.funcs_initialized[func_id] = 1;
        // print_xc_dimensions(func);
    }
}

void libxc_finalize()
{
    for (u64 i = 0; i < registry.func_count; ++i)
    {
        if (registry.funcs_initialized[i])
        {
            xc_func_end(registry.funcs + i);
        }
    }
    x_free(registry.funcs);
    x_free(registry.hybrid_coeffs);
    x_free(registry.xc_types);
    x_free(registry.funcs_initialized);
}

f64 libxc_hyb_coef(u64 func_id)
{
    return registry.hybrid_coeffs[func_id];
}

u64 get_xc_type(u64 x_functional_id, u64 c_functional_id)
{
    return registry.xc_types[x_functional_id] | registry.xc_types[c_functional_id];
}

/*
 *  func_id: functional id
 *  num_points: number of points
 *  rho: the density
 *  sigma: contracted gradients of the density
 *
 *  exc: the energy per unit particle
 *  vrho: first derivative of the energy per unit volume
 */
void libxc_exc_vxc(u64 func_id, u64 num_points, f64 const *rho, f64 const *sigma, f64 const *lapl, f64 const *tau,
                   f64 *exc, f64 *vrho, f64 *vsigma, f64 *vlapl, f64 *vtau)
{
    xc_func_type *func = registry.funcs + func_id;
    switch (func->info->family)
    {
    case XC_FAMILY_LDA:
    case XC_FAMILY_HYB_LDA:
        xc_lda_exc_vxc(func, num_points, rho, exc, vrho);
        break;
    case XC_FAMILY_GGA:
    case XC_FAMILY_HYB_GGA:
        xc_gga_exc_vxc(func, num_points, rho, sigma, exc, vrho, vsigma);
        break;
    case XC_FAMILY_MGGA:
    case XC_FAMILY_HYB_MGGA:
        xc_mgga_exc_vxc(func, num_points, rho, sigma, lapl, tau,
                        exc, vrho, vsigma, vlapl, vtau);
        break;
    default:
        fprintf(stderr, "Failed to evaluate functional %ld.\n", func_id);
    }
}

#ifdef MODULE_TEST
int main(void)
{
    printf("-----------------------------------------------------------\n");
    printf("Libxc has %d available functionals.\n", xc_number_of_functionals());
    printf("-----------------------------------------------------------\n");

    i32 func_ids[2] = {1, 7};
    i32 is_polarized[2] = {0, 0};
    libxc_initialize(func_ids, is_polarized, 2);

    f64 rho[5] = {0.1, 0.2, 0.3, 0.4, 0.5};
    f64 sigma[5] = {0.2, 0.3, 0.4, 0.5, 0.6};
    f64 exc[5] = {0};
    f64 vrho[5] = {0};
    f64 vsigma[5] = {0};

    /* input */
    f64 *lapl = NULL;
    f64 *tau = NULL;

    /* output */
    f64 *vlapl = NULL;
    f64 *vtau = NULL;

    /*
     * If the functional was initialized with nspin=XC_UNPOLARIZED,
     * all the input arrays are of size np (number of points).
     */
    libxc_exc_vxc(1, 5, rho, sigma, lapl, tau,
                  exc, vrho, vsigma, vlapl, vtau);
    for (u64 i = 0; i < 5; i += 1)
    {
        printf("%.6e %.6e %.6e %.6e %.6e\n", rho[i], sigma[i], exc[i], vrho[i], vsigma[i]);
    }

    printf("------------------------------------\n");

    libxc_exc_vxc(7, 5, rho, sigma, lapl, tau,
                  exc, vrho, vsigma, vlapl, vtau);
    for (u64 i = 0; i < 5; i += 1)
    {
        printf("%.6e %.6e %.6e %.6e %.6e\n", rho[i], sigma[i], exc[i], vrho[i], vsigma[i]);
    }

    libxc_finalize();
}
#endif
