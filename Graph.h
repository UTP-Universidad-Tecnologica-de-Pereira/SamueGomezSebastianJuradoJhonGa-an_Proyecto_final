/* Graph.h */
#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 50
#define MAX_LINE_NAME 20
#define MAX_STATION_NAME 50
#define INF 99999999

typedef struct Schedule {
    int start_hour;
    int end_hour;
    int frequency_min;
} Schedule;

typedef struct AdjNode {
    int vertex;
    int weight;       
    int cost;          
    char line[MAX_LINE_NAME];     
    Schedule schedule;
    struct AdjNode* next;
} AdjNode;

typedef struct Graph {
    int num_vertices;
    char station_names[MAX_VERTICES][MAX_STATION_NAME];
    AdjNode** adj_list;
} Graph;

typedef struct Path {
    int* vertices;  
    int length;     
    int total_time; 
    int total_cost; 
    int transfers;  
    char lines_used[100];
} Path;

Graph* create_graph(int vertices);
void add_edge_with_cost(Graph* graph, int src, int dest, int time, int cost, 
                        const char* line, Schedule sched);
void free_graph(Graph* graph);
void load_pereira_megabus(Graph* graph);

#endif