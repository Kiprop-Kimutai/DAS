/*
* Depth First Search impelementation using adjacency matrix
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define V 5

void createAdjMatrix(int Graph[][V], int edges[][2], int edgesCount) {
  int i,j;
  // initialize graph
  for(i = 0; i < V; i++) {
    for(j = 0; j < V; j++) {
      Graph[i][j] = 0;
    }
  }
  // add edges
  for(i = 0; i < edgesCount; i++) {
    int x = edges[i][0];int y = edges[i][1];
    Graph[x][y] = 1;
    Graph[y][x] = 1;
  }
}
void printGraph(int Graph[][V]) {
  int i,j;
  for(i = 0; i < V; i++) {
    for(j = 0; j < V; j++) {
      printf("%d ", Graph[i][j]);
    }
    printf("\n");
  }
}

void DFS(int Graph[][V], int visited[V], int start) {
  int i,j;
  visited[start] = 1;
  printf("Visited %d\n",start);
  for(i = 0; i < V; i++) {
    if(visited[i] == 0) {
      DFS(Graph, visited,i);
    }
  }
}

int main(void) {
  int Graph[V][V];
  int edgesArray[][2] = {{0,1},{0,2},{0,3},{0,4}};
  int visited[V] = {0,0,0,0,0};
  int edgesCount = sizeof(edgesArray)/sizeof(edgesArray[0]);
  createAdjMatrix(Graph, edgesArray, edgesCount);
  printGraph(Graph);
  printf("\n");
  DFS(Graph,visited,0);
  return 0;
}