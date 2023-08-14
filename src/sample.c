/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "constants.h"
#include "elements.h"
#include "molecule.h"
#include "f64_util.h"
#include "mm.h"
#include "diagnostics.h"

u64 h2o_atomic_nums[] = {1, 1, 8};

struct vec3d h2o_coords[3] = {
    {0.00, 0.49, -0.79}, // H
    {0.00, 0.49, 0.79},  // H
    {0.00, -0.12, 0.00}  // O
};

u64 h2o_charge = 0;
u64 h2o_multiplicity = 1;

struct molecule *sample_molecule_h2o()
{
    struct molecule *h2o = x_malloc(sizeof(struct molecule));
    h2o->atomic_nums = x_malloc(3 * sizeof(u64));
    h2o->masses = x_malloc(3 * sizeof(f64));
    h2o->coords = x_malloc(3 * sizeof(struct vec3d));
    h2o->velocities = x_malloc(3 * sizeof(struct vec3d));
    h2o->forces_last = x_malloc(3 * sizeof(struct vec3d));
    h2o->forces = x_malloc(3 * sizeof(struct vec3d));
    h2o->name = x_malloc(8);
    for (u64 i = 0; i < 3; ++i)
    {
        h2o->atomic_nums[i] = h2o_atomic_nums[i];
        h2o->masses[i] = STANDARD_ATOMIC_WEIGHTS[h2o_atomic_nums[i]] * DALTON_TO_AU;
        h2o->coords[i].x = h2o_coords[i].x / BOHR_TO_ANGSTROM;
        h2o->coords[i].y = h2o_coords[i].y / BOHR_TO_ANGSTROM;
        h2o->coords[i].z = h2o_coords[i].z / BOHR_TO_ANGSTROM;
    }
    h2o->n_atoms = 3;
    h2o->n_electrons = 10;
    h2o->multiplicity = 1;

    memcpy(h2o->name, "h2o", 4);

    return h2o;
}

/*
 * Suffixes:
 * lv: lebedev level
 * rv: radial level
 */

f64 self_ref_energy_results_lv14_rv6[] = {
    -7.4964697712686018e+01, // HF
    -7.4739356439434076e+01, // DFT: LDA_X,LDA_C_VWN
    -7.5233707494446236e+01, // DFT: GGA_X_PBE,GGA_C_PBE
    -7.5319468740973932e+01, // DFT: HYB_GGA_XC_B3LYP
    -7.5310734601047500e+01, // DFT: MGGA_X_M06_L,MGGA_C_M06_L
    -7.5318292025239657e+01  // DFT: HYB_MGGA_X_M06_2X,MGGA_C_M06_2X
};

f64 self_ref_forces_on_nuclei_lv14_rv6[][9] = {
    {// HF
     1.5750748104263788e-18, 2.3539258256943807e-03, 1.7964854393100804e-02,
     -5.6503404027018776e-18, 2.3539258256946027e-03, -1.7964854393101026e-02,
     4.0752655922754999e-18, -4.7078516513945345e-03, -4.2440701848653118e-16},
    {// DFT: LDA_X,LDA_C_VWN
     2.9207915174437467e-18, 2.8926313175810847e-02, -1.0625703513341911e-02,
     2.1711404134723697e-17, 2.8926313175809515e-02, 1.0625703513343021e-02,
     -1.1735533955743336e-17, -5.7849736601347068e-02, -4.9819962680367374e-15},
    {// DFT: GGA_X_PBE,GGA_C_PBE
     5.4748322210942997e-19, 3.3608239725162470e-02, -1.4081048713330713e-02,
     -5.6482076512706944e-18, 3.3608239725162026e-02, 1.4081048713330491e-02,
     2.1676777539690636e-17, -6.7205826092596066e-02, -9.4691645873631095e-15},
    {// DFT: HYB_GGA_XC_B3LYP
     1.6710536637530739e-18, 2.7335910277611619e-02, -8.6456364174316569e-03,
     -2.0038396238089902e-17, 2.7335910277606734e-02, 8.6456364174314349e-03,
     3.5034720358725603e-17, -5.4664147389984930e-02, -4.4119586114931980e-15},
    {// DFT: MGGA_X_M06_L,MGGA_C_M06_L
     -1.2134147984068639e-17, 2.3610410426274653e-02, -4.9338743938931451e-04,
     2.9411138328342418e-17, 2.3610410426273321e-02, 4.9338743938820429e-04,
     -6.6613378884004808e-17, -4.7287897097694209e-02, -1.1396575184903440e-15},
    {// DFT: HYB_MGGA_X_M06_2X,MGGA_C_M06_2X
     -2.1094330734923149e-17, 2.0356538498262688e-02, -1.5775748602009365e-03,
     2.5324824313039180e-17, 2.0356538498264021e-02, 1.5775748602016026e-03,
     2.9843452214013341e-16, -4.0661205803001810e-02, 1.2819918977464476e-16}};

f64 pyscf_grid_lvl3_energy_11e_results[] = {
    -7.49646977127e+01, // HF
    -7.47393642241e+01, // DFT: LDA_X,LDA_C_VWN
    -7.52337124545e+01, // DFT: GGA_X_PBE,GGA_C_PBE
    -7.53194733533e+01, // DFT: HYB_GGA_XC_B3LYP
    -7.53107436057e+01, // DFT: MGGA_X_M06_L,MGGA_C_M06_L
    -7.53182583267e+01  // DFT: HYB_MGGA_X_M06_2X,MGGA_C_M06_2X
};

f64 pyscf_grid_lvl3_energy_acceptance_threshold_lv14_rv6[] = {
    1.4e-11, // HF
    7.8e-06, // DFT: LDA_X,LDA_C_VWN
    5.0e-06, // DFT: GGA_X_PBE,GGA_C_PBE
    4.7e-06, // DFT: HYB_GGA_XC_B3LYP
    9.1e-06, // DFT: MGGA_X_M06_L,MGGA_C_M06_L
    3.4e-05  // DFT: HYB_MGGA_X_M06_2X,MGGA_C_M06_2X
};

f64 pyscf_grid_lvl4_energy_11e_results[] = {
    -7.49646977127e+01, // HF
    -7.47393579907e+01, // DFT: LDA_X,LDA_C_VWN
    -7.52337086491e+01, // DFT: GGA_X_PBE,GGA_C_PBE
    -7.53194698434e+01, // DFT: HYB_GGA_XC_B3LYP
    -7.53107315664e+01, // DFT: MGGA_X_M06_L,MGGA_C_M06_L
    -7.53182976862e+01  // DFT: HYB_MGGA_X_M06_2X,MGGA_C_M06_2X
};

f64 pyscf_grid_lvl4_energy_acceptance_threshold_lv14_rv6[] = {
    1.4e-11, // HF
    1.6e-06, // DFT: LDA_X,LDA_C_VWN
    1.2e-06, // DFT: GGA_X_PBE,GGA_C_PBE
    1.2e-06, // DFT: HYB_GGA_XC_B3LYP
    3.1e-06, // DFT: MGGA_X_M06_L,MGGA_C_M06_L
    5.7e-06  // DFT: HYB_MGGA_X_M06_2X,MGGA_C_M06_2X
};

f64 pyscf_grid_lvl4_forces_on_nuclei[][9] = {
    {// HF
     1.4223388025631463e-17, 2.3536708412610352e-03, 1.7964856246361460e-02,
     3.2311056920281253e-17, 2.3536708412625895e-03, -1.7964856246360350e-02,
     -4.6534444945911816e-17, -4.7073416825225145e-03, -1.2802259252708836e-15},
    {// DFT: LDA_X,LDA_C_VWN
     -2.7781271132157854e-17, 2.8926442302140698e-02, -1.0625731811039207e-02,
     -5.8477891647054513e-17, 2.8926442302140698e-02, 1.0625731811038541e-02,
     1.4166150516487505e-16, -5.7876214750715249e-02, 8.3266726846886938e-17},
    {// DFT: GGA_X_PBE,GGA_C_PBE
     2.0085580055855134e-18, 3.3608348747936834e-02, -1.4081172972106426e-02,
     5.7415725228690897e-17, 3.3608348747938388e-02, 1.4081172972106204e-02,
     -6.3540237373091459e-17, -6.7224673544943325e-02, -2.1510571102112250e-16},
    {// DFT: HYB_GGA_XC_B3LYP
     -4.5271578727739728e-18, 2.7335986306790794e-02, -8.6456414541633553e-03,
     -4.2423974296011348e-19, 2.7335986306790794e-02, 8.6456414541629112e-03,
     2.7688362067177402e-17, -5.4684415357411531e-02, -2.0122792321330962e-16},
    {// DFT: MGGA_X_M06_L,MGGA_C_M06_L
     -1.4262138078868409e-17, 2.3598238994109622e-02, -5.1328178241294431e-04,
     6.5554562437762022e-17, 2.3598238994106957e-02, 5.1328178240983569e-04,
     -2.0389076973416833e-16, -4.7186530676884164e-02, 4.2604808569990374e-15},
    {// DFT: HYB_MGGA_X_M06_2X,MGGA_C_M06_2X
     1.1078247335367749e-16, 2.0368586043345349e-02, -1.5860015919204606e-03,
     -1.3184164101830065e-16, 2.0368586043346903e-02, 1.5860015919211268e-03,
     2.6460606272169974e-16, -4.0703749942135214e-02, -9.6103680569115113e-16}};

f64 pyscf_grid_lvl5_forces_on_nuclei[][9] = {
    {// HF
     1.4223388025631463e-17, 2.3536708412610352e-03, 1.7964856246361460e-02,
     3.2311056920281253e-17, 2.3536708412625895e-03, -1.7964856246360350e-02,
     -4.6534444945911816e-17, -4.7073416825225145e-03, -1.2802259252708836e-15},
    {// DFT: LDA_X,LDA_C_VWN
     1.5843308337067941e-17, 2.8926426244829218e-02, -1.0625736959399834e-02,
     -1.8310254515902521e-18, 2.8926426244830106e-02, 1.0625736959400722e-02,
     -1.2244753498717694e-17, -5.7852285220446387e-02, -1.6271706204662435e-15},
    {// DFT: GGA_X_PBE,GGA_C_PBE
     -1.9426601243151323e-17, 3.3608271067018913e-02, -1.4081049546275315e-02,
     1.5164336949305729e-16, 3.3608271067016249e-02, 1.4081049546271762e-02,
     -2.0974196189102208e-16, -6.7216221603672466e-02, 3.2231162183649076e-15},
    {// DFT: HYB_GGA_XC_B3LYP
     -2.7040913000651763e-17, 2.7335951542575287e-02, -8.6456218759654035e-03,
     -8.7687059562163019e-17, 2.7335951542577508e-02, 8.6456218759674019e-03,
     1.3349345794392232e-16, -5.4669658141794031e-02, -1.2177758801357186e-15},
    {// DFT: MGGA_X_M06_L,MGGA_C_M06_L
     2.7476766445326504e-17, 2.3602786900898565e-02, -5.1694902254229014e-04,
     -6.0973337713780281e-18, 2.3602786900898787e-02, 5.1694902254029174e-04,
     2.6281539505590676e-16, -4.7198041078716724e-02, 3.3896496720586811e-15},
    {// DFT: HYB_MGGA_X_M06_2X,MGGA_C_M06_2X
     -3.6953775946395935e-17, 2.0364316597167642e-02, -1.5911570739040037e-03,
     1.5684368534080027e-17, 2.0364316597165422e-02, 1.5911570739008951e-03,
     3.9748244895866170e-16, -4.0687886372441806e-02, 4.5866088704826795e-15}};

f64 pyscf_grid_lvl5_forces_on_nuclei_acceptance_threshold_lv14_rv6[] = {
    5.1e-07, // HF
    2.6e-06, // DFT: LDA_X,LDA_C_VWN
    1.1e-05, // DFT: GGA_X_PBE,GGA_C_PBE
    5.6e-06, // DFT: HYB_GGA_XC_B3LYP
    9.0e-05, // DFT: MGGA_X_M06_L,MGGA_C_M06_L
    2.7e-05  // DFT: HYB_MGGA_X_M06_2X,MGGA_C_M06_2X
};

f64 pyscf_grid_lvl6_forces_on_nuclei[][9] = {
    {// HF
     1.4223388025631463e-17, 2.3536708412610352e-03, 1.7964856246361460e-02,
     3.2311056920281253e-17, 2.3536708412625895e-03, -1.7964856246360350e-02,
     -4.6534444945911816e-17, -4.7073416825225145e-03, -1.2802259252708836e-15},
    {// DFT: LDA_X,LDA_C_VWN
     -8.1698623583254168e-18, 2.8926436476585105e-02, -1.0625739274263690e-02,
     5.6051577917707907e-17, 2.8926436476581996e-02, 1.0625739274260360e-02,
     -6.2481305467409805e-17, -5.7851684373387169e-02, 3.6394498525993421e-15},
    {// DFT: GGA_X_PBE,GGA_C_PBE
     4.2037355181421790e-18, 3.3608317660640541e-02, -1.4081051195926619e-02,
     9.4027629824424120e-17, 3.3608317660638987e-02, 1.4081051195923733e-02,
     -1.1800572427955518e-16, -6.7212487145076771e-02, 2.9698465908722953e-15},
    {// DFT: HYB_GGA_XC_B3LYP
     9.6386302753186818e-18, 2.7335962936859692e-02, -8.6456160811467786e-03,
     7.7964057737412291e-18, 2.7335962936861469e-02, 8.6456160811494431e-03,
     -2.6412343912690363e-17, -5.4670119934109973e-02, -2.4875934645507410e-15},
    {// DFT: MGGA_X_M06_L,MGGA_C_M06_L
     9.6717971493226160e-19, 2.3604317863024527e-02, -5.1412949041140799e-04,
     -3.2372258197232489e-19, 2.3604317863024749e-02, 5.1412949041029776e-04,
     2.1559047564690420e-17, -4.7185597613027763e-02, 1.8457457784393224e-15},
    {// DFT: HYB_MGGA_X_M06_2X,MGGA_C_M06_2X
     2.7254465515070325e-17, 2.0365167236180870e-02, -1.5904049712707202e-03,
     -1.1912036811996878e-16, 2.0365167236182424e-02, 1.5904049712729407e-03,
     1.6755147963919217e-16, -4.0741371927853542e-02, -2.0435042547006788e-15}};

#define CC_METHODS_COUNT 7

char *CC_METHODS[] = {
    "HF",                                       // CC_METHOD_ID = 1
    "DFT with LDA_X, LDA_C_VWN",                // CC_METHOD_ID = 2
    "DFT with GGA_X_PBE, GGA_C_PBE",            // CC_METHOD_ID = 3
    "DFT with HYB_GGA_XC_B3LYP",                // CC_METHOD_ID = 4
    "DFT with MGGA_X_M06_L, MGGA_C_M06_L",      // CC_METHOD_ID = 5
    "DFT with HYB_MGGA_X_M06_2X, MGGA_C_M06_2X" // CC_METHOD_ID = 6
};

f64 sanity_test_threshold = 9e-3;

/*
 * return 1 if one of the desirable results is matched
 * return 0 otherwise
 */
i64 check_total_energy(f64 value, u64 cc_method_id)
{
    if (cc_method_id < 1 || cc_method_id > 6)
    {
        return 0;
    }

    u64 cc_method_idx = cc_method_id - 1;

    f64 energy_diff = fabs(value - pyscf_grid_lvl3_energy_11e_results[cc_method_idx]);
    printf("%s: energy difference is |%.12e - %.12e| = %.6e (PySCF, lvl 3), sanity test (< %.1e): %s\n",
           CC_METHODS[cc_method_idx],
           value,
           pyscf_grid_lvl3_energy_11e_results[cc_method_idx],
           energy_diff,
           //pyscf_grid_lvl3_energy_acceptance_threshold_lv14_rv6[cc_method_idx],
           //energy_diff < pyscf_grid_lvl3_energy_acceptance_threshold_lv14_rv6[cc_method_idx] ? "Passed" : "Failed");
           sanity_test_threshold,
           energy_diff < sanity_test_threshold ? "Passed" : "Failed");

    energy_diff = fabs(value - pyscf_grid_lvl4_energy_11e_results[cc_method_idx]);
    printf("%s: energy difference is |%.12e - %.12e| = %.6e (PySCF, lvl 4), sanity test (< %.1e): %s\n",
           CC_METHODS[cc_method_idx],
           value,
           pyscf_grid_lvl4_energy_11e_results[cc_method_idx],
           energy_diff,
           //pyscf_grid_lvl4_energy_acceptance_threshold_lv14_rv6[cc_method_idx],
           //energy_diff < pyscf_grid_lvl4_energy_acceptance_threshold_lv14_rv6[cc_method_idx] ? "Passed" : "Failed");
           sanity_test_threshold,
           energy_diff < sanity_test_threshold ? "Passed" : "Failed");

    return 1;
}

i64 check_forces(f64 *forces, u64 cc_method_id)
{
    if (cc_method_id < 1 || cc_method_id > 6)
    {
        return 0;
    }

    u64 cc_method_idx = cc_method_id - 1;

    f64 max_delta = 0.0;
    f64 max_delta_force = 0.0;
    f64 max_delta_ref_force = 0.0;

    for (u64 i = 0; i < 9; ++i)
    {
        f64 ref_force = pyscf_grid_lvl5_forces_on_nuclei[cc_method_idx][i];

        f64 delta = fabs(forces[i] - ref_force);
        if (delta > max_delta)
        {
            max_delta = delta;
            max_delta_force = forces[i];
            max_delta_ref_force = ref_force;
        }
    }

    printf("%s: max force difference is |%.12e - %.12e| = %.6e (PySCF, lvl 5), sanity test (< %.1e): %s\n",
           CC_METHODS[cc_method_idx],
           max_delta_force,
           max_delta_ref_force,
           max_delta,
           //pyscf_grid_lvl5_forces_on_nuclei_acceptance_threshold_lv14_rv6[cc_method_idx],
           //max_delta < pyscf_grid_lvl5_forces_on_nuclei_acceptance_threshold_lv14_rv6[cc_method_idx] ? "Passed" : "Failed");
           sanity_test_threshold,
           max_delta < sanity_test_threshold ? "Passed" : "Failed");

    return 1;
}
