#include <stdio.h>
#include "Graph.h"

void print_menu() {
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf("║         SISTEMA DE RUTAS MEGABUS - PEREIRA           ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");
    printf("1. Ver red completa\n");
    printf("2. Ruta más rápida (tiempo)\n");
    printf("3. Ruta más económica (costo)\n");
    printf("4. Ruta con menos transbordos\n");
    printf("5. Estadísticas de red\n");
    printf("6. Salir\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf("Seleccione una opción: ");
}

void show_stations(Graph* graph) {
    printf("\n════════════ ESTACIONES ════════════\n");
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("%2d. %s\n", i, graph->station_names[i]);
    }
    printf("════════════════════════════════════\n");
}
