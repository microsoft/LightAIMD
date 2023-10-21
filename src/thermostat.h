/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "molecule.h"
#include "numeric_types.h"

/* enforce the given temperature */
void enforce_temperature(struct molecule* mol, f64 temperature_K);

/* Get the temperature of the molecule in Kelvin. */
f64 calc_temperature(struct molecule* mol);

/*
 * Berendsen velocity rescaling scheme for NVT ensemble.
 * time_smoothing_factor, whose range is (0, 1], is the ratio of (dt / tau) in the terms of the vanilla Berendsen.
 * When time_smoothing_factor is 1, the temperature deviation will be corrected immediately;
 * When time_smoothing_factor < 1, the cooling down or heating up process is smoothed over time;
 * smaller the factor, slower the process.
 */
void thermostat_berendsen_nvt(struct molecule* mol, f64 temperature_K, f64 time_smoothing_factor);

#endif
