#!/usr/bin/env python3
import os

__all__ = ["config", "print_config", "expand_string", "expand_strings", "bfs"]

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.dirname(script_dir)
src_dir = os.path.join(root_dir, "src")
ext_dir = os.path.join(root_dir, "ext")

tmp_dir = os.path.join(root_dir, "build", "tmp")
build_root_dir = os.path.join(root_dir, "build")
build_debug_dir = os.path.join(root_dir, "build", "debug")
build_release_dir = os.path.join(root_dir, "build", "release")
test_debug_dir = os.path.join(build_debug_dir, "test")
test_release_dir = os.path.join(build_release_dir, "test")


class Configuration:
    def __init__(self):
        self.user_settings = {
            # library versions
            "LIBXC_VERSION": "6.2.2",
            # build system related
            "SHARED_LIBS": ["c", "m", "pthread", "gcc_s", "stdc++"],
            "RUNTIME_DEFINED_SYMS": [
                "__dso_handle",
                "__tls_get_addr",
                "__cudaRegisterLinkedBinary_",
                "_intel_fast_mem",
                "__svml_",
                "_GLOBAL_OFFSET_TABLE_",
            ],
            "STATIC_LIBS": [],
            "SRC_EXTENSIONS": ["c", "cpp", "cu", "h", "hpp"],
            # cuda related
            "DISABLE_CUDA": False,
            "CUDA_SHARED_LIBS": ["cuda", "cudart"],
            "CUDA_INC_DIR": "/usr/local/cuda/include",
            "CUDA_LIB_DIR": "/usr/local/cuda/lib64",
            # mkl related
            "USE_MKL": False,
            # compiler related
            "COMPILER": "gcc",  # possible values: "clang", "gcc", "icx"
        }

        self.runtime_settings = {
            "script_dir": script_dir,
            "root_dir": root_dir,
            "src_dir": src_dir,
            "ext_dir": ext_dir,
            "tmp_dir": tmp_dir,
            #
            "build_root_dir": build_root_dir,
            "build_debug_dir": build_debug_dir,
            "build_release_dir": build_release_dir,
            "active_build_dir": build_release_dir,
            #
            "test_debug_dir": test_debug_dir,
            "test_release_dir": test_release_dir,
            "active_test_dir": test_release_dir,
            #
            "bin_dir": os.path.join(build_release_dir, "bin"),
            "lib_dir": os.path.join(build_release_dir, "lib"),
            "obj_dir": os.path.join(build_release_dir, "obj"),
            #
            "verbose": False,
            "quiet": False,
            "dry_run": False,
        }

    def __getitem__(self, key):
        if key in self.user_settings:
            return self.user_settings[key]
        elif key in self.runtime_settings:
            return self.runtime_settings[key]
        else:
            raise KeyError(f"Key {key} not found in config")

    def __setitem__(self, key, value):
        if key in self.user_settings:
            self.user_settings[key] = value
        else:
            self.runtime_settings[key] = value

    def items(self):
        return {**self.user_settings, **self.runtime_settings}.items()

    def has_key(self, key):
        return key in self.user_settings or key in self.runtime_settings


config = Configuration()


def expand_string(s):
    if "${" in s:
        for k, v in config.items():
            if isinstance(v, str):
                s = s.replace("${" + k + "}", v)
    return s


def expand_strings(ss):
    return [expand_string(s) for s in ss]


def print_config():
    for k, v in config.items():
        print(f"{k}: {v}")


def bfs(graph, node):
    visited = set()
    queue = []
    queue.append(node)
    while queue:
        s = queue.pop(0)
        visited.add(s)
        for neighbor in graph.get(s, []):
            if neighbor not in visited:
                queue.append(neighbor)
    return visited


if __name__ == "__main__":
    print_config()
