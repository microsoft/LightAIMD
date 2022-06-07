/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef DFT_H
#define DFT_H
#include "numeric_types.h"
#include "scf.h"
#include "md.h"

struct dft_context
{
    struct scf_context *scf_ctx;
    struct molecular_grid_desc *mgd;
    f64 total_energy;
};

struct dft_context *dft_initialize(struct scf_context *scf_ctx, struct cmd_line_args *args);
void dft_total_energy(struct dft_context *ctx);
void dft_finalize(struct dft_context *ctx);

void dft_scf_config(struct scf_context *ctx);
void dft_single_point_energy(struct cmd_line_args *args);
void dft_single_point_forces(struct cmd_line_args *args);
void dft_calc_forces_on_nuclei(struct cmd_line_args *args, struct md_context *md_ctx);

#endif
