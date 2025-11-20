# Makefile para Sistema de Rutas Megabus - Pereira

# Compilador
CC = gcc

# Flags de compilación
CFLAGS = -Wall -Wextra -std=c99 -O2

# Flags de debug (descomenta para debugging)
# CFLAGS = -Wall -Wextra -std=c99 -g -DDEBUG

# Nombre del ejecutable
TARGET = megabus

# Archivos fuente
SOURCES = main.c Graph.c algorithms.c Dataset.c menu.c

# Archivos objeto (se generan automáticamente desde SOURCES)
OBJECTS = $(SOURCES:.c=.o)

# Archivos header
HEADERS = Graph.h algorithms.h

# Regla principal: compilar todo
all: $(TARGET)

# Regla para crear el ejecutable
$(TARGET): $(OBJECTS)
	@echo "Enlazando el programa..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✓ Compilación exitosa. Ejecutable: $(TARGET)"

# Regla para compilar archivos .c a .o
%.o: %.c $(HEADERS)
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar y ejecutar
run: $(TARGET)
	@echo "Ejecutando $(TARGET)..."
	@./$(TARGET)

# Limpiar archivos objeto y ejecutable
clean:
	@echo "Limpiando archivos compilados..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Limpieza completada"

# Limpiar y recompilar
rebuild: clean all

# Compilar con flags de debug
debug: CFLAGS = -Wall -Wextra -std=c99 -g -DDEBUG
debug: clean $(TARGET)
	@echo "✓ Versión debug compilada"

# Mostrar información de compilación
info:
	@echo "=== Información del Makefile ==="
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Ejecutable: $(TARGET)"
	@echo "Fuentes: $(SOURCES)"
	@echo "Objetos: $(OBJECTS)"
	@echo "Headers: $(HEADERS)"

# Verificar que existen todos los archivos fuente
check:
	@echo "Verificando archivos fuente..."
	@for file in $(SOURCES) $(HEADERS); do \
		if [ -f $$file ]; then \
			echo "✓ $$file"; \
		else \
			echo "✗ $$file (FALTA)"; \
		fi; \
	done

# Ayuda
help:
	@echo "=== Makefile - Sistema Megabus ==="
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make         - Compilar el proyecto"
	@echo "  make all     - Compilar el proyecto (igual que make)"
	@echo "  make run     - Compilar y ejecutar"
	@echo "  make clean   - Eliminar archivos compilados"
	@echo "  make rebuild - Limpiar y recompilar"
	@echo "  make debug   - Compilar con símbolos de debug"
	@echo "  make info    - Mostrar información de compilación"
	@echo "  make check   - Verificar que existen los archivos"
	@echo "  make help    - Mostrar esta ayuda"
	@echo ""

# Declarar reglas que no son archivos
.PHONY: all run clean rebuild debug info check help