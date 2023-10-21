/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef SAMPLE_H
#define SAMPLE_H

#include "numeric_types.h"
#include "molecule.h"

extern u64 h2o_atomic_num[];
extern f64 h2o_coords[3][3];
extern u64 h2o_charge;
extern u64 h2o_multiplicity;

struct molecule* sample_molecule_h2o();
i64 check_total_energy(f64 value, u64 cc_method_id);
i64 check_forces(f64* forces, u64 cc_method_id);

#endif
