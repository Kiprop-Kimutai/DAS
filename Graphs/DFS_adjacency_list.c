#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int vertex;
  struct node *next;
};
struct Graph {
  int vertices;
  struct node **adjList;
  int *visited;
};
struct node *createNode(int vertex) {
  struct node *newNode = malloc(sizeof(struct node));
  newNode->vertex = vertex;
  newNode->next = NULL;
  return newNode;
}
struct Graph *createGraph(int vertices) {
  int i,j;
  struct Graph *graph = malloc(sizeof(struct Graph));
  graph->vertices = vertices;
  graph->adjList = malloc(vertices *sizeof(struct node));
  graph->visited = malloc(vertices *sizeof(int));

  for(i = 0; i < vertices; i++) {
    graph->adjList[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}
void addEdge(struct Graph *graph, int src, int dest) {
  // add edge from src to dest
  struct node *newNode = createNode(dest);
  newNode->next = graph->adjList[src];
  graph->adjList[src] = newNode;
  // add edge from dest to src
  newNode = createNode(src);
  newNode->next = graph->adjList[dest];
  graph->adjList[dest] = newNode;
}
void printGraph(struct Graph *graph) {
  int v;
  for(v = 0; v < graph->vertices; v++) {
    printf("\n%d",v);
    struct node *node = graph->adjList[v];
    while(node) {
      printf("->%d",node->vertex);
      node = node->next;
    }
  }
}
void DFS(struct Graph *graph, int start) {
  int v;
  graph->visited[start] = 1;
  struct node *temp = graph->adjList[start];
  printf("Visited %d\n",start);
  while(temp) {
    if(graph->visited[temp->vertex] == 0) {
      DFS(graph, temp->vertex);
    }
    temp = temp->next;
  }
}
int main(void) {
  struct Graph *graph= createGraph(5);
  addEdge(graph, 0, 4);
  addEdge(graph, 0, 3);
  addEdge(graph, 0, 2);
  addEdge(graph, 0, 1);
  printGraph(graph);
  printf("\n");
  DFS(graph, 0);
  return 0;
}