#include <stdio.h>
#include <string.h>
#include "Graph.h"

// Dataset Pereira (Estaciones, líneas, tiempos, etc.)
void load_pereira_megabus(Graph* graph) {
    char* stations[15] = {
        "Terminal", "Plaza de Bolívar", "Hospital San Jorge", "La Popa",
        "Dosquebradas", "Aeropuerto", "Cerritos", "Estadio", "Cuba",
        "Parque Arboleda", "Álamos", "Universidad Tecnológica",
        "Palo de Agua", "Unicentro", "El Poblado"
    };
    
    graph->num_vertices = 15;
    for (int i = 0; i < 15; i++) {
        strncpy(graph->station_names[i], stations[i], MAX_STATION_NAME - 1);
        graph->station_names[i][MAX_STATION_NAME - 1] = '\0';
    }
    
    Schedule default_schedule = {5, 23, 10};
    
    // Línea 1: Terminal ↔ Cuba ↔ Centro ↔ Aeropuerto
    add_edge_with_cost(graph, 0, 8, 12, 2700, "Línea 1", default_schedule);
    add_edge_with_cost(graph, 8, 0, 12, 2700, "Línea 1", default_schedule);

    add_edge_with_cost(graph, 8, 1, 10, 2700, "Línea 1", default_schedule);
    add_edge_with_cost(graph, 1, 8, 10, 2700, "Línea 1", default_schedule);

    add_edge_with_cost(graph, 1, 5, 15, 2700, "Línea 1", default_schedule);
    add_edge_with_cost(graph, 5, 1, 15, 2700, "Línea 1", default_schedule);
    
    // Línea 2: Dosquebradas ↔ Plaza ↔ UTP ↔ Hospital
    add_edge_with_cost(graph, 4, 1, 8, 2700, "Línea 2", default_schedule);
    add_edge_with_cost(graph, 1, 4, 8, 2700, "Línea 2", default_schedule);

    add_edge_with_cost(graph, 1, 11, 7, 2700, "Línea 2", default_schedule);
    add_edge_with_cost(graph, 11, 1, 7, 2700, "Línea 2", default_schedule);

    add_edge_with_cost(graph, 11, 2, 10, 2700, "Línea 2", default_schedule);
    add_edge_with_cost(graph, 2, 11, 10, 2700, "Línea 2", default_schedule);
    
    // Ruta A: Cuba ↔ Álamos ↔ Estadio
    add_edge_with_cost(graph, 8, 10, 6, 1800, "Ruta A", default_schedule);
    add_edge_with_cost(graph, 10, 8, 6, 1800, "Ruta A", default_schedule);

    add_edge_with_cost(graph, 10, 7, 8, 1800, "Ruta A", default_schedule);
    add_edge_with_cost(graph, 7, 10, 8, 1800, "Ruta A", default_schedule);
    
    // Ruta B: Centro ↔ Arboleda ↔ Cerritos
    add_edge_with_cost(graph, 1, 9, 9, 1800, "Ruta B", default_schedule);
    add_edge_with_cost(graph, 9, 1, 9, 1800, "Ruta B", default_schedule);

    add_edge_with_cost(graph, 9, 6, 18, 1800, "Ruta B", default_schedule);
    add_edge_with_cost(graph, 6, 9, 18, 1800, "Ruta B", default_schedule);
}
