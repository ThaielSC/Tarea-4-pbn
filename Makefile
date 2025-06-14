# Makefile para compilar un proyecto de C++ con una estructura de directorios anidados.
#
# Uso:
#   make          - Compila el ejecutable de pruebas en el directorio build/.
#   make test     - Compila y ejecuta las pruebas.
#   make clean    - Limpia todos los archivos generados.
# -----------------------------------------------------------------------------

# --- Compilador y Flags ---
CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -Wundef -Wuninitialized -Winit-self -g -O0 \
           -Iinclude -MMD -MP

# --- Directorios del Proyecto ---
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# --- Archivos del Proyecto ---
TEST_EXEC = $(BUILD_DIR)/run_tests

# Encuentra recursivamente todos los archivos .cpp en los directorios de fuente y tests.
# Usamos 'find' en lugar de 'wildcard' para la búsqueda recursiva.
SRCS := $(shell find $(SRC_DIR) -name '*.cpp') $(shell find $(TEST_DIR) -name '*.cpp')

# Genera los nombres de los archivos objeto (.o) en el directorio build/,
# manteniendo la estructura de subdirectorios.
# Ejemplo: src/composites/ObjectA.cpp -> build/composites/ObjectA.o
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Genera los nombres de los archivos de dependencia (.d)
DEPS := $(OBJS:.o=.d)

# --- Reglas del Makefile ---

all: $(TEST_EXEC)

$(TEST_EXEC): $(OBJS)
	@echo "Enlazando para crear el ejecutable..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla patrón genérica para compilar cualquier .cpp en un .o dentro de build/.
# Esta única regla ahora maneja tanto los archivos de src/ como los de tests/.
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_EXEC)
	@echo "--- Ejecutando Pruebas ---"
	./$(TEST_EXEC)

clean:
	@echo "Limpiando directorio de build..."
	rm -rf $(BUILD_DIR)

-include $(DEPS)

.PHONY: all clean test
