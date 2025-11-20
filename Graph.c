#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = vertices;
    graph->adj_list = (AdjNode**)malloc(vertices * sizeof(AdjNode*));
    
    for (int i = 0; i < vertices; i++) {
        graph->adj_list[i] = NULL;
    }
    
    return graph;
}

void add_edge_with_cost(Graph* graph, int src, int dest, int time, int cost, 
                        const char* line, Schedule sched) {
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->vertex = dest;
    newNode->weight = time;
    newNode->cost = cost;
    strncpy(newNode->line, line, MAX_LINE_NAME - 1);
    newNode->line[MAX_LINE_NAME - 1] = '\0';
    newNode->schedule = sched;
    newNode->next = graph->adj_list[src];
    graph->adj_list[src] = newNode;
}

void free_graph(Graph* graph) {
    if (!graph) return;
    
    for (int i = 0; i < graph->num_vertices; i++) {
        AdjNode* current = graph->adj_list[i];
        while (current) {
            AdjNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    free(graph->adj_list);
    free(graph);
}



