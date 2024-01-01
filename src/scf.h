/*
 * Copyright (c) Microsoft Corporation.
 * Licensed under the MIT License.
 */
#ifndef SCF_H
#define SCF_H
#include <float.h>
#include "numeric_types.h"
#include "molecule.h"
#include "thread_pool.h"
#include "basis_func.h"
#include "cli_args.h"

struct scf_context
{
    struct molecule* mol;
    /* Number of basis functions: N */
    u64 n_basis_funcs;
    u64 N2;
    u64 N2_f64;
    struct basis_func* basis_funcs;
    char* basis_funcs_buff;

    /* Core Hamiltonian operator H = T + V, (N, N) */
    f64* H;

    /* Overlap matrix */
    f64* S;

    /* Fock matrix */
    f64* F;

    /* Two-electron integrals, (N, N, N, N) */
    f64* TwoE;

    /* derivatives with respect to atomic coordinates*/
    f64* dS;
    f64* dT;
    f64* dV;
    f64* dH;
    f64* dTwoE;
    f64* dJ;
    f64* dK;
    f64* dF;

    /* n_atom X n_bf */
    u32* atom_bf_map;

    /* Coefficient matrix */
    f64* C;
    /* Occupied orbital slice of the coefficient matrix */
    f64* COO;
    /* Transpose of COO */
    f64* COOT;

    /* Charge density matrix */
    f64* P;
    /* Charge density matrix of last SCF iteration */
    f64* P_last;
    /* RMSD of the diff of P and P_last */
    f64 density_rmsd;
    /* flag indicating the guess scheme used for initializing density matrix */
    u64 density_init_method;

    /* Total electronic energy */
    f64 energy;
    /* Total electronic energy of last SCF iteration */
    f64 energy_last;
    /* Delta between energy and energy_last */
    f64 delta_energy;

    u64 n_max_iteration;
    f64 JK_screening_threshold;
    f64 converge_threshold;
    u64 converged;

    f64 nuclear_repulsion_energy;

    u64 direct_scf;
    u64 damping;

    struct threadpool_context* tp_ctx;
    /* Spinlock array */
    volatile atomic_bool* LOCK;
    f64* ScreeningMatrix;

    /* DIIS */
    u64 diis_subspace_size;
    u64 diis_ring_buff_head;
    u64 diis_history_size;
    f64* diis_fock_matrices;  // ring buffer
    f64* diis_error_matrices;  // ring buffer
    f64* diis_FPS;
    f64* diis_SPF;
    f64* diis_B;
    f64* diis_ordinate_vector;
    f64* diis_coefficients;
    f64* diis_F;

    /* Damping */
    f64 damping_factor;

    /* A preallocated temp matrix buffer (N, N) */
    f64* NxN_1;
    f64* NxN_2;
    f64* NxN_3;

    struct dft_context* dft_ctx;

    u64 silent;
};

extern const u64 DENSITY_INIT_SOAD;
extern const u64 DENSITY_INIT_HCORE;
extern const u64 DENSITY_INIT_USER_PROVIDED;
extern const u64 CC_METHOD_HF;
extern const u64 CC_METHOD_DFT;
typedef void (*scf_config_func_pointer)(struct scf_context*);

void print_basis_func_struct(struct basis_func* bf);
void print_scf_context(struct scf_context* ctx);
void free_basis(struct scf_context* ctx);
struct scf_context* scf_initialize(struct cmd_line_args* args, scf_config_func_pointer config_func);
void diis_update_fock(struct scf_context* ctx);
void scf_finalize(struct scf_context* ctx);
#endif
