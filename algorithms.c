#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"

// BFS Modificado para minimizar transbordos
void bfs_min_transfers(Graph* graph, int src, int dest) {
    int V = graph->num_vertices;
    int* visited = (int*)calloc(V, sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));
    char (*parent_line)[MAX_LINE_NAME] = malloc(V * sizeof(*parent_line));
    int* transfers = (int*)malloc(V * sizeof(int));
    
    for (int i = 0; i < V; i++) {
        parent[i] = -1;
        transfers[i] = INF;
        strcpy(parent_line[i], "");
    }
    
    State* queue = (State*)malloc(MAX_QUEUE_SIZE * sizeof(State));
    int front = 0, rear = 0;
    
    queue[rear].vertex = src;
    strcpy(queue[rear].current_line, "");
    queue[rear].transfers = 0;
    rear++;
    
    visited[src] = 1;
    transfers[src] = 0;
    
    while (front != rear) {
        State current = queue[front++];
        
        if (current.vertex == dest) break;
        
        AdjNode* adj = graph->adj_list[current.vertex];
        while (adj != NULL) {
            int next = adj->vertex;
            int new_transfers = current.transfers;
            
            if (strcmp(current.current_line, adj->line) != 0 &&
                strcmp(current.current_line, "") != 0)
                new_transfers++;
            
            if (!visited[next] || new_transfers < transfers[next]) {
                visited[next] = 1;
                transfers[next] = new_transfers;
                parent[next] = current.vertex;
                strncpy(parent_line[next], adj->line, MAX_LINE_NAME - 1);
                parent_line[next][MAX_LINE_NAME - 1] = '\0';
                
                queue[rear].vertex = next;
                strncpy(queue[rear].current_line, adj->line, MAX_LINE_NAME - 1);
                queue[rear].current_line[MAX_LINE_NAME - 1] = '\0';
                queue[rear].transfers = new_transfers;
                rear++;
            }
            adj = adj->next;
        }
    }
    int path[MAX_VERTICES], len = 0;
    int crawl = dest;
    while (crawl != -1) {
        path[len++] = crawl;
        crawl = parent[crawl];
    }
    
    printf("\n========== RUTA CON MENOS TRANSBORDOS ==========\n");
    printf("Origen: %s\n", graph->station_names[src]);
    printf("Destino: %s\n\n", graph->station_names[dest]);
    printf("Transbordos: %d\n", transfers[dest]);
    printf("Estaciones: %d\n\n", len);
    printf("Itinerario:\n");
    
    for (int i = len - 1; i >= 0; i--) {
        printf("%d. %s", len - i, graph->station_names[path[i]]);
        if (i != len - 1) {
            printf(" [%s]", parent_line[path[i]]);
        }
        if (i > 0 && strcmp(parent_line[path[i]], parent_line[path[i - 1]]) != 0)
            printf(" → TRANSBORDO");
        printf("\n");
    }
    printf("================================================\n");
    
    free(visited);
    free(parent);
    free(parent_line);
    free(transfers);
    free(queue);
}


void dijkstra_by_cost(Graph* graph, int src, int dest) {
    int V = graph->num_vertices;
    int* cost = (int*)malloc(V * sizeof(int));
    int* time = (int*)malloc(V * sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));
    int* visited = (int*)calloc(V, sizeof(int));
    
    for (int i = 0; i < V; i++) {
        cost[i] = INF;
        time[i] = INF;
        parent[i] = -1;
    }
    
    cost[src] = 0;
    time[src] = 0;
    
    for (int c = 0; c < V - 1; c++) {
        int min = INF, u = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && cost[i] < min) {
                min = cost[i];
                u = i;
            }
        }
        
        if (u == -1) break;
        
        visited[u] = 1;
        
        AdjNode* temp = graph->adj_list[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int new_cost = cost[u] + temp->cost;
            int new_time = time[u] + temp->weight;
            
            if (!visited[v] && new_cost < cost[v]) {
                cost[v] = new_cost;
                time[v] = new_time;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }
    if (cost[dest] == INF) {
    printf("\n========== RUTA MÁS ECONÓMICA ==========\n");
    printf("NO existe una ruta entre %s y %s.\n",
           graph->station_names[src],
           graph->station_names[dest]);
    printf("=========================================\n");
    free(cost);
    free(time);
    free(parent);
    free(visited);
    return;
}
    int path[MAX_VERTICES], len = 0;
    int crawl = dest;
    while (crawl != -1) {
        path[len++] = crawl;
        crawl = parent[crawl];
    }
    
    printf("\n========== RUTA MÁS ECONÓMICA ==========\n");
    printf("Origen: %s\n", graph->station_names[src]);
    printf("Destino: %s\n\n", graph->station_names[dest]);
    printf("Costo total: $%d\n", cost[dest]);
    printf("Tiempo total: %d minutos\n", time[dest]);
    printf("Estaciones: %d\n\n", len);
    printf("Ruta:\n");
    
    for (int i = len - 1; i >= 0; i--) {
        printf("%s", graph->station_names[path[i]]);
        if (i) printf(" → ");
    }
    printf("\n=========================================\n");
    
    free(cost);
    free(time);
    free(parent);
    free(visited);
}

int is_edge_available(AdjNode* edge, int current_hour) {
    return (current_hour >= edge->schedule.start_hour && 
            current_hour <= edge->schedule.end_hour);
}

int calculate_wait_time(AdjNode* edge, int current_hour, int current_min) {
    if (!is_edge_available(edge, current_hour)) return -1;
    
    int total_min = current_hour * 60 + current_min;
    int freq = edge->schedule.frequency_min;
    int next_departure = ((total_min / freq) + 1) * freq;
    return next_departure - total_min;
}

void dijkstra_by_cost_with_schedule(Graph* graph, int src, int dest, 
                                    int current_hour, int current_min) {
    printf("Ruta más económica con horarios:\n");
    printf("Función en desarrollo...\n");
}

int is_path_different(Path* p1, Path* p2) {
    return strcmp(p1->lines_used, p2->lines_used) != 0;
}

void find_alternative_paths(Graph* graph, int src, int dest) {
    Path paths[3];
    int path_count = 0;
    
    printf("Búsqueda de rutas alternativas:\n");
    printf("Función en desarrollo...\n");
    
    for (int i = 0; i < path_count; i++) {
        printf("Ruta %d: Tiempo %d, Costo %d, Transbordos %d, Líneas %s\n",
               i+1, paths[i].total_time, paths[i].total_cost, 
               paths[i].transfers, paths[i].lines_used);
    }
}



void print_station_degrees(Graph* g) {
    printf("\n===== Grado de cada estación =====\n");

    for (int i = 0; i < g->num_vertices; i++) {
        int degree = 0;
        AdjNode* adj = g->adj_list[i];

        while (adj != NULL) {
            degree++;
            adj = adj->next;
        }

        printf("%d. %s — %d conexiones\n", i, g->station_names[i], degree);
    }
}

typedef struct {
    int id;
    int degree;
} HubInfo;

int compare_hubs(const void* a, const void* b) {
    return ((HubInfo*)b)->degree - ((HubInfo*)a)->degree;
}

void print_top3_hubs(Graph* g) {
    HubInfo hubs[g->num_vertices];

    for (int i = 0; i < g->num_vertices; i++) {
        int degree = 0;
        AdjNode* adj = g->adj_list[i];
        while (adj != NULL) {
            degree++;
            adj = adj->next;
        }
        hubs[i].id = i;
        hubs[i].degree = degree;
    }

    qsort(hubs, g->num_vertices, sizeof(HubInfo), compare_hubs);

    printf("\n===== TOP 3 Estaciones Hub =====\n");

    int limit = (g->num_vertices < 3 ? g->num_vertices : 3);

    for (int i = 0; i < limit; i++) {
        int id = hubs[i].id;
        printf("%d. %s — %d conexiones\n", i + 1, g->station_names[id], hubs[i].degree);
    }
}


int is_graph_connected(Graph* g) {
    int V = g->num_vertices;
    int visited[V];
    for (int i = 0; i < V; i++) visited[i] = 0;

    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = 0;
    visited[0] = 1;

    while (front != rear) {
        int u = queue[front++];

        AdjNode* adj = g->adj_list[u];
        while (adj != NULL) {
            if (!visited[adj->vertex]) {
                visited[adj->vertex] = 1;
                queue[rear++] = adj->vertex;
            }
            adj = adj->next;
        }
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i]) return 0;  
    }
    return 1;  
}

void print_connectivity(Graph* g) {
    printf("\n===== Conectividad de la red =====\n");
    if (is_graph_connected(g))
        printf("La red está CONECTADA.\n");
    else
        printf("La red NO está conectada.\n");
}


void bfs_dist(Graph* g, int start, int* dist) {
    int V = g->num_vertices;
    for (int i = 0; i < V; i++) dist[i] = -1;

    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = start;
    dist[start] = 0;

    while (front != rear) {
        int u = queue[front++];

        AdjNode* adj = g->adj_list[u];
        while (adj != NULL) {
            int v = adj->vertex;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
            adj = adj->next;
        }
    }
}

void print_average_distance(Graph* g) {
    printf("\n===== Distancia promedio =====\n");

    int V = g->num_vertices;
    int dist[V];

    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < V; i++) {
        bfs_dist(g, i, dist);

        for (int j = i + 1; j < V; j++) {
            if (dist[j] != -1) {
                sum += dist[j];
                count++;
            }
        }
    }

    if (count == 0) {
        printf("No es posible calcular distancia promedio.\n");
        return;
    }

    printf("Distancia promedio entre estaciones: %.2f saltos\n",
           sum / count);
}
