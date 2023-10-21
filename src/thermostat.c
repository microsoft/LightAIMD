/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include "thermostat.h"

#include <assert.h>
#include <math.h>

#include "constants.h"
#include "mm.h"
#include "random.h"
#include "vec3d.h"
#include "velocity_init.h"

void enforce_temperature(struct molecule* mol, f64 temperature_K)
{
    f64 scaling_factor = sqrt(temperature_K / calc_temperature(mol));

    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        mol->velocities[i].x *= scaling_factor;
        mol->velocities[i].y *= scaling_factor;
        mol->velocities[i].z *= scaling_factor;
    }
}

f64 calc_temperature(struct molecule* mol)
{
    f64 kinetic_energy = 0.0;

    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        struct vec3d* v = mol->velocities + i;
        f64 v_sq = v->x * v->x + v->y * v->y + v->z * v->z;
        kinetic_energy += 0.5 * mol->masses[i] * v_sq;
    }
    f64 temperature_K = kinetic_energy * ENERGY_ATOMIC_UNIT_TO_J / (1.5 * mol->n_atoms) / BOLTZMANN_CONSTANT_k;
    return temperature_K;
}

void thermostat_berendsen_nvt(struct molecule* mol, f64 temperature_K, f64 time_smoothing_factor)
{
    f64 current_temperature = calc_temperature(mol);
    f64 scaling_factor = sqrt(1.0 + (temperature_K / current_temperature - 1.0) * time_smoothing_factor);

    scaling_factor = scaling_factor > 1.1 ? 1.1 : scaling_factor;
    scaling_factor = scaling_factor < 0.9 ? 0.9 : scaling_factor;

    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        mol->velocities[i].x *= scaling_factor;
        mol->velocities[i].y *= scaling_factor;
        mol->velocities[i].z *= scaling_factor;
    }
}

#ifdef MODULE_TEST
void test_temperature()
{
    /* create a random molecule*/
    struct molecule* mol = x_malloc(sizeof(struct molecule));
    f64 T = 300.0;
    mol->n_atoms = 1000;
    mol->masses = x_malloc(mol->n_atoms * sizeof(f64));
    mol->velocities = x_malloc(mol->n_atoms * sizeof(struct vec3d));
    for (u64 i = 0; i < mol->n_atoms; ++i)
    {
        mol->masses[i] = (rand_uniform() * 100 + 1) * DALTON_TO_AU;
    }

    /* init velocity */
    maxwell_boltzmann_velocity_init(mol, T);

    f64 temp = calc_temperature(mol);
    printf("Number of atoms: %lu, Temperature (K): %f (should be %f)\n",
           mol->n_atoms, temp, T);
    assert(fabs(temp - T) < 5);

    thermostat_berendsen_nvt(mol, T, 1e-3);
    temp = calc_temperature(mol);
    printf("After berendsen_scale, Temperature (K): %f\n", temp);
    assert(fabs(temp - T) < 5);

    enforce_temperature(mol, T);
    temp = calc_temperature(mol);
    printf("After enforce_temperature, Temperature (K): %f\n", temp);
    assert(fabs(temp - T) < 0.01);

    x_free(mol->masses);
    x_free(mol->velocities);
    x_free(mol);
}

int main(void)
{
    test_temperature();
    print_mm_status();
    return 0;
}
#endif
