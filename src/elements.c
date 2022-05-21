/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <string.h>
#include "numeric_types.h"

char *ELEMENTS[] = {
    "X", /* Placeholder */
    "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne",
    "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca",
    "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",
    "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr",
    "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn",
    "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd",
    "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb",
    "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg",
    "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th",
    "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm",
    "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds",
    "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og" /* Og: 118 (Z) */
};

u64 atomic_symbol_to_num(char const *sym)
{
    for (u64 i = 0; i < 119; ++i)
    {
        if (strcmp(ELEMENTS[i], sym) == 0)
        {
            return i;
        }
    }
    return 0;
}

char *ATOMIC_NAMES[] = {
    "Placeholder",
    /* IUPAC version dated 28 November 2016 */
    "Hydrogen", "Helium", "Lithium", "Beryllium", "Boron",
    "Carbon", "Nitrogen", "Oxygen", "Fluorine", "Neon",
    "Sodium", "Magnesium", "Aluminium", "Silicon", "Phosphorus",
    "Sulfur", "Chlorine", "Argon", "Potassium", "Calcium",
    "Scandium", "Titanium", "Vanadium", "Chromium", "Manganese",
    "Iron", "Cobalt", "Nickel", "Copper", "Zinc",
    "Gallium", "Germanium", "Arsenic", "Selenium", "Bromine",
    "Krypton", "Rubidium", "Strontium", "Yttrium", "Zirconium",
    "Niobium", "Molybdenum", "Technetium", "Ruthenium", "Rhodium",
    "Palladium", "Silver", "Cadmium", "Indium", "Tin",
    "Antimony", "Tellurium", "Iodine", "Xenon", "Caesium",
    "Barium", "Lanthanum", "Cerium", "Praseodymium", "Neodymium",
    "Promethium", "Samarium", "Europium", "Gadolinium", "Terbium",
    "Dysprosium", "Holmium", "Erbium", "Thulium", "Ytterbium",
    "Lutetium", "Hafnium", "Tantalum", "Tungsten", "Rhenium",
    "Osmium", "Iridium", "Platinum", "Gold", "Mercury",
    "Thallium", "Lead", "Bismuth", "Polonium", "Astatine",
    "Radon", "Francium", "Radium", "Actinium", "Thorium",
    "Protactinium", "Uranium", "Neptunium", "Plutonium", "Americium",
    "Curium", "Berkelium", "Californium", "Einsteinium", "Fermium",
    "Mendelevium", "Nobelium", "Lawrencium", "Rutherfordium", "Dubnium",
    "Seaborgium", "Bohrium", "Hassium", "Meitnerium", "Darmastadtium",
    "Roentgenium", "Copernicium", "Nihonium", "Flerovium", "Moscovium",
    "Livermorium", "Tennessine", "Oganesson" /* Oganesson: 118 (Z) */
};

/*
 * Ref: https://en.wikipedia.org/wiki/Standard_atomic_weight
 * Ref: https://iupac.qmul.ac.uk/AtWt/
 */
f64 STANDARD_ATOMIC_WEIGHTS[] = {
    0.,           // Placeholder
    1.008,        // H [1.00784, 1.00811]
    4.002602,     // He
    6.94,         // Li [6.938, 6.997]
    9.0121831,    // Be
    10.81,        // B [10.806, 10.821]
    12.011,       // C [12.0096, 12.0116]
    14.007,       // N [14.00643, 14.00728]
    15.999,       // O [15.99903, 15.99977]
    18.998403163, // F
    20.1797,      // Ne
    22.98976928,  // Na
    24.305,       // Mg [24.304, 24.307]
    26.9815384,   // Al, updated in 2017, 26.9815385 -> 26.9815384
    28.085,       // Si [28.084, 28.086]
    30.973761998, // P
    32.06,        // S [32.059, 32.076]
    35.45,        // Cl [35.446, 35.457]
    39.948,       // Ar
    39.0983,      // K
    40.078,       // Ca
    44.955908,    // Sc
    47.867,       // Ti
    50.9415,      // V
    51.9961,      // Cr
    54.938043,    // Mn, updated in 2017, 54.938044 -> 54.938043
    55.845,       // Fe
    58.933194,    // Co
    58.6934,      // Ni
    63.546,       // Cu
    65.38,        // Zn
    69.723,       // Ga
    72.630,       // Ge
    74.921595,    // As
    78.971,       // Se
    79.904,       // Br [79.901, 79.907]
    83.798,       // Kr
    85.4678,      // Rb
    87.62,        // Sr
    88.90584,     // Y
    91.224,       // Zr
    92.90637,     // Nb
    95.95,        // Mo
    97.90721,     // 98Tc
    101.07,       // Ru
    102.90549,    // Rh, updated in 2017, 102.90550 -> 102.90549
    106.42,       // Pd
    107.8682,     // Ag
    112.414,      // Cd
    114.818,      // In
    118.710,      // Sn
    121.760,      // Sb
    127.60,       // Te
    126.90447,    // I
    131.293,      // Xe
    132.90545196, // Cs
    137.327,      // Ba
    138.90547,    // La
    140.116,      // Ce
    140.90766,    // Pr
    144.242,      // Nd
    144.91276,    // 145Pm
    150.36,       // Sm
    151.964,      // Eu
    157.25,       // Gd
    158.925354,   // Tb, updated in 2017, 158.92535 -> 158.925354
    162.500,      // Dy
    164.930328,   // Ho, updated in 2017, 164.93033 -> 164.930328
    167.259,      // Er
    168.934218,   // Tm, updated in 2017, 168.93422 -> 168.934218
    173.045,      // Yb, updated in 2017, 173.054 -> 173.045
    174.9668,     // Lu
    178.49,       // Hf
    180.94788,    // Ta
    183.84,       // W
    186.207,      // Re
    190.23,       // Os
    192.217,      // Ir
    195.084,      // Pt
    196.966570,   // Au, updated in 2017, 196.966569 -> 196.966570
    200.592,      // Hg
    204.38,       // Tl [204.382, 204.385]
    207.2,        // Pb
    208.98040,    // Bi
    208.98243,    // Po
    209.98715,    // At
    222.01758,    // Rn
    223.01974,    // Fr
    226.02541,    // Ra
    227.02775,    // Ac
    232.0377,     // Th
    231.03588,    // Pa
    238.02891,    // U
    237.04817,    // Np
    244.06421,    // Pu
    243.06138,    // Am
    247.07035,    // Cm
    247.07031,    // Bk
    251.07959,    // Cf
    252.0830,     // Es
    257.09511,    // Fm
    258.09843,    // Md
    259.1010,     // No
    262.110,      // Lr
    267.122,      // Rf
    268.126,      // Db
    271.134,      // Sg
    270.133,      // Bh
    269.1338,     // Hs
    278.156,      // Mt
    281.165,      // Ds
    281.166,      // Rg
    285.177,      // Cn
    286.182,      // Nh
    289.190,      // Fl
    289.194,      // Mc
    293.204,      // Lv
    293.208,      // Ts
    294.214       // Og, Z: 118
};

f64 atomic_num_to_mass(u64 Z)
{
    return STANDARD_ATOMIC_WEIGHTS[Z];
}

/*
 * Bragg slater radii in angstroms
 * Ref: Atomic Radii in Crystals, JCP 41, 3199
 * Ref: A multicenter numerical integration scheme for polyatomic molecules, JCP 88, 2547
 */
f64 BRAGG_SLATER_RADII[] = {
    0, // Placeholder
    /*
     * Ref: JCP 88, 2547, appendix: atomic size adjustments
     * "For hydrogen, however, we prefer a radius of 0.35 A, somewhat larger than Slater's value of 0.25 A."
     */
    0.35, // H
    1.40,
    1.45, 1.05, 0.85, 0.70, 0.65, 0.60, 0.50, 1.50,
    1.80, 1.50, 1.25, 1.10, 1.00, 1.00, 1.00, 1.80,
    2.20, 1.80,
    1.60, 1.40, 1.35, 1.40, 1.40, 1.40, 1.35, 1.35, 1.35, 1.35,
    1.30, 1.25, 1.15, 1.15, 1.15, 1.90,
    2.35, 2.00,
    1.80, 1.55, 1.45, 1.45, 1.35, 1.30, 1.35, 1.40, 1.60, 1.55,
    1.55, 1.45, 1.45, 1.40, 1.40, 2.10,
    2.60, 2.15,
    1.95, 1.85, 1.85, 1.85, 1.85, 1.85, 1.85,
    1.80, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75,
    1.55, 1.45, 1.35, 1.35, 1.30, 1.35, 1.35, 1.35, 1.50,
    1.90, 1.80, 1.60, 1.90, 1.45, 2.10,
    1.80, 2.15,
    1.95, 1.80, 1.80, 1.75, 1.75, 1.75, 1.75,
    1.75, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75,
    1.75, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75,
    1.75, 1.75, 1.75, 1.75, 1.75, 1.75,
    1.75, 1.75,
    1.75, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75, 1.75 //
};

u64 STO_3G_Atomic_ORBITAL_COUNT[] = {
    0,  // Placeholder
    1,  // Z: 1
    1,  // Z: 2
    5,  // Z: 3
    5,  // Z: 4
    5,  // Z: 5
    5,  // Z: 6
    5,  // Z: 7
    5,  // Z: 8
    5,  // Z: 9
    5,  // Z: 10
    9,  // Z: 11
    9,  // Z: 12
    9,  // Z: 13
    9,  // Z: 14
    9,  // Z: 15
    9,  // Z: 16
    9,  // Z: 17
    9,  // Z: 18
    13, // Z: 19
    13, // Z: 20
    19, // Z: 21
    19, // Z: 22
    19, // Z: 23
    19, // Z: 24
    19, // Z: 25
    19, // Z: 26
    19, // Z: 27
    19, // Z: 28
    19, // Z: 29
    19, // Z: 30
    19, // Z: 31
    19, // Z: 32
    19, // Z: 33
    19, // Z: 34
    19, // Z: 35
    19, // Z: 36
    23, // Z: 37
    23, // Z: 38
    29, // Z: 39
    29, // Z: 40
    29, // Z: 41
    29, // Z: 42
    29, // Z: 43
    29, // Z: 44
    29, // Z: 45
    29, // Z: 46
    29, // Z: 47
    29, // Z: 48
    29, // Z: 49
    29, // Z: 50
    29, // Z: 51
    29, // Z: 52
    29, // Z: 53
    29  // Z: 54
};

#ifdef MODULE_TEST
#include <stdio.h>
int main(void)
{
    for (u64 i = 0; i < 119; ++i)
    {
        printf("%lu %s %s %f\n", i, ELEMENTS[i], ATOMIC_NAMES[i], STANDARD_ATOMIC_WEIGHTS[i]);
    }
    return 0;
}
#endif
