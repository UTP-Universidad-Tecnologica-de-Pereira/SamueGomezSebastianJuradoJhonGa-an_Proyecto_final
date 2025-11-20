/* algorithms.h */
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.h"

#define MAX_QUEUE_SIZE 200

typedef struct State {
    int vertex;
    char current_line[MAX_LINE_NAME];
    int transfers;
} State;

void bfs_min_transfers(Graph* graph, int src, int dest);
void dijkstra_by_cost(Graph* graph, int src, int dest);
int is_edge_available(AdjNode* edge, int current_hour);
int calculate_wait_time(AdjNode* edge, int current_hour, int current_min);
void dijkstra_by_cost_with_schedule(Graph* graph, int src, int dest, 
                                    int current_hour, int current_min);
int is_path_different(Path* p1, Path* p2);
void find_alternative_paths(Graph* graph, int src, int dest);
void print_station_degrees(Graph* graph);
void print_top3_hubs(Graph* graph);
void print_connectivity(Graph* graph);
void print_average_distance(Graph* graph);
#endif