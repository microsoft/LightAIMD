#!/usr/bin/env python3
import os
from config import *

# 'target_name': 'compilation_flags'
object_targets = {
    'libxc_bridge.o': "-I${ext_dir}/libxc/include",
    'cpp_bridge.o': "-I${ext_dir} -I${ext_dir}/eigen"
}

# 'target_name': (['source_file1', 'source_file2', ...], 'compilation_flags')
executable_targets = {
    # -DMODULE_TEST
    "numeric_types": (['numeric_types.c'], "-DMODULE_TEST"),
    "io": (['io.c'], "-DMODULE_TEST"),
    "elements": (['elements.c'], "-DMODULE_TEST"),
    "time_util": (['time_util.c'], "-DMODULE_TEST"),
    "spinlock": (['spinlock.c'], "-DMODULE_TEST"),
    "vec3d": (['vec3d.c'], "-DMODULE_TEST"),

    # -DMODULE_TEST -lm
    "functional": (['functional.c'], "-DMODULE_TEST -lm"),
    "random": (['random.c'], "-DMODULE_TEST -lm"),

    # -DMODULE_TEST
    "molecule": (['molecule.c', 'elements.o', 'mm.o', 'spinlock.o', 'io.o'], "-DMODULE_TEST"),
    "cmd_line_args": (['cmd_line_args.c', 'mm.o', 'spinlock.o', 'sample.o', 'elements.o', 'molecule.o', 'io.o'], "-DMODULE_TEST"),

    # -DMODULE_TEST -lm
    "math_util": (['math_util.c', 'mm.o', 'spinlock.o'], "-DMODULE_TEST -lm"),
    "basis_func": (['basis_func.c', 'vec3d.o', 'special_func.o'], "-DMODULE_TEST -lm"),
    "molecular_integral": (['molecular_integral.c', 'special_func.o'], "-DMODULE_TEST -lm"),
    "diagnostics": (['diagnostics.c', 'mm.o', 'spinlock.o', 'f64_util.o', 'time_util.o'], "-DMODULE_TEST -lm"),
    "lebedev_grid": (['lebedev_grid.c', 'diagnostics.o', 'f64_util.o', 'mm.o', 'spinlock.o'], "-DMODULE_TEST -lm"),
    "velocity_init": (['velocity_init.c', 'mm.o', 'random.o', 'spinlock.o', 'molecule.o', 'elements.o', 'thermostat.o', 'io.o'], "-DMODULE_TEST -lm"),
    "thermostat": (['thermostat.c', 'mm.o', 'random.o', 'spinlock.o', 'molecule.o', 'elements.o', 'velocity_init.o', 'io.o'], "-DMODULE_TEST -lm"),
    "standard_grid": (['standard_grid.c', 'cmd_line_args.o', 'mm.o', 'spinlock.o', 'sample.o', 'elements.o', 'molecule.o', 'io.o'], "-DMODULE_TEST -lm"),
    "special_func": (['special_func.c', 'diagnostics.o', 'mm.o', 'spinlock.o', 'f64_util.o'], "-DMODULE_TEST -lm"),

    # -DMODULE_TEST -lm -lstdc++ -lpthread
    "hf": (['hf.c', 'cpp_bridge.o', 'numeric_types.o', 'mm.o', 'scf.o', 'energy_gradient.o', 'special_func.o', 'math_util.o', 'molecular_integral.o', 'elements.o', 'molecule.o', 'f64_util.o', 'sample.o', 'time_util.o', 'soad.o', 'basis_func.o', 'thread_pool.o', 'spinlock.o', 'vec3d.o', 'functional.o', 'cmd_line_args.o', 'diagnostics.o', 'radial_grid.o', 'einsum.o', 'random.o', 'velocity_init.o', 'thermostat.o', 'md.o', 'io.o', 'dft_matrices.o', 'lebedev_grid.o', 'molecular_grid.o', 'libxc_bridge.o', 'cuda_helper.o', 'standard_grid.o', '${ext_dir}/libxc/lib/libxc.a'], "-DMODULE_TEST -lm -lstdc++ -lpthread"),
    "dft": (['dft.c', 'cpp_bridge.o', 'numeric_types.o', 'mm.o', 'scf.o', 'energy_gradient.o', 'special_func.o', 'math_util.o', 'molecular_integral.o', 'elements.o', 'molecule.o', 'f64_util.o', 'sample.o', 'time_util.o', 'soad.o', 'basis_func.o', 'thread_pool.o', 'spinlock.o', 'vec3d.o', 'functional.o', 'cmd_line_args.o', 'diagnostics.o', 'radial_grid.o', 'einsum.o', 'random.o', 'velocity_init.o', 'thermostat.o', 'md.o', 'io.o', 'dft_matrices.o', 'lebedev_grid.o', 'molecular_grid.o', 'libxc_bridge.o', 'cuda_helper.o', 'standard_grid.o', '${ext_dir}/libxc/lib/libxc.a'], "-DMODULE_TEST -lm -lstdc++ -lpthread"),
    "thread_pool": (['thread_pool.c', 'cpp_bridge.o', 'time_util.o', 'mm.o', 'spinlock.o'], "-DMODULE_TEST -lm -lstdc++ -lpthread"),
    "einsum": (['einsum.c', 'mm.o', 'spinlock.o', 'thread_pool.o', 'cpp_bridge.o', 'time_util.o'], "-DMODULE_TEST -lm -lstdc++ -lpthread"),

    # -DMODULE_TEST -lm -I${ext_dir}/libxc/include
    "libxc_bridge": (['libxc_bridge.c', 'diagnostics.o', 'mm.o', 'spinlock.o', 'f64_util.o', '${ext_dir}/libxc/lib/libxc.a'], "-DMODULE_TEST -lm -I${ext_dir}/libxc/include"),

    # -DMODULE_TEST -I${ext_dir} -I${ext_dir}/eigen
    "cpp_bridge": (['cpp_bridge.cpp', 'mm.o', 'spinlock.o'], "-DMODULE_TEST -I${ext_dir} -I${ext_dir}/eigen"),

    # -lm -lstdc++ -lpthread
    "lightaimd": (['lightaimd.o', 'hf.o', 'dft.o', 'cpp_bridge.o', 'numeric_types.o', 'mm.o', 'scf.o', 'energy_gradient.o', 'special_func.o', 'math_util.o', 'molecular_integral.o', 'elements.o', 'molecule.o', 'f64_util.o', 'sample.o', 'time_util.o', 'soad.o', 'basis_func.o', 'thread_pool.o', 'spinlock.o', 'vec3d.o', 'functional.o', 'cmd_line_args.o', 'diagnostics.o', 'radial_grid.o', 'einsum.o', 'random.o', 'velocity_init.o', 'thermostat.o', 'md.o', 'io.o', 'dft_matrices.o', 'lebedev_grid.o', 'molecular_grid.o', 'libxc_bridge.o', 'cuda_helper.o', 'standard_grid.o', '${ext_dir}/libxc/lib/libxc.a'], "-lm -lstdc++ -lpthread"),
}
