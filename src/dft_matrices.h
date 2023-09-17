/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef DFT_MATRICES_H
#define DFT_MATRICES_H
#include "vec3d.h"
#include "molecule.h"
#include "scf.h"
#include "molecular_grid.h"

void build_J_matrix(struct molecular_grid_desc *mgd);
void build_K_matrix(struct molecular_grid_desc *mgd);
void build_JK_matrices(struct molecular_grid_desc *mgd);
void build_JK_matrices_cuda(struct molecular_grid_desc *mgd);
void build_xc_matrix_with_grid(struct molecular_grid_desc *mgd);
void calc_xc_gradients(struct molecular_grid_desc *mgd);

#ifdef USE_CUDA
#ifdef __cplusplus
extern "C"
{
#endif

    void cg_electron_repulsion_integral_cuda(struct basis_func *basis_func_buff, u32 *basis_func_index_buff, u64 count, f64 *result);

#ifdef __cplusplus
}
#endif
#endif

#endif
