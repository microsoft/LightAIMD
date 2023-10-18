#!/usr/bin/env python3
import os
import re
from config import *
from symbols import *

__all__ = ["generate_object_targets", "ObjectTarget", "bfs"]


class ObjectTarget:
    def __init__(self, name, src, target, include_dirs, cuda=False, flags=[]):
        self.name = name
        self.src = src
        self.target = target
        self.include_dirs = include_dirs
        self.cuda = cuda
        self.cpp = src.endswith(".cpp") or src.endswith(".cxx")
        self.flags = flags

    def __str__(self):
        return f"{self.target}"

    def __repr__(self):
        return self.__str__()


header2include_dirs = {
    "xc": "-I${ext_dir}/libxc/include",
}


def expand_string(s):
    if "${" in s:
        for k, v in config.items():
            if isinstance(v, str):
                s = s.replace("${" + k + "}", v)
    return s


def expand_strings(ss):
    return [expand_string(s) for s in ss]


def generate_object_targets():
    if os.path.exists("/usr/include/lapacke"):
        header2include_dirs["lapacke"] = "-I/usr/include/lapacke"

    for k, v in header2include_dirs.items():
        header2include_dirs[k] = expand_string(v)

    fc = 0
    graph = {}
    libgraph = {}
    module_test_executables = []
    executables = []
    object_targets = []
    for root, _, files in os.walk(config["src_dir"]):
        for fname in files:
            if fname.split(".")[-1] in config["SRC_EXTENSIONS"]:
                process_src_file(
                    root,
                    fname,
                    graph,
                    libgraph,
                    object_targets,
                    module_test_executables,
                    executables,
                )
                fc += 1
    print(f"Processed {fc} source files")

    dependencies = {}
    lib_dependencies = {}
    for fname in graph:
        dependencies[fname] = bfs(graph, fname)
        lib_dependencies[fname] = set()
        for f in dependencies[fname]:
            lib_dependencies[fname].update(libgraph.get(f, []))

    _object_targets = []
    for target in object_targets:
        if ".cuda." in target.target:
            if not config["use_cuda"]:
                continue

        for k, v in header2include_dirs.items():
            matched = False
            for lib in lib_dependencies[target.name]:
                if k in lib:
                    matched = True
                    break
            if matched:
                target.include_dirs.append(v)

        _object_targets.append(target)

    return _object_targets


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


def add_to_graph(graph, fname, included_file):
    if fname not in graph:
        graph[fname] = []
    graph[fname].append(included_file)


def process_src_file(
    root, fname, graph, libgraph, object_targets, module_test_executables, executables
):
    is_cuda_file = fname.endswith(".cu")
    fpath = os.path.join(root, fname)
    fstem, ext = os.path.splitext(fname)
    with open(fpath, "r", newline="", encoding="utf-8") as rf:
        for line in rf:
            l = line.strip()
            if l.startswith("#include"):
                m = re.match(r"#include\s*[<\"](.*)([>\"])", l)
                included_file = m.group(1)
                include_file_stem = os.path.splitext(included_file)[0]
                inclusion_type = m.group(2)

                if m:
                    if inclusion_type == ">":
                        add_to_graph(libgraph, fstem, include_file_stem)
                    if inclusion_type == '"':
                        if os.path.exists(os.path.join(root, included_file)):
                            add_to_graph(graph, fstem, include_file_stem)
                        else:
                            add_to_graph(libgraph, fstem, include_file_stem)
            if l.startswith("#ifdef MODULE_TEST"):
                module_test_executables.append(fstem)
                executables.append(fstem)

            if "main" in l or "main" in l:
                m1 = re.match(r"int\s+main\s*\(", l)
                m2 = re.match(r"void\s+main\s*\(", l)
                if m1 is not None or m2 is not None:
                    executables.append(fstem)

            if "__device__" in l or "__global__" in l or "__host__" in l:
                is_cuda_file = True

    non_module_test_executables = [
        e for e in executables if e not in module_test_executables
    ]

    if ext == ".cu":
        if fstem in executables:
            object_target = ObjectTarget(
                fstem,
                fname,
                f"{fstem}.cuda.main.o",
                [],
                cuda=is_cuda_file,
                flags=["-DMODULE_TEST"] if fstem in module_test_executables else [],
            )
            object_targets.append(object_target)
        if fstem not in non_module_test_executables:
            object_target = ObjectTarget(
                fstem, fname, f"{fstem}.cuda.o", [], cuda=is_cuda_file
            )
            object_targets.append(object_target)

    if ext in (".c", ".cpp"):
        if fstem in executables:
            object_target = ObjectTarget(
                fstem,
                fname,
                f"{fstem}.main.o",
                [],
                cuda=is_cuda_file,
                flags=["-DMODULE_TEST"] if fstem in module_test_executables else [],
            )
            object_targets.append(object_target)
        if fstem not in non_module_test_executables:
            object_target = ObjectTarget(
                fstem, fname, f"{fstem}.o", [], cuda=is_cuda_file
            )
            object_targets.append(object_target)

        if is_cuda_file:
            if fstem in executables:
                object_target = ObjectTarget(
                    fstem,
                    fname,
                    f"{fstem}.cuda.main.o",
                    [],
                    cuda=is_cuda_file,
                    flags=["-DMODULE_TEST"] if fstem in module_test_executables else [],
                )
                object_targets.append(object_target)
            if fstem not in non_module_test_executables:
                object_target = ObjectTarget(
                    fstem, fname, f"{fstem}.cuda.o", [], cuda=is_cuda_file
                )
                object_targets.append(object_target)
