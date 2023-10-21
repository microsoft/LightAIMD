/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include "velocity_init.h"

#include <assert.h>
#include <math.h>

#include "constants.h"
#include "mm.h"
#include "random.h"
#include "thermostat.h"
#include "vec3d.h"

void maxwell_boltzmann_velocity_init(struct molecule* mol, f64 temperature_K)
{
    f64 t_au = BOLTZMANN_CONSTANT_k * temperature_K * ENERGY_J_TO_ATOMIC_UNIT;
    f64* rnd = x_malloc(mol->n_atoms * 3 * sizeof(f64));
    rand_standard_normal(rnd, mol->n_atoms * 3);

    f64* p_rnd = rnd;
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        f64 v = sqrt(t_au / mol->masses[i]);
        mol->velocities[i].x = p_rnd[0] * v;
        mol->velocities[i].y = p_rnd[1] * v;
        mol->velocities[i].z = p_rnd[2] * v;
        p_rnd += 3;
    }
    x_free(rnd);
}

#ifdef MODULE_TEST
int main(void)
{
    struct molecule* mol = x_malloc(sizeof(struct molecule));
    f64 T = 300.0;
    mol->n_atoms = 1000;
    mol->masses = x_malloc(mol->n_atoms * sizeof(f64));
    mol->velocities = x_malloc(mol->n_atoms * sizeof(struct vec3d));
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        mol->masses[i] = (rand_uniform() * 100 + 1) * DALTON_TO_AU;
    }

    maxwell_boltzmann_velocity_init(mol, T);

    for (u64 i = 0; i < 16; ++i)
    {
        printf("%lu i: %.6e\n", i, mol->velocities[i].y);
    }

    f64 temp = calc_temperature(mol);
    printf("Number of atoms: %lu, Temperature (K): %f (should be %f)\n",
           mol->n_atoms, temp, T);
    assert(fabs(temp - T) < 5);

    x_free(mol->masses);
    x_free(mol->velocities);
    x_free(mol);
    print_mm_status();
    return 0;
}
#endif
