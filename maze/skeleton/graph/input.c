#include <stdio.h>
#include  <stdlib.h>
#include "graph.h"



int main(int argc,char *argv[]) {

	int size_of_graph = atoi(argv[1]);
	int vertex, edge;

	Graph *g = graph_new(size_of_graph);

	while(scanf("%d %d",&vertex,&edge) == 2) {
		graph_add_edge(g,vertex,edge,NULL);
	}
	
	for(int i=0;i<size_of_graph;i++) {
		printf("vertex %d: ",i );
		for(int j=0;j<g->vertices[i].num_edges;j++) {
			printf("%d ",g->vertices[i].edges[j].u);
		}
		printf("\n");
	}
	return 0;
}