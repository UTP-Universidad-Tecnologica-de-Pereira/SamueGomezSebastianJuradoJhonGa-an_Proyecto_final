# Sistema de Rutas Megabus - Pereira

Universidad Tecnologica de Pereira 2025

## Descripción del Sistema

Este proyecto implementa un sistema de búsqueda y análisis de rutas para el sistema de transporte Megabus de Pereira, Colombia. El sistema utiliza teoría de grafos para modelar la red de transporte público y ofrece diferentes algoritmos de búsqueda para encontrar rutas óptimas según diversos criterios (tiempo, costo, transbordos).

El sistema modela 15 estaciones del Megabus conectadas por diferentes líneas de transporte, permitiendo a los usuarios encontrar la mejor ruta entre dos puntos según sus necesidades específicas.

## Compilación (make)

Para compilar el proyecto, se requiere un compilador de C (gcc) y la herramienta make. El proyecto incluye los siguientes archivos fuente:

- `main.c` - Programa principal con menú interactivo
- `Graph.c` - Implementación de la estructura de grafos
- `algorithms.c` - Algoritmos de búsqueda de rutas
- `Dataset.c` - Carga de datos de las estaciones de Pereira
- `menu.c` - Funciones de interfaz de usuario

**Comandos de compilación:**

```bash
# Compilar el proyecto
make

# Ejecutar el programa
./megabus

# Limpiar archivos objeto
make clean
```

## Ejecución

Una vez compilado, ejecutar el programa con:

```bash
./megabus
```

El sistema presenta un menú interactivo con las siguientes opciones:

1. **Ver red completa** - Muestra todas las estaciones disponibles
2. **Ruta más rápida** - Encuentra la ruta con menor tiempo de viaje
3. **Ruta más económica** - Encuentra la ruta con menor costo
4. **Ruta con menos transbordos** - Minimiza la cantidad de cambios de línea
5. **Estadísticas de red** - Muestra análisis de conectividad
6. **Salir** - Termina el programa

## Funcionalidades Implementadas

### 1. Búsqueda de Ruta Más Económica (Dijkstra)
- **Algoritmo:** Dijkstra modificado para minimizar costo
- **Función:** `dijkstra_by_cost()`
- **Criterio:** Encuentra la ruta con menor costo total en pesos colombianos
- **Salida:** Muestra origen, destino, costo total, tiempo total, número de estaciones y ruta completa

### 2. Búsqueda de Ruta con Menos Transbordos (BFS Modificado)
- **Algoritmo:** BFS (Breadth-First Search) con seguimiento de líneas
- **Función:** `bfs_min_transfers()`
- **Criterio:** Minimiza el número de cambios entre líneas de transporte
- **Salida:** Muestra la ruta con indicación de transbordos y líneas utilizadas

### 3. Análisis de Red
El sistema incluye varias funciones de análisis de la red de transporte:

- **Grado de estaciones** (`print_station_degrees()`): Muestra el número de conexiones de cada estación
- **Top 3 Hubs** (`print_top3_hubs()`): Identifica las 3 estaciones más conectadas
- **Conectividad** (`print_connectivity()`): Verifica si todas las estaciones son alcanzables
- **Distancia promedio** (`print_average_distance()`): Calcula el promedio de saltos entre estaciones

### 4. Modelado de la Red
- Representa 15 estaciones del Megabus de Pereira
- Incluye múltiples líneas: Línea 1, Línea 2, Ruta A, Ruta B
- Cada conexión tiene: tiempo (minutos), costo (pesos), línea, horarios

## Complejidad

### Complejidad Temporal

- **BFS con menos transbordos:** O(V + E)
  - V = número de vértices (estaciones)
  - E = número de aristas (conexiones)
  
- **Dijkstra por costo:** O(V²)
  - Implementación con búsqueda lineal del mínimo
  - Puede optimizarse a O((V + E) log V) con heap binario

- **Análisis de conectividad (BFS):** O(V + E)

- **Cálculo de distancia promedio:** O(V × (V + E))
  - Ejecuta BFS desde cada vértice

### Complejidad Espacial

- **Estructura del grafo:** O(V + E)
  - Lista de adyacencia para representación del grafo
  
- **Algoritmos de búsqueda:** O(V)
  - Arrays auxiliares: visited, parent, distances, queue

## Ejemplos de Salida

### Ejemplo 1: Ruta más económica

```
========== RUTA MÁS ECONÓMICA ==========
Origen: Terminal
Destino: Hospital San Jorge

Costo total: $5400
Tiempo total: 29 minutos
Estaciones: 4

Ruta:
Terminal → Cuba → Plaza de Bolívar → Hospital San Jorge
=========================================
```

### Ejemplo 2: Ruta con menos transbordos

```
========== RUTA CON MENOS TRANSBORDOS ==========
Origen: Dosquebradas
Destino: Aeropuerto

Transbordos: 1
Estaciones: 3

Itinerario:
1. Dosquebradas [Línea 2]
2. Plaza de Bolívar [Línea 2] → TRANSBORDO
3. Aeropuerto [Línea 1]
================================================
```

### Ejemplo 3: Estadísticas de red

```
===== TOP 3 Estaciones Hub =====
1. Plaza de Bolívar — 8 conexiones
2. Cuba — 6 conexiones
3. Universidad Tecnológica — 4 conexiones

===== Conectividad de la red =====
La red está CONECTADA.

===== Distancia promedio =====
Distancia promedio entre estaciones: 2.45 saltos
```

## Limitaciones

1. **Horarios simplificados:** El sistema incluye estructuras para horarios (`Schedule`), pero la funcionalidad completa de búsqueda con horarios (`dijkstra_by_cost_with_schedule`) está en desarrollo.

2. **Rutas alternativas:** La función `find_alternative_paths()` está declarada pero no implementada completamente.

3. **Datos estáticos:** La red de estaciones está hardcodeada en `Dataset.c`. No hay carga dinámica desde archivos externos.

4. **Sin interfaz gráfica:** El sistema es completamente por línea de comandos.

5. **Validación básica:** No hay validación exhaustiva de entrada del usuario (ej: índices fuera de rango).

6. **Algoritmo Dijkstra no optimizado:** Usa búsqueda lineal (O(V²)) en lugar de heap de prioridad (O((V+E) log V)).

7. **Memoria fija:** Usa constantes (`MAX_VERTICES`, `MAX_QUEUE_SIZE`) en lugar de estructuras dinámicas.

8. **Dataset limitado:** Solo incluye 15 estaciones de ejemplo, no toda la red real de Megabus.

---

**Autor:** Samuel Gómez, Sebastian Jurado, Jhon Alexander  
**Lenguaje:** C (C99)  
**Plataforma:** Linux/Unix/Windows con gcc
