/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef MOLECULE_H
#define MOLECULE_H
#include <stdio.h>

#include "numeric_types.h"
#include "vec3d.h"

struct molecule
{
    u64 n_atoms;
    u64 n_electrons;
    u64 *atomic_nums;
    f64 *masses;

    /* coords */
    struct vec3d *coords;
    struct vec3d *velocities;
    struct vec3d *forces_last;
    struct vec3d *forces;

    u64 multiplicity;

    char *name;
};

void free_molecule(struct molecule *mol);
void mol_reset_forces(struct molecule *mol);
i64 read_xyz(char const *xyz_file, struct molecule *mol);
void write_trajectory(FILE *fp, struct molecule *mol, u64 step);
void write_velocities(FILE *fp, struct molecule *mol, u64 step);
void write_forces(FILE *fp, struct molecule *mol, u64 step);
u64 *mol_elements(struct molecule *mol);
void center_of_charge(struct molecule *mol, struct vec3d *cc);
void print_molecule(struct molecule *mol);

#endif
