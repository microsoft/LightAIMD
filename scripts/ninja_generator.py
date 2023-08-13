#!/usr/bin/env python3
import os
from config import *
from toolchain import *

__all__ = ['generate_ninja_script']

ninja_preamble ="""ccompiler = {CC}
cppcompiler = {CXX}
compiler = $ccompiler

compile_flags = -O3 -Wall -fPIC -I{src_dir}{debug_flags}
extra_compile_flags =
link_flags = -O3 -Wall{debug_flags}
extra_link_flags =

rule compile_c
  command = $ccompiler $compile_flags $extra_compile_flags -c $in -o $out

rule compile_cpp
  command = $cppcompiler $compile_flags $extra_compile_flags -c $in -o $out

rule make_executable
  command = $compiler $link_flags $extra_link_flags -o $out $in
"""

def generate_ninja_script(object_targets={}, executable_targets={}, debug=False):
    def write_ninja_preamble(writer):
        debug_flags = ' -g' if debug else ''
        writer.write(ninja_preamble.format(CC=config['CC'], CXX=config['CXX'], src_dir=config['src_dir'], debug_flags=debug_flags))
        writer.write("\n")

    def expand_string(s):
        if '${' in s:
            for k, v in config.items():
                s = s.replace('${' + k + '}', v)
        return s

    def expand_strings(ss):
        return [expand_string(s) for s in ss]

    for k, v in object_targets.items():
        object_targets[k] = expand_string(v)

    for k, v in executable_targets.items():
        executable_targets[k] = (expand_strings(v[0]), expand_string(v[1]))

    def ninja_compile_objects(writer, src_dir, obj_dir, extensions):
        for f in walk_src(src_dir, extensions):
            basename = os.path.basename(f)
            stem, ext = os.path.splitext(basename)

            obj = os.path.join(obj_dir, f'{stem}.o')
            writer.write(f"build {obj}: compile_{ext[1:]} {f}\n")

            if os.path.basename(obj) in object_targets:
                writer.write(f"  extra_compile_flags = {object_targets[os.path.basename(obj)]}\n")
        writer.write("\n")

    def ninja_make_executables(writer, src_dir, bin_dir, extensions):
        for filename, (files, flags) in executable_targets.items():

            input_files = []
            cpp = False
            for f in files:
                if '/' in f:
                    input_files.append(f)
                elif f.endswith('.o'):
                    input_files.append(os.path.join(config['obj_dir'], f))
                else:
                    input_files.append(os.path.join(config['src_dir'], f))
                if f.endswith('.cpp'):
                    cpp = True

            writer.write(f"build {os.path.join(bin_dir, filename)}: make_executable {' '.join(input_files)}\n")
            writer.write(f"  extra_link_flags = {flags}\n")
            if cpp:
                writer.write(f"  compiler = $cppcompiler\n")

    def walk_src(src_dir, extensions):
        for root, dirs, files in os.walk(src_dir):
            for f in files:
                if f.split('.')[-1] in extensions:
                    yield os.path.join(root, f)

    def write_ninja_file(ninja_file, src_dir, obj_dir, bin_dir, extensions):
        os.makedirs(os.path.dirname(ninja_file), exist_ok=True)
        with open(ninja_file, 'w', newline='', encoding='utf-8') as writer:
            write_ninja_preamble(writer)
            ninja_compile_objects(writer, src_dir, obj_dir, extensions)
            ninja_make_executables(writer, src_dir, bin_dir, extensions)
        print(f'Generated {ninja_file}')

    write_ninja_file(os.path.join(config['active_build_dir'], 'build.ninja'), config['src_dir'], config['obj_dir'], config['bin_dir'], ['c', 'cpp'])

if __name__ == '__main__':
    setup_toolchain()
    generate_ninja_script()
