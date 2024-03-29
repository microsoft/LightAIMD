/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#include <stdio.h>
#include "numeric_types.h"

u64 element_shell_count [] = {
    0, // placeholder
    1, // Z: 1
    1, // Z: 2
    2, // Z: 3
    2, // Z: 4
    3, // Z: 5
    3, // Z: 6
    3, // Z: 7
    3, // Z: 8
    3, // Z: 9
    3, // Z: 10
    4, // Z: 11
    4, // Z: 12
    5, // Z: 13
    5, // Z: 14
    5, // Z: 15
    5, // Z: 16
    5, // Z: 17
    5, // Z: 18
    6, // Z: 19
    6, // Z: 20
    7, // Z: 21
    7, // Z: 22
    7, // Z: 23
    7, // Z: 24
    7, // Z: 25
    7, // Z: 26
    7, // Z: 27
    7, // Z: 28
    7, // Z: 29
    7, // Z: 30
    8, // Z: 31
    8, // Z: 32
    8, // Z: 33
    8, // Z: 34
    8, // Z: 35
    8, // Z: 36
    9, // Z: 37
    9, // Z: 38
    10, // Z: 39
    10, // Z: 40
    10, // Z: 41
    10, // Z: 42
    10, // Z: 43
    10, // Z: 44
    10, // Z: 45
    9, // Z: 46
    10, // Z: 47
    10, // Z: 48
    11, // Z: 49
    11, // Z: 50
    11, // Z: 51
    11, // Z: 52
    11, // Z: 53
    11  // Z: 54
};

/*
  For each element, the array contains the number of atomic orbitals for each shell
*/
u64 element_ao_count [][11] = {
    {0}, // placeholder
    {1}, // Z: 1
    {1}, // Z: 2
    {1,1}, // Z: 3
    {1,1}, // Z: 4
    {1,1,3}, // Z: 5
    {1,1,3}, // Z: 6
    {1,1,3}, // Z: 7
    {1,1,3}, // Z: 8
    {1,1,3}, // Z: 9
    {1,1,3}, // Z: 10
    {1,1,3,1}, // Z: 11
    {1,1,3,1}, // Z: 12
    {1,1,3,1,3}, // Z: 13
    {1,1,3,1,3}, // Z: 14
    {1,1,3,1,3}, // Z: 15
    {1,1,3,1,3}, // Z: 16
    {1,1,3,1,3}, // Z: 17
    {1,1,3,1,3}, // Z: 18
    {1,1,3,1,3,1}, // Z: 19
    {1,1,3,1,3,1}, // Z: 20
    {1,1,3,1,3,1,6}, // Z: 21
    {1,1,3,1,3,1,6}, // Z: 22
    {1,1,3,1,3,1,6}, // Z: 23
    {1,1,3,1,3,1,6}, // Z: 24
    {1,1,3,1,3,1,6}, // Z: 25
    {1,1,3,1,3,1,6}, // Z: 26
    {1,1,3,1,3,1,6}, // Z: 27
    {1,1,3,1,3,1,6}, // Z: 28
    {1,1,3,1,3,1,6}, // Z: 29
    {1,1,3,1,3,1,6}, // Z: 30
    {1,1,3,1,3,1,6,3}, // Z: 31
    {1,1,3,1,3,1,6,3}, // Z: 32
    {1,1,3,1,3,1,6,3}, // Z: 33
    {1,1,3,1,3,1,6,3}, // Z: 34
    {1,1,3,1,3,1,6,3}, // Z: 35
    {1,1,3,1,3,1,6,3}, // Z: 36
    {1,1,3,1,3,1,6,3,1}, // Z: 37
    {1,1,3,1,3,1,6,3,1}, // Z: 38
    {1,1,3,1,3,1,6,3,1,6}, // Z: 39
    {1,1,3,1,3,1,6,3,1,6}, // Z: 40
    {1,1,3,1,3,1,6,3,1,6}, // Z: 41
    {1,1,3,1,3,1,6,3,1,6}, // Z: 42
    {1,1,3,1,3,1,6,3,1,6}, // Z: 43
    {1,1,3,1,3,1,6,3,1,6}, // Z: 44
    {1,1,3,1,3,1,6,3,1,6}, // Z: 45
    {1,1,3,1,3,1,6,3,6}, // Z: 46
    {1,1,3,1,3,1,6,3,1,6}, // Z: 47
    {1,1,3,1,3,1,6,3,1,6}, // Z: 48
    {1,1,3,1,3,1,6,3,1,6,3}, // Z: 49
    {1,1,3,1,3,1,6,3,1,6,3}, // Z: 50
    {1,1,3,1,3,1,6,3,1,6,3}, // Z: 51
    {1,1,3,1,3,1,6,3,1,6,3}, // Z: 52
    {1,1,3,1,3,1,6,3,1,6,3}, // Z: 53
    {1,1,3,1,3,1,6,3,1,6,3}  // Z: 54
};

u64 element_electron_distribution [][11] = {
    {0}, // placeholder
    {1}, // Z: 1
    {2}, // Z: 2
    {2,1}, // Z: 3
    {2,2}, // Z: 4
    {2,2,1}, // Z: 5
    {2,2,2}, // Z: 6
    {2,2,3}, // Z: 7
    {2,2,4}, // Z: 8
    {2,2,5}, // Z: 9
    {2,2,6}, // Z: 10
    {2,2,6,1}, // Z: 11
    {2,2,6,2}, // Z: 12
    {2,2,6,2,1}, // Z: 13
    {2,2,6,2,2}, // Z: 14
    {2,2,6,2,3}, // Z: 15
    {2,2,6,2,4}, // Z: 16
    {2,2,6,2,5}, // Z: 17
    {2,2,6,2,6}, // Z: 18
    {2,2,6,2,6,1}, // Z: 19
    {2,2,6,2,6,2}, // Z: 20
    {2,2,6,2,6,2,1}, // Z: 21
    {2,2,6,2,6,2,2}, // Z: 22
    {2,2,6,2,6,2,3}, // Z: 23
    {2,2,6,2,6,1,5}, // Z: 24
    {2,2,6,2,6,2,5}, // Z: 25
    {2,2,6,2,6,2,6}, // Z: 26
    {2,2,6,2,6,2,7}, // Z: 27
    {2,2,6,2,6,2,8}, // Z: 28
    {2,2,6,2,6,1,10}, // Z: 29
    {2,2,6,2,6,2,10}, // Z: 30
    {2,2,6,2,6,2,10,1}, // Z: 31
    {2,2,6,2,6,2,10,2}, // Z: 32
    {2,2,6,2,6,2,10,3}, // Z: 33
    {2,2,6,2,6,2,10,4}, // Z: 34
    {2,2,6,2,6,2,10,5}, // Z: 35
    {2,2,6,2,6,2,10,6}, // Z: 36
    {2,2,6,2,6,2,10,6,1}, // Z: 37
    {2,2,6,2,6,2,10,6,2}, // Z: 38
    {2,2,6,2,6,2,10,6,2,1}, // Z: 39
    {2,2,6,2,6,2,10,6,2,2}, // Z: 40
    {2,2,6,2,6,2,10,6,1,4}, // Z: 41
    {2,2,6,2,6,2,10,6,1,5}, // Z: 42
    {2,2,6,2,6,2,10,6,2,5}, // Z: 43
    {2,2,6,2,6,2,10,6,1,7}, // Z: 44
    {2,2,6,2,6,2,10,6,1,8}, // Z: 45
    {2,2,6,2,6,2,10,6,10}, // Z: 46
    {2,2,6,2,6,2,10,6,1,10}, // Z: 47
    {2,2,6,2,6,2,10,6,2,10}, // Z: 48
    {2,2,6,2,6,2,10,6,2,10,1}, // Z: 49
    {2,2,6,2,6,2,10,6,2,10,2}, // Z: 50
    {2,2,6,2,6,2,10,6,2,10,3}, // Z: 51
    {2,2,6,2,6,2,10,6,2,10,4}, // Z: 52
    {2,2,6,2,6,2,10,6,2,10,5}, // Z: 53
    {2,2,6,2,6,2,10,6,2,10,6}  // Z: 54
};

/* Initializing the density matrix P with Superposition-Of-Atomic-Densities guess */
void soad_initialize_density_matrix(f64* density_matrix, u64 N, u64* atomic_nums, u64 n_atoms)
{
    u64 index = 0;
    for (u64 i = 0; i < n_atoms; ++i)
    {
        u64 Z = atomic_nums[i];
        u64 shell_count = element_shell_count[Z];
        u64* ao_counts = element_ao_count[Z];
        u64* electrons_per_shell = element_electron_distribution[Z];
        for (u64 j = 0; j < shell_count; ++j)
        {
            u64 ao_count = ao_counts[j];
            f64 electrons_per_ao = 0.5 * electrons_per_shell[j] / ao_count;
            for (u64 k = 0; k < ao_count; ++k)
            {
                density_matrix[index * N + index] = electrons_per_ao;
                ++index;
            }
        }
    }
}
