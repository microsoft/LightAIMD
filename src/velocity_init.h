/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef VELOCITY_INIT_H
#define VELOCITY_INIT_H

#include "molecule.h"
#include "numeric_types.h"

void maxwell_boltzmann_velocity_init(struct molecule *mol, f64 temperature_K);

#endif
