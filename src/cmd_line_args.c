/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdlib.h>
#include <string.h>
#include "cmd_line_args.h"
#include "sample.h"
#include "mm.h"

u64 const JOB_TYPE_SPE = 1;  // Single Point Energy
u64 const JOB_TYPE_SPF = 2;  // Single Point Forces
u64 const JOB_TYPE_BOMD = 3; // Born-Oppenheimer Molecular Dynamics

u64 const CC_METHOD_HF = 1;  // Hartree Fock
u64 const CC_METHOD_DFT = 2; // Density Functional Theory

u64 const GRID_SCHEME_FULL = 1;
u64 const GRID_SCHEME_SG2 = 2;
u64 const GRID_SCHEME_SG3 = 3;

char* get_arg_value_by_key(int argc, char* argv[], char const* key)
{
    /* no command-line arguments are provided */
    if (argc < 2)
    {
        return NULL;
    }

    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], key))
        {
            if (i + 1 < argc)
            {
                return argv[i + 1];
            }
        }
    }
    return NULL;
}

u64 check_flag(int argc, char* argv[], char const* key)
{
    if (argc < 2)
    {
        return 0;
    }

    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], key))
        {
            return 1;
        }
    }
    return 0;
}

void parse_cmd_line_args(int argc, char* argv[], struct cmd_line_args* args)
{
    char* xyz_file;
    struct molecule* mol;

    char* mol_value = get_arg_value_by_key(argc, argv, "--mol");
    if (mol_value)
    {
        xyz_file = mol_value;
        mol = x_malloc(sizeof(struct molecule));
        read_xyz(xyz_file, mol);
    }
    else
    {
        mol = sample_molecule_h2o();
    }
    args->mol = mol;

    char* basis_set_value = get_arg_value_by_key(argc, argv, "--basis-set");
    if (basis_set_value)
    {
        args->basis_set = basis_set_value;
    }
    else
    {
        args->basis_set = "basis-set/sto-3g.json";
    }

    char* cc_method_value = get_arg_value_by_key(argc, argv, "--cc-method");
    if (cc_method_value)
    {
        if (!strcmp(cc_method_value, "hf"))
        {
            args->cc_method = CC_METHOD_HF;
        }

        if (!strcmp(cc_method_value, "dft"))
        {
            args->cc_method = CC_METHOD_DFT;
        }
    }
    else
    {
        args->cc_method = CC_METHOD_DFT;
    }

    if (check_flag(argc, argv, "--hf"))
    {
        args->cc_method = CC_METHOD_HF;
    }

    if (check_flag(argc, argv, "--dft"))
    {
        args->cc_method = CC_METHOD_DFT;
    }

    args->damping = check_flag(argc, argv, "--damping");

    char* diis_subspace_size_value = get_arg_value_by_key(argc, argv, "--diis-subspace-size");
    if (diis_subspace_size_value)
    {
        args->diis_subspace_size = strtoull(diis_subspace_size_value, NULL, 10);
    }
    else
    {
        args->diis_subspace_size = 6;
    }

    /*
     * The accepted formats:
     * xid,cid
     * xcid
     */
    args->x_functional_id = 0;
    args->c_functional_id = 0;
    char* xc_functional_value = get_arg_value_by_key(argc, argv, "--xc-functional");
    if (xc_functional_value)
    {
        char* p = xc_functional_value;
        char* str_end;
        args->x_functional_id = strtoull(p, &str_end, 10);

        if (str_end - p < strlen(p))
        {
            args->c_functional_id = strtoull(str_end + 1, NULL, 10);
        }
    }
    else
    {
        args->x_functional_id = 450;
        args->c_functional_id = 236;
    }

    args->silent = check_flag(argc, argv, "--silent");

    args->job_type = JOB_TYPE_SPE; // the default job type
    if (check_flag(argc, argv, "--bomd"))
    {
        args->job_type = JOB_TYPE_BOMD;
    }
    if (check_flag(argc, argv, "--spf"))
    {
        args->job_type = JOB_TYPE_SPF;
    }

    char* radial_grid_level_value = get_arg_value_by_key(argc, argv, "--radial-grid-level");
    if (radial_grid_level_value)
    {
        args->radial_grid_level = strtoull(radial_grid_level_value, NULL, 10);
    }
    else
    {
        args->radial_grid_level = 3;
    }

    char* lebedev_level_value = get_arg_value_by_key(argc, argv, "--lebedev-level");
    if (lebedev_level_value)
    {
        args->lebedev_level = strtoull(lebedev_level_value, NULL, 10);
    }
    else
    {
        args->lebedev_level = 13;
    }

    char* md_steps_value = get_arg_value_by_key(argc, argv, "--md-steps");
    if (md_steps_value)
    {
        args->md_steps = strtoull(md_steps_value, NULL, 10);
    }
    else
    {
        args->md_steps = 100;
    }

    char* md_delta_t_fs_value = get_arg_value_by_key(argc, argv, "--md-delta-t");
    if (md_delta_t_fs_value)
    {
        args->md_delta_t_fs = strtod(md_delta_t_fs_value, NULL);
    }
    else
    {
        args->md_delta_t_fs = 1.0;
    }

    char* md_temperature_K_value = get_arg_value_by_key(argc, argv, "--md-temperature");
    if (md_temperature_K_value)
    {
        args->md_temperature_K = strtod(md_temperature_K_value, NULL);
    }
    else
    {
        args->md_temperature_K = 300.0;
    }

    char* md_thermostat_time_smoothing_factor_value = get_arg_value_by_key(argc, argv, "--md-thermostat-time-smoothing-factor");
    if (md_thermostat_time_smoothing_factor_value)
    {
        args->md_thermostat_time_smoothing_factor = strtod(md_thermostat_time_smoothing_factor_value, NULL);
    }
    else
    {
        args->md_thermostat_time_smoothing_factor = 1e-3;
    }

    char* check_results_cc_method_id = get_arg_value_by_key(argc, argv, "--check-results");
    if (check_results_cc_method_id)
    {
        args->check_results = strtoull(check_results_cc_method_id, NULL, 10);
    }
    else
    {
        args->check_results = 0;
    }

    args->grid_scheme = GRID_SCHEME_SG2;
}

#ifdef MODULE_TEST
#include <stdio.h>

int main(int argc, char* argv[])
{
    struct cmd_line_args args;
    parse_cmd_line_args(argc, argv, &args);

    printf("job_type: %lu\n", args.job_type);
    printf("basis_set: %s\n", args.basis_set);
    printf("cc_method: %lu\n", args.cc_method);

    // SCF
    printf("damping: %lu\n", args.damping);
    printf("diis_subspace_size: %lu\n", args.diis_subspace_size);

    // DFT
    printf("x_functional_id: %lu\n", args.x_functional_id);
    printf("c_functional_id: %lu\n", args.c_functional_id);
    printf("radial_grid_level: %lu\n", args.radial_grid_level);
    printf("lebedev_level: %lu\n", args.lebedev_level);

    printf("md_steps: %lu\n", args.md_steps);

    printf("md_delta_t_fs: %.3e\n", args.md_delta_t_fs);
    printf("md_temperature_K: %.3e\n", args.md_temperature_K);
    printf("md_thermostat_time_smoothing_factor: %.3e\n", args.md_thermostat_time_smoothing_factor);

    printf("silent: %lu\n", args.silent);
    printf("check_results: %lu\n", args.check_results);

    return 0;
}
#endif
