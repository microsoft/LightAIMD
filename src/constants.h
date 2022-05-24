/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define CODATA_2018

#ifdef CODATA_2018
/* Constants*/
#define PLANCK_CONSTANT_h 6.62607015e-34             // exact, unit: J / Hz
#define PLANCK_CONSTANT_hbar 1.0545718176461565e-34  // derived value: PLANCK_CONSTANT_h / (2 pi)
#define BOLTZMANN_CONSTANT_k 1.380649e-23            // exact, unit: J/K
#define ELEMENTARY_CHARGE_e 1.602176634e-19          // exact, unit: C
#define BOLTZMANN_CONSTANT_kB 8.6173332621451788e-05 // derived value: BOLTZMANN_CONSTANT_k / ELEMENTARY_CHARGE_e, unit: eV/K
#define BOHR_RADIUS_a0 5.29177210903e-11             // unit: m, uncertainty: (80)
#define ELECTRON_MASS_me 9.1093837015e-31            // unit: kg, uncertainty: (28)

/* Conversion factors */
#define BOHR_TO_ANGSTROM 5.29177210903e-01
#define ENERGY_ATOMIC_UNIT_TO_J 4.3597447222071e-18     // unit: J, Hartree to J, uncertainty (85)
#define ENERGY_J_TO_ATOMIC_UNIT 2.2937122783963248e+17  // derived value: 1 / ENERGY_ATOMIC_UNIT_TO_J
#define ENERGY_ATOMIC_UNIT_TO_eV 27.211386245988        // unit: eV, uncertainty (53)
#define ENERGY_eV_TO_ATOMIC_UNIT 3.6749322175654991e-02 // derived value, 1 / ENERGY_ATOMIC_UNIT_TO_eV

#define VELOCITY_ATOMIC_UNIT_TO_M_PER_S 2.18769126364e+06              // unit: m/s, hbar / (me * a0), uncertainty: (33)
#define VELOCITY_ATOMIC_UNIT_TO_ANGSTROM_PER_FS 2.18769126364e+01      // VELOCITY_ATOMIC_UNIT_TO_M_PER_S * 1e-05
#define VELOCITY_ANGSTROM_PER_FS_TO_ATOMIC_UNIT 4.5710289043991770e-02 // derived value: 1 / VELOCITY_ATOMIC_UNIT_TO_ANGSTROM_PER_FS

#define TIME_ATOMIC_UNIT_TO_S 2.4188843265857e-17     // unit: s, uncertainity: (47)
#define TIME_ATOMIC_UNIT_TO_FS 2.4188843265857e-02    // unit: fs
#define TIME_FS_TO_ATOMIC_UNIT 4.1341373335182112e+01 // derived value: 1 / TIME_ATOMIC_UNIT_TO_FS

#define FORCE_HARTREE_PER_BOHR_TO_HARTREE_PER_ANGSTROM 1.8897261246257702 // derived value: 1 / BOHR_TO_ANGSTROM
#endif

#ifdef CODATA_2014
#define BOHR_TO_ANGSTROM 0.52917721067
#endif

#ifdef CODATA_2010
#define BOHR_TO_ANGSTROM 0.52917721092
#endif

/* ref: https://en.wikipedia.org/wiki/Dalton_(unit) */
#define DALTON_TO_AU 1822.888486209 // uncertainty: (53)

/*
 * For the mathematical constants, 17 significant digits are kept to fully recover the binary double-precision representation
 */

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* pow(M_PI, 1.5) */
#define POW_PI_1_DOT_5 5.568327996831708

// log(2.0 * M_PI)
#define LOG_2PI 1.8378770664093453e+00

#define F64_QUASI_INFINITY 1e+300

/* 1.0 / 3.0 */
#define ONE_THIRD 3.3333333333333331e-01

/* sqrt(0.5) */
#define SQRT_1_2 7.0710678118654757e-01

/* sqrt(1.0/3.0) */
#define SQRT_1_3 5.7735026918962573e-01

/* 1/ln(2) */
#define ONE_OVER_LN2 1.4426950408889634

#endif
