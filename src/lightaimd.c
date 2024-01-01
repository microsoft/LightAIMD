/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */

#include "scf.h"
#include "time_util.h"
#include "cli_args.h"
#include "hf.h"
#include "dft.h"
#include "md.h"
#include "mm.h"
#include "diagnostics.h"
#include "cuda_helper.h"

void scf_config_hf(struct scf_context* ctx)
{
    ctx->JK_screening_threshold = 1e-8;
    ctx->converge_threshold = 1e-12;
    ctx->n_max_iteration = 100;
    ctx->direct_scf = 1;
    ctx->density_init_method = DENSITY_INIT_SOAD;
}

void scf_config_dft(struct scf_context* ctx)
{
    ctx->JK_screening_threshold = 1e-8;
    ctx->converge_threshold = 1e-12;
    ctx->n_max_iteration = 1000;
    ctx->direct_scf = 1;
    ctx->density_init_method = DENSITY_INIT_HCORE;
}

int main(int argc, char* argv[])
{
#ifdef USE_CUDA
    cuda_configure();
#endif

    struct timespec time_start, time_end;
    get_wall_time(&time_start);

    struct cmd_line_args args;
    cli_parse_args(argc, argv, &args);

    if (!args.silent)
    {
        print_molecule(args.mol);
    }

    if (args.job_type == JOB_TYPE_SPE)
    {
        if (args.cc_method == CC_METHOD_HF)
        {
            hf_single_point_energy(&args);
        }

        if (args.cc_method == CC_METHOD_DFT)
        {
            dft_single_point_energy(&args);
        }
    }
    if (args.job_type == JOB_TYPE_SPF)
    {
        if (args.cc_method == CC_METHOD_HF)
        {
            hf_single_point_forces(&args);
        }

        if (args.cc_method == CC_METHOD_DFT)
        {
            dft_single_point_forces(&args);
        }
    }
    if (args.job_type == JOB_TYPE_BOMD)
    {
        if (args.cc_method == CC_METHOD_HF)
        {
            struct scf_context* ctx = scf_initialize(&args, hf_scf_config);
            u64 n_basis_funcs = ctx->n_basis_funcs;
            scf_finalize(ctx);

            struct md_context* md_ctx = md_initialize(&args, hf_calc_forces_on_nuclei, n_basis_funcs, "hf");
            md_simulate(&args, md_ctx);
            md_finalize(md_ctx);
        }

        if (args.cc_method == CC_METHOD_DFT)
        {
            struct scf_context* ctx = scf_initialize(&args, dft_scf_config);
            u64 n_basis_funcs = ctx->n_basis_funcs;
            scf_finalize(ctx);

            struct md_context* md_ctx = md_initialize(&args, dft_calc_forces_on_nuclei, n_basis_funcs, "dft");
            md_simulate(&args, md_ctx);
            md_finalize(md_ctx);
        }
    }

    free_molecule(args.mol);

    get_wall_time(&time_end);
    console_printf(0, "The whole program took %.3f ms\n", diff_time_ms(&time_start, &time_end));

    if (!args.silent)
    {
        print_mm_status();
    }

    return 0;
}
