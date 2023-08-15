#!/usr/bin/env python3
import os
from config import *
from toolchain import *
from targets import *

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
nvcc_compile_flags = {nvcc_compile_flags}{nvcc_debug_flags}
nvcc_extra_compile_flags =
nvcc_link_flags = {nvcc_link_flags}{nvcc_debug_flags}
nvcc_extra_link_flags =

rule compile_c
  command = $ccompiler $compile_flags $extra_compile_flags -c $in -o $out

rule compile_cpp
  command = $cppcompiler $compile_flags $extra_compile_flags -c $in -o $out

rule make_executable
  command = $compiler $link_flags $extra_link_flags -o $out $in

rule nvcc_compile
  command = $nvcc $nvcc_flags $nvcc_compile_flags $extra_compile_flags -x cu -dc -o $out $in

rule nvcc_link
  command = $nvcc $nvcc_flags $nvcc_link_flags $extra_link_flags -o $out $in
"""


def generate_ninja_script(debug=False):
    def write_ninja_preamble(writer):
        nvcc_flags = f"-ccbin {config['CC']} --allow-unsupported-compiler -Xnvlink --suppress-stack-size-warning"

        debug_flags = " -g" if debug else ""
        nvcc_debug_flags = " -g -G" if debug else ""
        cuda_compile_flags = (
            " -DUSE_CUDA -I/usr/local/cuda/include"
            if config["USE_CUDA"] == "YES"
            else ""
        )
        cuda_link_flags = (
            " -L/usr/local/cuda/lib64 -lcudart -lcuda"
            if config["USE_CUDA"] == "YES"
            else ""
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
                nvcc_compile_flags=cuda_compile_flags,
                nvcc_link_flags=cuda_link_flags,
                debug_flags=debug_flags,
                nvcc_debug_flags=nvcc_debug_flags,
            )
        )
        writer.write("\n")

    def expand_string(s):
        if "${" in s:
            for k, v in config.items():
                s = s.replace("${" + k + "}", v)
        return s

    def expand_strings(ss):
        return [expand_string(s) for s in ss]

    for k, v in object_targets.items():
        object_targets[k] = expand_string(v)

    for k, v in cuda_object_targets.items():
        cuda_object_targets[k] = (expand_string(v[0]), expand_string(v[1]))

    for k, v in executable_targets.items():
        executable_targets[k] = (expand_strings(v[0]), expand_string(v[1]))

    for k, v in cuda_executable_targets.items():
        cuda_executable_targets[k] = (expand_strings(v[0]), expand_string(v[1]))

    def ninja_compile_objects(writer, extensions):
        for f in walk_src(config["src_dir"], extensions):
            basename = os.path.basename(f)
            stem, ext = os.path.splitext(basename)

            obj = os.path.join(config["obj_dir"], f"{stem}.o")
            writer.write(f"build {obj}: compile_{ext[1:]} {f}\n")

            if os.path.basename(obj) in object_targets:
                writer.write(
                    f"  extra_compile_flags = {object_targets[os.path.basename(obj)]}\n"
                )
        writer.write("\n")

    def ninja_compile_cuda_objects(writer):
        for target, (input_file, flags) in cuda_object_targets.items():
            writer.write(
                f"build {os.path.join(config['obj_dir'], target)}: nvcc_compile {os.path.join(config['src_dir'], input_file)}\n"
            )
            if flags != "":
                writer.write(f"  extra_compile_flags = {flags}\n")

    def ninja_make_executables(writer):
        for target, (files, flags) in executable_targets.items():
            if (config["USE_CUDA"] == "YES") and (target in cuda_executable_targets):
                continue

            input_files = []
            cpp = False
            for f in files:
                if "/" in f:
                    input_files.append(f)
                elif f.endswith(".o"):
                    input_files.append(os.path.join(config["obj_dir"], f))
                else:
                    input_files.append(os.path.join(config["src_dir"], f))
                if f.endswith(".cpp"):
                    cpp = True

            writer.write(
                f"build {os.path.join(config['bin_dir'], target)}: make_executable {' '.join(input_files)}\n"
            )
            writer.write(f"  extra_link_flags = {flags}\n")
            if cpp:
                writer.write(f"  compiler = $cppcompiler\n")

    def ninja_make_cuda_executables(writer):
        for target, (files, flags) in cuda_executable_targets.items():
            input_files = []
            for f in files:
                if "/" in f:
                    input_files.append(f)
                elif f.endswith(".o"):
                    input_files.append(os.path.join(config["obj_dir"], f))
                else:
                    input_files.append(os.path.join(config["src_dir"], f))

            writer.write(
                f"build {os.path.join(config['bin_dir'], target)}: nvcc_link {' '.join(input_files)}\n"
            )
            writer.write(f"  extra_link_flags = {flags}\n")

    def walk_src(src_dir, extensions):
        for root, dirs, files in os.walk(src_dir):
            for f in files:
                if f.split(".")[-1] in extensions:
                    yield os.path.join(root, f)

    def write_ninja_file(ninja_file, extensions):
        os.makedirs(os.path.dirname(ninja_file), exist_ok=True)
        with open(ninja_file, "w", newline="", encoding="utf-8") as writer:
            write_ninja_preamble(writer)
            ninja_compile_objects(writer, extensions)
            ninja_make_executables(writer)
            if config["USE_CUDA"] == "YES":
                ninja_compile_cuda_objects(writer)
                ninja_make_cuda_executables(writer)
        print(f"Generated {ninja_file}")

    write_ninja_file(
        os.path.join(config["active_build_dir"], "build.ninja"), ["c", "cpp"]
    )


if __name__ == "__main__":
    setup_toolchain()
    generate_ninja_script()
