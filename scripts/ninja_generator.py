#!/usr/bin/env python3
import os
import subprocess
from config import *
from toolchain import *
from symbols import *
from object_targets import *

__all__ = ["generate_ninja_script"]

ninja_preamble = """ccompiler = {cc}
cppcompiler = {cxx}
nvcc = {nvcc}
compiler = $ccompiler

compile_flags = -O3 -Wall -fPIC -I{src_dir}{cuda_compile_flags}{debug_flags}
extra_compile_flags =
link_flags = -O3 -Wall{cuda_link_flags}{debug_flags}
extra_link_flags =
nvcc_flags = {nvcc_flags}
compile_cu_flags = {compile_cu_flags}{nvcc_debug_flags}
nvcc_extra_compile_flags =
nvcc_link_flags = {nvcc_link_flags}{nvcc_debug_flags}
nvcc_extra_link_flags =

rule compile_c
  command = $ccompiler $compile_flags $extra_compile_flags -c $in -o $out

rule compile_cpp
  command = $cppcompiler $compile_flags $extra_compile_flags -c $in -o $out

rule link_objects
  command = $compiler -o $out $in $link_flags $extra_link_flags

rule compile_cu
  command = $nvcc $nvcc_flags $compile_cu_flags $extra_compile_flags -x cu -dc -o $out $in

rule nvcc_link
  command = $nvcc $nvcc_flags -o $out $in $nvcc_link_flags $extra_link_flags
"""

special_treatment = {
    ## example
    # "cpp_bridge.o": {
    #    "gcc": ["-Wno-maybe-uninitialized"],
    #    "icx": ["-Wno-tautological-constant-compare"],
    # },  # ignore warning from Eigen
    # "cpp_bridge.main.o": {
    #    "gcc": ["-Wno-maybe-uninitialized"],
    #    "icx": ["-Wno-tautological-constant-compare"],
    # },  # ignore warning from Eigen
}


def generate_ninja_script(debug=False):
    def write_ninja_preamble(writer):
        nvcc_flags = f"-ccbin {config['CC']} --allow-unsupported-compiler -Xnvlink --suppress-stack-size-warning"
        debug_flags = " -g" if debug else ""
        nvcc_debug_flags = " -g -G" if debug else ""
        cuda_compile_flags = (
            f" -DUSE_CUDA -I{config['CUDA_INC_DIR']}" if config["use_cuda"] else ""
        )
        cuda_link_flags = (
            f" -L{config['CUDA_LIB_DIR']} -lcudart -lcuda" if config["use_cuda"] else ""
        )
        writer.write(
            ninja_preamble.format(
                cc=config["CC"],
                cxx=config["CXX"],
                nvcc=config["NVCC"],
                src_dir=config["src_dir"],
                cuda_compile_flags=cuda_compile_flags,
                cuda_link_flags=cuda_link_flags,
                nvcc_flags=nvcc_flags,
                compile_cu_flags=cuda_compile_flags,
                nvcc_link_flags=cuda_link_flags,
                debug_flags=debug_flags,
                nvcc_debug_flags=nvcc_debug_flags,
            )
        )
        writer.write("\n")

    def ninja_compile_objects(writer, object_targets):
        for ot in object_targets:
            obj = os.path.join(config["obj_dir"], ot.target)
            input_file = os.path.join(config["src_dir"], ot.src)
            extra_flags = ot.include_dirs + ot.flags

            if ot.target in special_treatment:
                flags = special_treatment[ot.target].get(config["COMPILER"], [])
                extra_flags.extend(flags)

            if config["use_cuda"]:
                extra_flags.append("-DUSE_CUDA")
            if ".cuda." in ot.target:
                if config["use_cuda"]:
                    writer.write(f"build {obj}: compile_cu {input_file}\n")
                    if len(extra_flags) > 0:
                        writer.write(
                            f"  extra_compile_flags = {' '.join(extra_flags)}\n"
                        )
            elif ot.cpp:
                writer.write(f"build {obj}: compile_cpp {input_file}\n")
                if len(extra_flags) > 0:
                    writer.write(f"  extra_compile_flags = {' '.join(extra_flags)}\n")
            else:
                writer.write(f"build {obj}: compile_c {input_file}\n")
                if len(extra_flags) > 0:
                    writer.write(f"  extra_compile_flags = {' '.join(extra_flags)}\n")
        writer.write("\n")

    def ninja_link_objects(
        writer,
        obj2linkdeps,
        obj2libsyms,
        sym2lib,
        lib2libs,
        sym2staticlib,
        staticlib2undefined_sym,
    ):
        for obj in obj2linkdeps.keys():
            if not obj.endswith(".main.o"):
                continue

            cuda_obj = True if ".cuda." in obj else False

            if cuda_obj:
                if not config["use_cuda"]:
                    continue

            deps = bfs(obj2linkdeps, obj)

            target = obj[: -len(".main.o")]

            input_files = []
            for dep in deps:
                input_files.append(os.path.join(config["obj_dir"], dep))
                if ".cuda." in dep:
                    cuda_obj = True

            libs = set()
            static_libs = set()
            undefined = set()
            for dep in deps:
                for uf in obj2libsyms.get(dep, []):
                    if uf in sym2lib:
                        libs |= sym2lib[uf]
                    elif uf in sym2staticlib:
                        static_libs.add(sym2staticlib[uf])
                    else:
                        undefined.add(uf)

            extended_libs = set()
            for lib in libs:
                if lib in lib2libs:
                    extended_libs |= lib2libs[lib]

            libs |= extended_libs

            if len(static_libs) > 0:
                input_files.extend(static_libs)
                for staticlib in static_libs:
                    if ".cuda." in staticlib:
                        cuda_obj = True

                    for uf in staticlib2undefined_sym[staticlib]:
                        if uf in sym2lib:
                            libs |= sym2lib[uf]
                        else:
                            undefined.add(uf)

            extra_flags = (
                ["-Wl,--start-group"]
                + [f"-l{lib}" for lib in libs]
                + ["-Wl,--end-group"]
            )

            if target in special_treatment:
                flags = special_treatment[target].get(config["COMPILER"], [])
                extra_flags.extend(flags)

            if cuda_obj and config["use_cuda"]:
                writer.write(
                    f"build {os.path.join(config['bin_dir'], target)}: nvcc_link {' '.join(input_files)}\n"
                )
            else:
                writer.write(
                    f"build {os.path.join(config['bin_dir'], target)}: link_objects {' '.join(input_files)}\n"
                )

            if len(extra_flags) > 0:
                writer.write(f"  extra_link_flags = {' '.join(extra_flags)}\n")

    def write_ninja_file_obj_targets(ninja_file, object_targets):
        os.makedirs(os.path.dirname(ninja_file), exist_ok=True)
        with open(ninja_file, "w", newline="", encoding="utf-8") as writer:
            write_ninja_preamble(writer)
            ninja_compile_objects(writer, object_targets)
        print(f"Ninja script generation, pass 1: generated {ninja_file}")
        subprocess.run(["ninja", "-f", ninja_file], check=True)

    def write_ninja_file_exe_targets(
        ninja_file,
        object_targets,
        obj2linkdeps,
        obj2libsyms,
        sym2lib,
        lib2libs,
        sym2staticlib,
        staticlib2undefined_sym,
    ):
        os.makedirs(os.path.dirname(ninja_file), exist_ok=True)
        with open(ninja_file, "w", newline="", encoding="utf-8") as writer:
            write_ninja_preamble(writer)
            ninja_compile_objects(writer, object_targets)
            ninja_link_objects(
                writer,
                obj2linkdeps,
                obj2libsyms,
                sym2lib,
                lib2libs,
                sym2staticlib,
                staticlib2undefined_sym,
            )
        print(f"Ninja script generation, pass 2: generated {ninja_file}")

    object_targets = generate_object_targets()
    write_ninja_file_obj_targets(
        os.path.join(config["active_build_dir"], "build.ninja"), object_targets
    )

    sym2obj = {}
    undefined2obj = {}
    obj2undefined = {}
    for ot in object_targets:
        obj_path = os.path.join(config["obj_dir"], ot.target)
        defined_funcs, undefined_funcs = extract_symbols(obj_path)
        obj2undefined[ot.target] = undefined_funcs
        for df in defined_funcs:
            sym2obj[df] = ot.target
        for uf in undefined_funcs:
            if uf not in undefined2obj:
                undefined2obj[uf] = []
            undefined2obj[uf].append(ot.target)

    obj2linkdeps = {}
    obj2libsyms = {}

    for obj, ufs in obj2undefined.items():
        if obj not in obj2linkdeps:
            obj2linkdeps[obj] = set()

        for uf in ufs:
            if uf not in sym2obj:
                if obj not in obj2libsyms:
                    obj2libsyms[obj] = set()
                obj2libsyms[obj].add(uf)

            else:
                obj2linkdeps[obj].add(sym2obj[uf])

    sym2staticlib = {}
    staticlib2undefined_sym = {}
    defined_static_lib_funcs = []
    for static_lib in config["STATIC_LIBS"]:
        defined_static_lib_funcs, undefined_static_lib_funcs = extract_symbols(
            static_lib
        )
        for static_sym in defined_static_lib_funcs:
            sym2staticlib[static_sym] = static_lib
        staticlib2undefined_sym[static_lib] = undefined_static_lib_funcs

    if config["use_cuda"]:
        sym2lib, lib2libs = build_sym2lib_graph(
            config["SHARED_LIBS"] + config["CUDA_SHARED_LIBS"]
        )
    else:
        sym2lib, lib2libs = build_sym2lib_graph(config["SHARED_LIBS"])

    for obj, libsyms in obj2libsyms.items():
        for libsym in libsyms:
            if libsym not in sym2lib and libsym not in defined_static_lib_funcs:
                matched = False
                for rds in config["RUNTIME_DEFINED_SYMS"]:
                    if rds in libsym:
                        matched = True
                        break
                if not matched:
                    print(f"Error: {libsym} not found a matching library")

    write_ninja_file_exe_targets(
        os.path.join(config["active_build_dir"], "build.ninja"),
        object_targets,
        obj2linkdeps,
        obj2libsyms,
        sym2lib,
        lib2libs,
        sym2staticlib,
        staticlib2undefined_sym,
    )
