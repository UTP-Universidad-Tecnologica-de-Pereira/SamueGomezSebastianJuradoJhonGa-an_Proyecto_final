#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "algorithms.h"   

void print_menu();
void show_stations(Graph* graph);

int main() {

    Graph* graph = create_graph(15);
    load_pereira_megabus(graph);

    int option;

    while (1) {
        print_menu();
        scanf("%d", &option);

        if (option == 6) break;

        switch (option) {

            case 1:
                show_stations(graph);
                break;

            case 2: {
                int o, d;
                show_stations(graph);
                printf("Origen: ");
                scanf("%d", &o);
                printf("Destino: ");
                scanf("%d", &d);
                dijkstra_by_cost(graph, o, d);
                break;
            }

            case 3: {
                int o, d;
                show_stations(graph);
                printf("Origen: ");
                scanf("%d", &o);
                printf("Destino: ");
                scanf("%d", &d);
                dijkstra_by_cost(graph, o, d);
                break;
            }

            case 4: {
                int o, d;
                show_stations(graph);
                printf("Origen: ");
                scanf("%d", &o);
                printf("Destino: ");
                scanf("%d", &d);
                bfs_min_transfers(graph, o, d);
                break;
            }

            case 5:
            print_station_degrees(graph);
            print_top3_hubs(graph);
            print_connectivity(graph);
            print_average_distance(graph);
                break;

            default:
                printf("Opción inválida.\n");
        }
    }

    free_graph(graph);
    return 0;
}
