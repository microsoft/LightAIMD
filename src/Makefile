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
EIGEN_INC_DIR=../ext/eigen-3.4.0
LIBXC_INC_DIR=../ext/libxc-5.2.2/libxc/include
LIBXC_LIB_FILE=../ext/libxc-5.2.2/libxc/lib/libxc.a

# -fPIC: If supported for the target machine, emit position-independent code,
# suitable for dynamic linking and avoiding any limit on the size of the global offset table

# $@ the target file name
# $^ the file names of all the prerequisites
# $< the file name of the first prerequisite

.DEFAULT_GOAL := all

OBJECTS = $(OBJ_DIR)/numeric_types.o $(OBJ_DIR)/mm.o $(OBJ_DIR)/scf.o $(OBJ_DIR)/energy_gradient.o $(OBJ_DIR)/special_func.o $(OBJ_DIR)/math_util.o $(OBJ_DIR)/molecular_integral.o $(OBJ_DIR)/elements.o $(OBJ_DIR)/molecule.o $(OBJ_DIR)/f64_util.o $(OBJ_DIR)/sample.o $(OBJ_DIR)/time_util.o $(OBJ_DIR)/soad.o $(OBJ_DIR)/basis_func.o $(OBJ_DIR)/thread_pool.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/vec3d.o $(OBJ_DIR)/functional.o $(OBJ_DIR)/cmd_line_args.o $(OBJ_DIR)/diagnostics.o $(OBJ_DIR)/radial_grid.o $(OBJ_DIR)/einsum.o $(OBJ_DIR)/random.o $(OBJ_DIR)/velocity_init.o $(OBJ_DIR)/thermostat.o $(OBJ_DIR)/md.o $(OBJ_DIR)/io.o $(OBJ_DIR)/dft_matrices.o $(LIB_DIR)/cpp_bridge.o $(OBJ_DIR)/lebedev_grid.o $(OBJ_DIR)/molecular_grid.o $(OBJ_DIR)/libxc_bridge.o $(LIBXC_LIB_FILE)

$(OBJ_DIR)/hf.main.o: hf.main.c
	$(CC) -c -o $@ $<

$(ROOT_DIR)/hf.exe: $(OBJ_DIR)/hf.main.o $(OBJECTS)
	$(CC) -lm -lstdc++ -lpthread -o $@ $^

$(ROOT_DIR)/dft.exe: $(OBJ_DIR)/dft.main.o $(OBJECTS)
	$(CC) -lm -lstdc++ -lpthread -o $@ $^

all: $(ROOT_DIR)/hf.exe $(ROOT_DIR)/dft.exe $(LIB_DIR)/cpp_bridge.exe $(BIN_DIR)/numeric_types.exe $(BIN_DIR)/special_func.exe $(BIN_DIR)/math_util.exe $(BIN_DIR)/molecular_integral.exe $(BIN_DIR)/elements.exe $(BIN_DIR)/molecule.exe $(BIN_DIR)/thread_pool.exe $(BIN_DIR)/time_util.exe $(BIN_DIR)/spinlock.exe $(BIN_DIR)/functional.exe $(BIN_DIR)/vec3d.exe $(BIN_DIR)/libxc_bridge.exe $(BIN_DIR)/basis_func.exe $(BIN_DIR)/diagnostics.exe $(BIN_DIR)/lebedev_grid.exe $(BIN_DIR)/einsum.exe $(BIN_DIR)/random.exe $(BIN_DIR)/velocity_init.exe $(BIN_DIR)/thermostat.exe $(BIN_DIR)/io.exe
	echo "All targets have been made."

.SILENT: all
.PHONY: clean

clean:
	rm -f $(ROOT_DIR)/*.so $(ROOT_DIR)/*.exe $(OBJ_DIR)/*.o $(BIN_DIR)/*.so $(BIN_DIR)/*.exe

clean-all:
	rm -f $(ROOT_DIR)/*.so $(ROOT_DIR)/*.exe $(OBJ_DIR)/*.o $(BIN_DIR)/*.so $(BIN_DIR)/*.exe $(LIB_DIR)/*

$(OBJ_DIR)/numeric_types.o: numeric_types.c numeric_types.h
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/numeric_types.exe: numeric_types.c numeric_types.h
	$(CC) -DMODULE_TEST -o $@ $<

$(OBJ_DIR)/mm.o: mm.c mm.h
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/libxc_bridge.o: libxc_bridge.c libxc_bridge.h
	$(CC) -fPIC -c -I$(LIBXC_INC_DIR) -o $@ $<

$(BIN_DIR)/libxc_bridge.exe: libxc_bridge.c libxc_bridge.h
	$(CC) -DMODULE_TEST -I$(LIBXC_INC_DIR) -lm -o $@ $< $(LIBXC_LIB_FILE) $(OBJ_DIR)/diagnostics.o $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/f64_util.o

$(OBJ_DIR)/special_func.o: special_func.c
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/cmd_line_args.o: cmd_line_args.c cmd_line_args.h
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/special_func.exe: special_func.c
	$(CC) -DMODULE_TEST -lm -o $@ $< $(OBJ_DIR)/diagnostics.o $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/f64_util.o

$(OBJ_DIR)/math_util.o: math_util.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/math_util.exe: math_util.c
	$(CC) -DMODULE_TEST -lm -o $@ $< $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o

$(OBJ_DIR)/molecular_integral.o: molecular_integral.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/molecular_integral.exe: molecular_integral.c $(OBJ_DIR)/special_func.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(OBJ_DIR)/elements.o: elements.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/elements.exe: elements.c
	$(CC) -DMODULE_TEST -o $@ $<

$(OBJ_DIR)/molecule.o: molecule.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/molecule.exe: molecule.c $(OBJ_DIR)/elements.o $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/io.o
	$(CC) -DMODULE_TEST -o $@ $^

$(OBJ_DIR)/functional.o: functional.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/functional.exe: functional.c
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(OBJ_DIR)/f64_util.o: f64_util.c f64_util.h
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/sample.o: sample.c
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/time_util.o: time_util.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/time_util.exe: time_util.c
	$(CC) -DMODULE_TEST -o $@ $^

$(OBJ_DIR)/vec3d.o: vec3d.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/vec3d.exe: vec3d.c
	$(CC) -DMODULE_TEST -o $@ $^

$(OBJ_DIR)/basis_func.o: basis_func.c
	$(CC) -fPIC -c -o $@ $^

$(BIN_DIR)/basis_func.exe: basis_func.c $(OBJ_DIR)/vec3d.o $(OBJ_DIR)/special_func.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(OBJ_DIR)/spinlock.o: spinlock.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/spinlock.exe: spinlock.c
	$(CC) -DMODULE_TEST -o $@ $^

$(OBJ_DIR)/soad.o: soad.c soad.h
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/lebedev_grid.o: lebedev_grid.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/lebedev_grid.exe: lebedev_grid.c $(OBJ_DIR)/diagnostics.o $(OBJ_DIR)/f64_util.o
	$(CC) -DMODULE_TEST -lm -o $@ $^ $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o

$(OBJ_DIR)/dft_matrices.o: dft_matrices.c dft_matrices.h
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/molecular_grid.o: molecular_grid.c molecular_grid.h
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/radial_grid.o: radial_grid.c radial_grid.h
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/scf.o: scf.c scf.h
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/energy_gradient.o: energy_gradient.c energy_gradient.h
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/dft.main.o: dft.main.c dft.h
	$(CC) -fPIC -c -o $@ $<

$(LIB_DIR)/cpp_bridge.o: cpp_bridge.cpp cpp_bridge.h
	$(CXX) -fPIC -I$(EXT_INC_DIR) -I$(EIGEN_INC_DIR) -c -o $@ $<

$(LIB_DIR)/cpp_bridge.exe: cpp_bridge.cpp cpp_bridge.h
	$(CXX) -DMODULE_TEST -I$(EXT_INC_DIR) -I$(EIGEN_INC_DIR) -o $@ $< $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o

$(OBJ_DIR)/thread_pool.o: thread_pool.c thread_pool.h
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/thread_pool.exe: thread_pool.c $(LIB_DIR)/cpp_bridge.o $(OBJ_DIR)/time_util.o
	$(CC) -DMODULE_TEST -lm -lstdc++ -lpthread -o $@ $^ $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o

$(OBJ_DIR)/diagnostics.o: diagnostics.c
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/diagnostics.exe: diagnostics.c
	$(CC) -DMODULE_TEST -lm -o $@ $< $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/f64_util.o $(OBJ_DIR)/time_util.o

$(OBJ_DIR)/einsum.o: einsum.c einsum.h
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/einsum.exe: einsum.c einsum.h
	$(CC) -DMODULE_TEST -lm -lpthread -lstdc++ -o $@ $< $(OBJ_DIR)/mm.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/thread_pool.o $(LIB_DIR)/cpp_bridge.o $(OBJ_DIR)/time_util.o

$(OBJ_DIR)/random.o: random.c random.h
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/random.exe: random.c random.h
	$(CC) -DMODULE_TEST -lm -o $@ $<

$(OBJ_DIR)/velocity_init.o: velocity_init.c velocity_init.h
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/velocity_init.exe: velocity_init.c $(OBJ_DIR)/mm.o $(OBJ_DIR)/random.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/molecule.o $(OBJ_DIR)/elements.o $(OBJ_DIR)/thermostat.o $(OBJ_DIR)/io.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(OBJ_DIR)/thermostat.o: thermostat.c thermostat.h
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/thermostat.exe: thermostat.c $(OBJ_DIR)/mm.o $(OBJ_DIR)/random.o $(OBJ_DIR)/spinlock.o $(OBJ_DIR)/molecule.o $(OBJ_DIR)/elements.o $(OBJ_DIR)/velocity_init.o $(OBJ_DIR)/io.o
	$(CC) -DMODULE_TEST -lm -o $@ $^

$(OBJ_DIR)/md.o: md.c md.h
	$(CC) -fPIC -c -o $@ $<

$(OBJ_DIR)/io.o: io.c io.h
	$(CC) -fPIC -c -o $@ $<

$(BIN_DIR)/io.exe: io.c io.h
	$(CC) -DMODULE_TEST -o $@ $<
