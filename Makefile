# -------------------------------
# 🔧 Configuración general
# -------------------------------

CXX             ?= g++
PYTHON_VERSION  ?= 3.13
PYTHON          ?= $(shell which python3 2>/dev/null || which python 2>/dev/null)

# Rutas obtenidas desde Python
PYTHON_INCLUDES := $(shell python3-config --cflags)
PYTHON_LDFLAGS  := $(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('LIBDIR'))")/lib$(PYTHON_VERSION).so
PYBIND11_INCLUDE := extern/pybind11/include

# Flags de compilación
CXXFLAGS   = -Wall -std=c++14 -fPIC -Iinclude -MMD -MP \
             $(PYTHON_INCLUDES) -I$(PYBIND11_INCLUDE)
SO_LDFLAGS = -shared -L$(dir $(PYTHON_LDFLAGS)) -lpython$(PYTHON_VERSION)
LDFLAGS    = $(SO_LDFLAGS)

# -------------------------------
# 📁 Directorios y nombres
# -------------------------------

SRC_DIR    = src
TEST_DIR   = tests
BUILD_DIR  = build
PKG_DIR    = colisionlib
LIB_NAME   = colisiones
TARGET     = $(PKG_DIR)/$(LIB_NAME).so
TEST_EXEC  = $(BUILD_DIR)/run_tests

# -------------------------------
# 🧱 Archivos fuente
# -------------------------------

SRC_SRCS   := $(shell find $(SRC_DIR) -name '*.cpp')
TEST_SRCS  := $(shell find $(TEST_DIR) -name '*.cpp')
ALL_SRCS   := $(SRC_SRCS) $(TEST_SRCS)

SRC_OBJS   := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC_SRCS))
TEST_OBJS  := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEST_SRCS))
ALL_OBJS   := $(SRC_OBJS) $(TEST_OBJS)

DEPS       := $(ALL_OBJS:.o=.d)

# -------------------------------
# 📦 Reglas principales
# -------------------------------

all: $(TARGET) stub ptest

# 🔗 Compilar la librería compartida
$(TARGET): $(SRC_OBJS)
	@mkdir -p $(dir $@)
	@echo "🔧 Enlazando $@..."
	@$(CXX) $(SO_LDFLAGS) -o $@ $^

# 🧪 Compilar el ejecutable de pruebas
$(TEST_EXEC): $(ALL_OBJS)
	@echo "🔧 Enlazando $@..."
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 🛠️ Compilar archivos .cpp en objetos .o
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "🛠️  Compilando $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# 🧪 Ejecutar pruebas
ctest: $(TEST_EXEC)
	@echo "--- 🧪 Ejecutando Pruebas ---"
	@./$(TEST_EXEC)

ptest:
	PYTHONPATH=colisionlib python test.py

# 🧹 Limpiar todo
clean:
	@echo "🧹 Limpiando..."
	@rm -rf $(BUILD_DIR) $(TARGET) $(PKG_DIR)

# 🧾 Generar stub de pybind11
stub:
	@if ! command -v pybind11-stubgen >/dev/null 2>&1; then \
		echo "⚠️  pybind11-stubgen no está instalado. Ejecuta 'pip install pybind11-stubgen' si quieres los stubs."; \
	else \
		echo "🧾 Generando stubs de pybind11..."; \
		PYTHONPATH=$(CURDIR)/$(PKG_DIR) pybind11-stubgen $(LIB_NAME) -o ./$(PKG_DIR); \
	fi

-include $(DEPS)

.PHONY: all clean ctest stub ptest
