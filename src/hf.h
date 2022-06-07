/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef HF_H
#define HF_H
#include "numeric_types.h"
#include "scf.h"
#include "md.h"

void hf_scf_config(struct scf_context *ctx);
void hf_single_point_energy(struct cmd_line_args *args);
void hf_single_point_forces(struct cmd_line_args *args);
void hf_calc_forces_on_nuclei(struct cmd_line_args *args, struct md_context *md_ctx);

#endif
