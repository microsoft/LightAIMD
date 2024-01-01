/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef MD_H
#define MD_H
#include "numeric_types.h"
#include "cli_args.h"
#include "scf.h"

struct md_context;
typedef void (*force_calculation_func_pointer)(struct cmd_line_args*, struct md_context*);

struct md_context
{
    f64 delta_t_fs;
    f64 temperature_K;
    f64 thermostat_time_smoothing_factor;
    force_calculation_func_pointer calc_forces_func;
    f64* density_matrix;
    char const* job_name;

    u64 step;
};

void scf_config_md(struct scf_context* ctx);
struct md_context* md_initialize(struct cmd_line_args* args, force_calculation_func_pointer calc_forces_on_nuclei, u64 n_basis_funcs, char const* job_name);
void md_simulate(struct cmd_line_args* args, struct md_context* md_ctx);
void md_finalize(struct md_context* ctx);

#endif
