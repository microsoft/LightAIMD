/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <math.h>
#include "constants.h"
#include "functional.h"

/*
 * Implementaiton of two simple functionals: functional_lda_x and functional_lda_c_vwn,
 * which should be equivalent to the following two libxc functionals (the XC_UNPOLARIZED case):
 * LDA_X (id=1) and LDA_C_VWN (id=7)
 */

#define XC_TOLERANCE_THRESHOLD 1e-10

/*
 *    (-9.0 / 4.0) * alpha * pow(3 / ( M_PI * 4.0), 1.0/3.0) * pow(1.0/2.0, 1.0/3.0)
 *  = (-9.0 / 4.0) * (2.0 / 3.0) * pow(3.0 / ( M_PI * 8.0), 1.0/3.0)
 */
#define LDA_X_EXC_PREFACTOR -7.3855876638202245e-01

/*
 *  = 4.0 / 3.0 * LDA_X_EXC_PREFACTOR
 */
#define LDA_X_VRHO_PREFACTOR -9.8474502184269663e-01

/*
 * E_{xc} = integrate[ f[rho(x,y,z)] dxdydz]
 * f[rho(x,y,z)] = rho exc(rho) = rho c rho^{1/3} = c rho^{4/3}
 * Note: we will multiply rho to exc in build_xc_matrix_with_grid(...)
 * vrho = df/drho = (4.0 / 3.0) c rho^{1/3}
 * c = LDA_X_EXC_PREFACTOR
 */
void functional_lda_x(f64 const *rho, f64 *exc, f64 *vrho, u64 num_grid_points)
{
    for (u64 i = 0; i < num_grid_points; ++i)
    {
        if (rho[i] < XC_TOLERANCE_THRESHOLD)
        {
            exc[i] = 0.0;
            vrho[i] = 0.0;
        }
        else
        {
            f64 rho_1_3rd = pow(rho[i], ONE_THIRD);
            exc[i] = LDA_X_EXC_PREFACTOR * rho_1_3rd;
            vrho[i] = LDA_X_VRHO_PREFACTOR * rho_1_3rd;
        }
    }
}

void functional_lda_c_vwn(f64 const *rho, f64 *exc, f64 *vrho, u64 num_grid_points)
{
    for (u64 i = 0; i < num_grid_points; i++)
    {
        if (rho[i] < XC_TOLERANCE_THRESHOLD)
        {
            exc[i] = 0.0;
            vrho[i] = 0.0;
        }
        else
        {
            f64 x = pow(3.0 / 4.0 / M_PI / rho[i], 1.0 / 6.0);

            f64 a = 0.0310907;
            f64 x0 = -0.10498;
            f64 b = 3.72744;
            f64 c = 12.9352;

            f64 c4_bb = c * 4.0 - b * b;
            f64 c4_bb_sqrt = sqrt(c4_bb);
            f64 x_sq = x * x;
            f64 x_b_c = x_sq + b * x + c;
            f64 x0_b_c = x0 * x0 + b * x0 + c;
            exc[i] = a * (log(x_sq / x_b_c) -
                     b * (x0 / x0_b_c) * log(pow(x - x0, 2.0) / x_b_c) +
                     (2.0 * b / c4_bb_sqrt) * (1.0 - (x0 * (2.0 * x0 + b) / x0_b_c)) * atan(c4_bb_sqrt / (2.0 * x + b)));

            f64 x2_b = x * 2.0 + b;
            f64 x2_b_sq = x2_b * x2_b;
            f64 x2_b_sq_c4_bb = x2_b_sq + c4_bb;
            vrho[i] = exc[i] - (x / 6.0) * a *
                      (2.0 / x -
                      x2_b / x_b_c -
                      4.0 * b / x2_b_sq_c4_bb -
                      (b * x0 / x0_b_c) * (2.0 / (x - x0) - x2_b / x_b_c - 4.0 * (2.0 * x0 + b) / x2_b_sq_c4_bb));
        }
    }
}

#ifdef MODULE_TEST
int main(void)
{
    return 0;
}
#endif
