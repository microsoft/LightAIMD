/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>

#include "numeric_types.h"
#include "constants.h"
#include "cmd_line_args.h"
#include "mm.h"
#include "io.h"
#include "md.h"
#include "velocity_init.h"
#include "thermostat.h"

void scf_config_md(struct scf_context* ctx)
{
    ctx->JK_screening_threshold = 1e-8;
    ctx->converge_threshold = 1e-12;
    ctx->n_max_iteration = 100;
    ctx->direct_scf = 1;
    ctx->density_init_method = DENSITY_INIT_USER_PROVIDED;
}

struct md_context* md_initialize(struct cmd_line_args* args, force_calculation_func_pointer calc_forces_on_nuclei, u64 n_basis_funcs, char const* job_name)
{
    struct md_context* md_ctx = x_malloc(sizeof(struct md_context));
    md_ctx->delta_t_fs = args->md_delta_t_fs;
    md_ctx->temperature_K = args->md_temperature_K;
    md_ctx->thermostat_time_smoothing_factor = args->md_thermostat_time_smoothing_factor;
    md_ctx->calc_forces_func = calc_forces_on_nuclei;
    md_ctx->job_name = job_name;
    md_ctx->step = 0;

    md_ctx->density_matrix = x_malloc(n_basis_funcs * n_basis_funcs * sizeof(f64));

    return md_ctx;
}

void md_finalize(struct md_context* md_ctx)
{
    x_free(md_ctx->density_matrix);
    x_free(md_ctx);
}

void md_simulate(struct cmd_line_args* args, struct md_context* md_ctx)
{
    f64 delta_t = md_ctx->delta_t_fs * TIME_FS_TO_ATOMIC_UNIT;

    struct molecule* mol = args->mol;
    maxwell_boltzmann_velocity_init(mol, md_ctx->temperature_K);
    enforce_temperature(mol, md_ctx->temperature_K);

    ensure_dir_exists("output");
    const u64 bufsz = 256;
    char sbuf[bufsz];
    snprintf(sbuf, bufsz, "output/%s_%s_trajectory.xyz", args->mol->name, md_ctx->job_name);
    FILE* fp_traj = fopen(sbuf, "wb");
    snprintf(sbuf, bufsz, "output/%s_%s_force.xyz", args->mol->name, md_ctx->job_name);
    FILE* fp_force = fopen(sbuf, "wb");
    snprintf(sbuf, bufsz, "output/%s_%s_velocity.xyz", args->mol->name, md_ctx->job_name);
    FILE* fp_velocity = fopen(sbuf, "wb");

    for (u64 i = 0; i < args->md_steps; ++i)
    {
        md_ctx->step = i;
        printf("MD step %lu\n", i);

        md_ctx->calc_forces_func(args, md_ctx);

        if (i > 0)
        {
            for (u64 j = 0; j < mol->n_atoms; ++j)
            {
                mol->velocities[j].x += 0.5 * delta_t * (mol->forces_last[j].x + mol->forces[j].x) / mol->masses[j];
                mol->velocities[j].y += 0.5 * delta_t * (mol->forces_last[j].y + mol->forces[j].y) / mol->masses[j];
                mol->velocities[j].z += 0.5 * delta_t * (mol->forces_last[j].z + mol->forces[j].z) / mol->masses[j];
            }
        }

        thermostat_berendsen_nvt(mol, md_ctx->temperature_K, 1e-3);

        write_trajectory(fp_traj, mol, i);
        fflush(fp_traj);
        write_velocities(fp_velocity, mol, i);
        fflush(fp_velocity);
        write_forces(fp_force, mol, i);
        fflush(fp_force);

        for (u64 j = 0; j < mol->n_atoms; ++j)
        {
            mol->coords[j].x += delta_t * mol->velocities[j].x + 0.5 * delta_t * delta_t * mol->forces[j].x / mol->masses[j];
            mol->coords[j].y += delta_t * mol->velocities[j].y + 0.5 * delta_t * delta_t * mol->forces[j].y / mol->masses[j];
            mol->coords[j].z += delta_t * mol->velocities[j].z + 0.5 * delta_t * delta_t * mol->forces[j].z / mol->masses[j];
            mol->forces_last[j].x = mol->forces[j].x;
            mol->forces_last[j].y = mol->forces[j].y;
            mol->forces_last[j].z = mol->forces[j].z;
        }
    }

    fclose(fp_traj);
    fclose(fp_force);
    fclose(fp_velocity);
}
