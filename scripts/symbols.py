#!/usr/bin/env python3
import os
import subprocess
from config import *

__all__ = ["extract_symbols", "build_sym2lib_graph"]


def extract_symbols(obj_file):
    defined_symbols = set()
    undefined_symbols = set()

    if ".cuda." in obj_file:
        cuobjdump_path = config["NVCC"].replace("nvcc", "cuobjdump")
        output = subprocess.run(
            [cuobjdump_path, "-symbols", obj_file], stdout=subprocess.PIPE, check=True
        ).stdout.decode("utf-8")
        output_lines = output.split("\n")
        for line in output_lines:
            l = line.strip()
            if l.startswith("STT_"):
                columns = l.split()
                if columns[-2] == "U":
                    undefined_symbols.add(columns[-1])
                else:
                    defined_symbols.add(columns[-1])

    output = subprocess.run(
        ["nm", "-g", "--no-recurse-limit", obj_file], stdout=subprocess.PIPE, check=True
    ).stdout.decode("utf-8")
    output_lines = output.split("\n")
    for line in output_lines:
        l = line.strip()
        if len(l) == 0:
            continue
        columns = l.split()
        if len(columns) < 2:
            continue
        if columns[-2] == "U":
            undefined_symbols.add(columns[-1])
        else:
            defined_symbols.add(columns[-1])

    defined_funcs = []
    undefined_funcs = []

    for s in defined_symbols:
        if len(s) == 0:
            continue
        if s.find(".") != -1:
            defined_funcs.append(s[: s.find(".")])
        else:
            defined_funcs.append(s)

    for s in undefined_symbols:
        if len(s) == 0:
            continue
        if s.find(".") != -1:
            undefined_funcs.append(s[: s.find(".")])
        else:
            undefined_funcs.append(s)

    return defined_funcs, undefined_funcs


def extract_dynamic_lib_symbols(lib_file):
    output = subprocess.run(
        ["objdump", "-T", lib_file], stdout=subprocess.PIPE, check=True
    ).stdout.decode("utf-8")
    output_lines = output.split("\n")
    found_symbol_table = False
    dynamic_syms = set()
    for line in output_lines:
        l = line.strip()
        if l.startswith("DYNAMIC SYMBOL TABLE"):
            found_symbol_table = True
            continue
        elif not found_symbol_table:
            continue

        if len(l) == 0:
            continue

        if "*UND*" in l:
            continue

        dynamic_syms.add(l.split()[-1])

    return dynamic_syms


def get_ld_search_dir():
    output = subprocess.run(
        ["ld", "--verbose"], stdout=subprocess.PIPE, check=True
    ).stdout.decode("utf-8")
    output_lines = output.split("\n")
    search_dirs = ["/usr/local/cuda/lib64"] if config["use_cuda"] else []
    for line in output_lines:
        l = line.strip()
        if l.startswith("SEARCH_DIR"):
            for sd in l.split(";"):
                d = sd.strip()
                if d.startswith("SEARCH_DIR("):
                    search_dirs.append(d[len('SEARCH_DIR("=') : -len('")')])
    return search_dirs


def get_shared_lib_path(search_dirs, lib):
    for d in search_dirs:
        for root, dirs, files in os.walk(d):
            for f in files:
                if f"lib{lib}.so." in f:
                    return os.path.join(root, f)
    return None


def build_sym2lib_graph(libs):
    search_dirs = get_ld_search_dir()
    sym2lib = {}
    for lib in libs:
        dynamic_syms = extract_dynamic_lib_symbols(
            get_shared_lib_path(search_dirs, lib)
        )
        for sym in dynamic_syms:
            if sym not in sym2lib:
                sym2lib[sym] = set()
            sym2lib[sym].add(lib)
    return sym2lib


if __name__ == "__main__":
    from toolchain import *

    setup_toolchain()
    sym2lib = build_sym2lib_graph(["c", "m"])
    print(sym2lib)
