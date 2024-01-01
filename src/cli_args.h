/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef CMD_LINE_ARGS_H
#define CMD_LINE_ARGS_H
#include "numeric_types.h"
#include "molecule.h"

extern u64 const JOB_TYPE_SPE;  // Single Point Energy
extern u64 const JOB_TYPE_SPF;  // Single Point Forces
extern u64 const JOB_TYPE_BOMD; // Born-Oppenheimer Molecular Dynamics

extern u64 const CC_METHOD_HF;  // Hartree Fock
extern u64 const CC_METHOD_DFT; // Density Functional Theory

extern u64 const GRID_SCHEME_FULL;
extern u64 const GRID_SCHEME_SG2;
extern u64 const GRID_SCHEME_SG3;

struct cmd_line_args
{
    u64 job_type;
    char* basis_set;
    struct molecule* mol;

    u64 cc_method;

    /* SCF */
    u64 damping; // flag

    /* DIIS */
    u64 diis_subspace_size;

    /* DFT related command-line arguments */
    u64 x_functional_id;
    u64 c_functional_id;
    u64 radial_grid_level;
    u64 lebedev_level;
    u64 grid_scheme;

    /* MD */
    u64 md_steps;
    f64 md_delta_t_fs;
    f64 md_temperature_K;
    f64 md_thermostat_time_smoothing_factor;

    /* MISC */
    u64 silent; // flag
    u64 check_results;
};

u64 cli_check_flag(int argc, char* argv[], char const* key);
char* cli_get_arg_value_by_key(int argc, char* argv[], char const* key);
void cli_parse_args(int argc, char* argv[], struct cmd_line_args* args);

#endif
