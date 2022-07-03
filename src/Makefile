CC=clang -O3 -Wall
CXX=clang++ -O3 -Wall

debug: CC += -g
debug: CXX += -g
debug: all

ROOT_DIR=..
OBJ_DIR=../obj
LIB_DIR=../lib
BIN_DIR=../bin
$(info $(shell mkdir -p $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)))

EXT_INC_DIR=../ext
EIGEN_INC_DIR=../ext/eigen
LIBXC_INC_DIR=../ext/libxc/include
LIBXC_LIB_FILE=../ext/libxc/lib/libxc.a

# -fPIC: If supported for the target machine, emit position-independent code,
# suitable for dynamic linking and avoiding any limit on the size of the global offset table

# $@ the target file name
# $^ the file names of all the prerequisites
# $< the file name of the first prerequisite

.DEFAULT_GOAL := all

OBJECTS = $(OBJ_DIR)/numeric_types.o $(OBJ_DIR)/mm.o $(OBJ_DIR)/scf.o $(OBJ_DIR)/energy_gradient.o $(OBJ_DIR)/special_func.o $(OBJ_DIR)/math_util.o $(OBJ_DIR)/molecular_integral.o $(OBJ_DIR)/elements.o $(OBJ_DIR)/molecule.o $(OBJ_DIR)/f64_util.o $(OBJ_DIR)/sample.o $(OBJ_DIR)/time_util.o $(OBJ_DIR)/soad.o $(OBJ_DIR)/basis_func.o $(OBJ_DIR)/thread_pool.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/vec3d.o $(OBJ_DIR)/functional.o $(OBJ_DIR)/cmd_line_args.o $(OBJ_DIR)/diagnostics.o $(OBJ_DIR)/radial_grid.o $(OBJ_DIR)/einsum.o $(OBJ_DIR)/random.o $(OBJ_DIR)/velocity_init.o $(OBJ_DIR)/thermostat.o $(OBJ_DIR)/md.o $(OBJ_DIR)/io.o $(OBJ_DIR)/dft_matrices.o $(OBJ_DIR)/lebedev_grid.o $(OBJ_DIR)/molecular_grid.o $(OBJ_DIR)/libxc_bridge.o $(LIBXC_LIB_FILE)

all: $(BIN_DIR)/lightaimd $(BIN_DIR)/hf $(BIN_DIR)/dft $(LIB_DIR)/cpp_bridge $(BIN_DIR)/numeric_types $(BIN_DIR)/special_func $(BIN_DIR)/math_util $(BIN_DIR)/molecular_integral $(BIN_DIR)/elements $(BIN_DIR)/molecule $(BIN_DIR)/thread_pool $(BIN_DIR)/time_util $(BIN_DIR)/spinlock $(BIN_DIR)/functional $(BIN_DIR)/vec3d $(BIN_DIR)/libxc_bridge $(BIN_DIR)/basis_func $(BIN_DIR)/diagnostics $(BIN_DIR)/lebedev_grid $(BIN_DIR)/einsum $(BIN_DIR)/random $(BIN_DIR)/velocity_init $(BIN_DIR)/thermostat $(BIN_DIR)/io $(BIN_DIR)/cmd_line_args
	echo "All targets have been made."

.SILENT: all
.PHONY: clean

clean:
	rm -f $(ROOT_DIR)/*.so $(OBJ_DIR)/*.o $(BIN_DIR)/*.so $(BIN_DIR)/*

clean-all:
	rm -f $(ROOT_DIR)/*.so $(OBJ_DIR)/*.o $(BIN_DIR)/*.so $(BIN_DIR)/* $(LIB_DIR)/*

$(LIB_DIR)/cpp_bridge.o: cpp_bridge.cpp cpp_bridge.h
	$(CXX) -fPIC -I$(EXT_INC_DIR) -I$(EIGEN_INC_DIR) -c -o $@ $<

$(LIB_DIR)/cpp_bridge: cpp_bridge.cpp cpp_bridge.h
	$(CXX) -DMODULE_TEST -I$(EXT_INC_DIR) -I$(EIGEN_INC_DIR) -o $@ $< $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o

$(OBJ_DIR)/libxc_bridge.o: libxc_bridge.c libxc_bridge.h
	$(CC) -fPIC -c -I$(LIBXC_INC_DIR) -o $@ $<

$(OBJ_DIR)/%.o: %.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/lightaimd: $(OBJ_DIR)/lightaimd.o $(OBJ_DIR)/hf.o $(OBJ_DIR)/dft.o $(LIB_DIR)/cpp_bridge.o $(OBJECTS)
	$(CC) -lm -lstdc++ -lpthread -o $@ $^

$(BIN_DIR)/hf: $(LIB_DIR)/cpp_bridge.o $(OBJECTS)
	$(CC) -DMODULE_TEST -lm -lstdc++ -lpthread -o $@ hf.c $^

$(BIN_DIR)/dft: $(LIB_DIR)/cpp_bridge.o $(OBJECTS)
	$(CC) -DMODULE_TEST -lm -lstdc++ -lpthread -o $@ dft.c $^

$(BIN_DIR)/libxc_bridge: libxc_bridge.c $(LIBXC_LIB_FILE) $(OBJ_DIR)/diagnostics.o $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/f64_util.o
	$(CC) -DMODULE_TEST -I$(LIBXC_INC_DIR) -lm -o $@ $^

$(BIN_DIR)/cmd_line_args: cmd_line_args.c $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/sample.o $(OBJ_DIR)/elements.o $(OBJ_DIR)/molecule.o $(OBJ_DIR)/io.o
	$(CC) -DMODULE_TEST -o $@ $^

$(BIN_DIR)/special_func: special_func.c $(OBJ_DIR)/diagnostics.o $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/f64_util.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(BIN_DIR)/math_util: math_util.c $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(BIN_DIR)/molecular_integral: molecular_integral.c $(OBJ_DIR)/special_func.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(BIN_DIR)/molecule: molecule.c $(OBJ_DIR)/elements.o $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/io.o
	$(CC) -DMODULE_TEST -o $@ $^

$(BIN_DIR)/basis_func: basis_func.c $(OBJ_DIR)/vec3d.o $(OBJ_DIR)/special_func.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(BIN_DIR)/lebedev_grid: lebedev_grid.c $(OBJ_DIR)/diagnostics.o $(OBJ_DIR)/f64_util.o $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(BIN_DIR)/thread_pool: thread_pool.c $(LIB_DIR)/cpp_bridge.o $(OBJ_DIR)/time_util.o $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o
	$(CC) -DMODULE_TEST -lm -lstdc++ -lpthread -o $@ $^

$(BIN_DIR)/diagnostics: diagnostics.c $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/f64_util.o $(OBJ_DIR)/time_util.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(BIN_DIR)/einsum: einsum.c $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/thread_pool.o $(LIB_DIR)/cpp_bridge.o $(OBJ_DIR)/time_util.o
	$(CC) -DMODULE_TEST -lm -lpthread -lstdc++ -o $@ $^

$(BIN_DIR)/velocity_init: velocity_init.c $(OBJ_DIR)/mm.o $(OBJ_DIR)/random.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/molecule.o $(OBJ_DIR)/elements.o $(OBJ_DIR)/thermostat.o $(OBJ_DIR)/io.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(BIN_DIR)/thermostat: thermostat.c $(OBJ_DIR)/mm.o $(OBJ_DIR)/random.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/molecule.o $(OBJ_DIR)/elements.o $(OBJ_DIR)/velocity_init.o $(OBJ_DIR)/io.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(BIN_DIR)/functional $(BIN_DIR)/random: $(BIN_DIR)/% : %.c
	$(CC) -DMODULE_TEST -lm -o $@ $<

$(BIN_DIR)/%: %.c
	$(CC) -DMODULE_TEST -o $@ $<
