/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef MOLECULAR_GRID_H
#define MOLECULAR_GRID_H
#include "numeric_types.h"

/* atomic grid descriptor */
struct atomic_grid_desc
{
    struct vec3d nucleus_coord;
    u64 grid_size;
    u64 num_radial_points;
    u64 num_angular_points;
    f64 bragg_slater_radius;

    struct molecular_grid_desc *mgd;
};

struct molecular_grid_desc
{
    struct atomic_grid_desc *atomic_grid_descs;
    u64 num_angular_points;
    u64 num_radial_points;

    u64 radial_grid_level;
    u64 lebedev_level;

    f64 *lebedev_grid;
    f64 *lebedev_weights;

    u64 grid_size; /* the total number of grid points */

    struct vec3d *global_coords;
    struct vec3d *local_coords;

    /* weight for each grid point */
    f64 *weights;
    /* becke_weight for each grid point */
    f64 *becke_weights;

    /* there are scf_ctx->n_basis_func bf_values for each grid point */
    f64 *bf_values;
    f64 *bf_derivative_x;
    f64 *bf_derivative_y;
    f64 *bf_derivative_z;
    f64 *bf_laplacian;

    f64 *bf_derivative_xx;
    f64 *bf_derivative_yy;
    f64 *bf_derivative_zz;
    f64 *bf_derivative_xy;
    f64 *bf_derivative_xz;
    f64 *bf_derivative_yz;

    f64 *V;
    f64 *V_fuzzy_cell;

    f64 *J;
    f64 *K;

    f64 hf_exchange_energy;
    f64 xc_energy;
    f64 hyb_coef;

    f64 *XC;    /* two-electron exchange-correlation matrix */
    f64 *VXC_x; /* grid_size X n_basis_func */
    f64 *VXC_y; /* grid_size X n_basis_func */
    f64 *VXC_z; /* grid_size X n_basis_func */
    u64 xc_type;

    /* density for each grid point */
    f64 *densities;
    f64 *density_derivative_x;
    f64 *density_derivative_y;
    f64 *density_derivative_z;

    /* memory buffers for calling xc functionals */
    f64 *densities_sigma;
    f64 *lapl;
    f64 *tau;

    f64 *exc_x;
    f64 *vrho_x;
    f64 *vsigma_x;
    f64 *vlapl_x;
    f64 *vtau_x;

    f64 *exc_c;
    f64 *vrho_c;
    f64 *vsigma_c;
    f64 *vlapl_c;
    f64 *vtau_c;

    /* buffers for calculating the derivatives of E_xc with respect to nuclear coordinates */
    f64 *d_sigma_x;
    f64 *d_sigma_y;
    f64 *d_sigma_z;

    f64 *d_lapl_x;
    f64 *d_lapl_y;
    f64 *d_lapl_z;

    f64 *d_tau_x;
    f64 *d_tau_y;
    f64 *d_tau_z;

    /* temp runtime buffers for calling xc functionals */
    f64 *bf_v;
    f64 *weighted_vrho;
    f64 *weighted_vsigma_rho_dx;
    f64 *weighted_vsigma_rho_dy;
    f64 *weighted_vsigma_rho_dz;

    f64 *bf_v_dx;
    f64 *bf_v_dy;
    f64 *bf_v_dz;

    u64 x_functional_id;
    u64 c_functional_id;

    /* temp runtime buffers */
    f64 *NxN; // n_basis_func X n_basis_func
    f64 *MxN;
    f64 *MxN_2; // grid_size X n_basis_func
    f64 *Mx1;

    struct scf_context *scf_ctx;
};

void calc_bfvalues_derivatives(struct molecular_grid_desc *mgd);
void calc_rho_sigma_lapl_tau(struct molecular_grid_desc *mgd);
void build_molecular_grid(struct molecular_grid_desc *mgd);
f64 cal_rho_sum_with_grid(struct molecular_grid_desc *mgd);

#endif
