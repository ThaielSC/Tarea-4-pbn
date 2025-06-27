# --- Compilador y Flags ---
CXX = g++

PYTHON_INCLUDES := -I/opt/homebrew/opt/python@3.13/Frameworks/Python.framework/Versions/3.13/include/python3.13 -Iextern/pybind11/include
PYTHON_LDFLAGS  := -L/opt/homebrew/opt/python@3.13/Frameworks/Python.framework/Versions/3.13/lib -lpython3.13

CXXFLAGS = -Wall -std=c++14 -fPIC -Iinclude -MMD -MP $(PYTHON_INCLUDES)
SO_LDFLAGS = -shared $(PYTHON_LDFLAGS)
LDFLAGS = $(PYTHON_LDFLAGS)

# --- Directorios ---
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# --- Archivos ---
TARGET = colisionlib/colisiona.so
TEST_EXEC = $(BUILD_DIR)/run_tests

# --- Fuente por grupo ---
SRC_SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
TEST_SRCS := $(shell find $(TEST_DIR) -name '*.cpp')
ALL_SRCS := $(SRC_SRCS) $(TEST_SRCS)

# Objetos correspondientes
SRC_OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC_SRCS))
TEST_OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEST_SRCS))
ALL_OBJS := $(SRC_OBJS) $(TEST_OBJS)

# Dependencias
DEPS := $(ALL_OBJS:.o=.d)

# --- Reglas ---

all: $(TARGET) stub

# Biblioteca compartida usando solo código fuente del núcleo
$(TARGET): $(SRC_OBJS)
	@mkdir -p $(dir $@)
	@echo "Enlazando $(TARGET)..."
	$(CXX) $(SO_LDFLAGS) -o $@ $^

# Ejecutable de pruebas usando código fuente del núcleo + pruebas
$(TEST_EXEC): $(ALL_OBJS)
	@echo "Enlazando $(TEST_EXEC)..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar cualquier .cpp a .o en build/
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar pruebas
test: $(TEST_EXEC)
	@echo "--- Ejecutando Pruebas ---"
	./$(TEST_EXEC)

# Limpiar
clean:
	@echo "Limpiando..."
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)

PYTHONPATH := $(CURDIR)/colisionlib

stub:
	PYTHONPATH=$(PYTHONPATH)
	pybind11-stubgen colisiona -o ./colisionlib

.PHONY: all clean test stub

