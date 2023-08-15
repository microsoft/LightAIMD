#!/usr/bin/env python3
import os
import subprocess

__all__ = ['config', 'print_config']

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.dirname(script_dir)
src_dir = os.path.join(root_dir, 'src')
ext_dir = os.path.join(root_dir, 'ext')

tmp_dir = os.path.join(root_dir, 'build', 'tmp')
build_root_dir = os.path.join(root_dir, 'build')
build_debug_dir = os.path.join(root_dir, 'build', 'debug')
build_release_dir = os.path.join(root_dir, 'build', 'release')
test_debug_dir = os.path.join(build_debug_dir, 'test')
test_release_dir = os.path.join(build_release_dir, 'test')

config = {
    'CC' : '',
    'CXX' : '',
    'USE_CUDA' : 'NO',
    'NVCC' : '',
    'MODULE_TEST' : '-DMODULE_TEST',
    #
    'NLOHMANN_JSON_VERSION' : '3.11.2',
    'EIGEN_VERSION' : '3.4.0',
    'LIBXC_VERSION' : '6.2.2',
    #
    'script_dir' : script_dir,
    'root_dir' : root_dir,
    'src_dir' : src_dir,
    'ext_dir' : ext_dir,
    'tmp_dir' : tmp_dir,
    #
    'build_root_dir' : build_root_dir,
    'build_debug_dir' : build_debug_dir,
    'build_release_dir' : build_release_dir,
    'active_build_dir' : build_release_dir,
    #
    'test_debug_dir' : test_debug_dir,
    'test_release_dir' : test_release_dir,
    'active_test_dir' : test_release_dir,
    #
    'bin_dir': os.path.join(build_release_dir, 'bin'),
    'lib_dir': os.path.join(build_release_dir, 'lib'),
    'obj_dir': os.path.join(build_release_dir, 'obj')
}

def print_config():
    for k,v in config.items():
        print(f'{k}: {v}')

if __name__ == '__main__':
    print_config()
