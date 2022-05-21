/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef DFT_H
#define DFT_H
#include "numeric_types.h"
#include "scf.h"

struct dft_context
{
    struct scf_context *scf_ctx;
    struct molecular_grid_desc *mgd;
    f64 total_energy;
};

struct dft_context *dft_initialize(struct scf_context *scf_ctx, struct cmd_line_args *args);
void dft_total_energy(struct dft_context *ctx);
void dft_finalize(struct dft_context *ctx);

#endif
