/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "molecule.h"
#include "elements.h"
#include "error_code.h"
#include "mm.h"
#include "io.h"

void free_molecule(struct molecule *mol)
{
    x_free(mol->atomic_nums);
    x_free(mol->masses);
    x_free(mol->coords);
    x_free(mol->velocities);
    x_free(mol->forces_last);
    x_free(mol->forces);
    x_free(mol->name);
    x_free(mol);
}

void mol_reset_forces(struct molecule *mol)
{
    memset(mol->forces, 0, mol->n_atoms * sizeof(struct vec3d));
}

i64 read_xyz(char const *xyz_file, struct molecule *mol)
{
    FILE *fp = fopen(xyz_file, "r");
    if (!fp)
    {
        fprintf(stderr, "fopen() failed in file %s at line %d", __FILE__, __LINE__);
        return E_FAILURE;
    }

    char buff[1024];
    // read atom number
    if (fgets(buff, sizeof(buff), fp))
    {
        char *str_end;
        mol->n_atoms = strtoull(buff, &str_end, 10);
    }

    u64 use_unit_angstrom = 1;
    i64 molecular_charge = 0;
    // read comment line
    if (fgets(buff, sizeof(buff), fp))
    {
        char *p = buff + strlen("charge ");
        char *str_end;
        molecular_charge = strtoll(p, &str_end, 10);
        p = str_end + strlen(" multiplicity ");
        mol->multiplicity = strtoull(p, &str_end, 10);

        p = str_end + strlen(" unit ");
        if (!strncmp(p, "bohr", strlen("bohr"))) // not bohr
        {
            use_unit_angstrom = 0;
        }
    }

    mol->atomic_nums = x_malloc(mol->n_atoms * sizeof(u64));
    mol->masses = x_malloc(mol->n_atoms * sizeof(f64));
    mol->coords = x_malloc(mol->n_atoms * sizeof(struct vec3d));
    mol->velocities = x_malloc(mol->n_atoms * sizeof(struct vec3d));
    mol->forces_last = x_malloc(mol->n_atoms * sizeof(struct vec3d));
    mol->forces = x_malloc(mol->n_atoms * sizeof(struct vec3d));
    mol->name = x_malloc(256);

    u64 lc = 0;
    u64 total_nuclear_charge = 0;
    while (fgets(buff, sizeof(buff), fp))
    {
        char *atom_symbol = strtok(buff, " ");
        u64 Z = atomic_symbol_to_num(atom_symbol);
        total_nuclear_charge += Z;
        mol->atomic_nums[lc] = Z;
        mol->masses[lc] = atomic_num_to_mass(Z) * DALTON_TO_AU;
        /* atom_symbol will be null if a line contains only blank spaces */
        if (!atom_symbol)
        {
            break;
        }

        f64 x = strtod(strtok(NULL, " "), NULL);
        f64 y = strtod(strtok(NULL, " "), NULL);
        f64 z = strtod(strtok(NULL, " "), NULL);
        if (use_unit_angstrom)
        {
            mol->coords[lc].x = x / BOHR_TO_ANGSTROM;
            mol->coords[lc].y = y / BOHR_TO_ANGSTROM;
            mol->coords[lc].z = z / BOHR_TO_ANGSTROM;
        }
        else
        {
            mol->coords[lc].x = x;
            mol->coords[lc].y = y;
            mol->coords[lc].z = z;
        }
        ++lc;
    }
    mol->n_electrons = (u64)(total_nuclear_charge - molecular_charge);
    filename_stem(xyz_file, mol->name);

    fclose(fp);
    return E_SUCCESS;
}

void write_trajectory(FILE *fp, struct molecule *mol, u64 step)
{
    fprintf(fp, "%lu\n", mol->n_atoms);
    fprintf(fp, "Step %lu coordinates (unit angstrom)\n", step);
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        fprintf(fp, "%2s %23.16e %23.16e %23.16e\n", ELEMENTS[mol->atomic_nums[i]], mol->coords[i].x * BOHR_TO_ANGSTROM, mol->coords[i].y * BOHR_TO_ANGSTROM, mol->coords[i].z * BOHR_TO_ANGSTROM);
    }
}

void write_velocities(FILE *fp, struct molecule *mol, u64 step)
{
    fprintf(fp, "%lu\n", mol->n_atoms);
    fprintf(fp, "Step %lu velocity (unit angstrom/fs)\n", step);
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        fprintf(fp, "%2s %23.16e %23.16e %23.16e\n", ELEMENTS[mol->atomic_nums[i]], mol->velocities[i].x * VELOCITY_ATOMIC_UNIT_TO_ANGSTROM_PER_FS, mol->velocities[i].y * VELOCITY_ATOMIC_UNIT_TO_ANGSTROM_PER_FS, mol->velocities[i].z * VELOCITY_ATOMIC_UNIT_TO_ANGSTROM_PER_FS);
    }
}

void write_forces(FILE *fp, struct molecule *mol, u64 step)
{
    fprintf(fp, "%lu\n", mol->n_atoms);
    fprintf(fp, "Step %lu forces (unit hartree/angstrom)\n", step);
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        fprintf(fp, "%2s %23.16e %23.16e %23.16e\n", ELEMENTS[mol->atomic_nums[i]], mol->forces[i].x * FORCE_HARTREE_PER_BOHR_TO_HARTREE_PER_ANGSTROM, mol->forces[i].y * FORCE_HARTREE_PER_BOHR_TO_HARTREE_PER_ANGSTROM, mol->forces[i].z * FORCE_HARTREE_PER_BOHR_TO_HARTREE_PER_ANGSTROM);
    }
}

u64 *mol_elements(struct molecule *mol)
{
    u64 elements[128] = {0};
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        elements[mol->atomic_nums[i]] = 1;
    }

    u64 n_elements = 0;
    for (u64 i = 0; i < 128; ++i)
    {
        n_elements += elements[i];
    }

    u64 *p_elements = x_malloc(sizeof(u64) * (n_elements + 1));
    p_elements[0] = n_elements;
    u64 p = 1;
    for (u64 i = 0; i < 128; ++i)
    {
        if (elements[i])
        {
            p_elements[p] = i;
            ++p;
        }
    }
    return p_elements;
}

void center_of_charge(struct molecule *mol, struct vec3d *cc)
{
    f64 cc_x = 0.0;
    f64 cc_y = 0.0;
    f64 cc_z = 0.0;
    f64 total_charge = 0.0;
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        cc_x += mol->coords[i].x * mol->atomic_nums[i];
        cc_y += mol->coords[i].y * mol->atomic_nums[i];
        cc_z += mol->coords[i].z * mol->atomic_nums[i];
        total_charge += mol->atomic_nums[i];
    }

    cc_x /= total_charge;
    cc_y /= total_charge;
    cc_z /= total_charge;

    cc->x = cc_x;
    cc->y = cc_y;
    cc->z = cc_z;
}

void print_molecule(struct molecule *mol)
{
    printf("--------------------------------- molecule ---------------------------------\n");
    printf("n_atoms: %lu\n", mol->n_atoms);
    printf("n_electrons: %lu\n", mol->n_electrons);
    printf("multiplicity: %lu\n", mol->multiplicity);
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        printf("atom %3lu Z: %lu mass: %.4e\n",
               i + 1, mol->atomic_nums[i], mol->masses[i]);

        printf("     coord: (%13.6e, %13.6e, %13.6e)\n", mol->coords[i].x, mol->coords[i].y, mol->coords[i].z);
        printf("velocities: (%13.6e, %13.6e, %13.6e)\n", mol->velocities[i].x, mol->velocities[i].y, mol->velocities[i].z);
        printf("    forces: (%13.6e, %13.6e, %13.6e)\n", mol->forces[i].x, mol->forces[i].y, mol->forces[i].z);
        printf("\n");
    }
    printf("----------------------------------------------------------------------------\n");
}

#ifdef MODULE_TEST
int main(void)
{
    struct molecule *mol = x_malloc(sizeof(struct molecule));
    read_xyz("sample/chignolin.xyz", mol);
    print_molecule(mol);
    return 0;
}
#endif
