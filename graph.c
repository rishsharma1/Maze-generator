/*
** Graph data type
** Uses an adjacency list representation (arrays for lists).
** Written for workshop 3 of COMP20007
**
** Andrew Turpin
** Tue 17 Mar 2015 19:13:47 AEDT
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

#define INITIAL 10

/*
** Create graph with number_of_vertices vertices
*/
Graph *
graph_new(int number_of_vertices) {
    assert(number_of_vertices > 0);
    int i;
    Graph *g = NULL;

    g = (Graph*)malloc(sizeof(Graph));
    assert(g);
    g->number_of_vertices = number_of_vertices;

    g->vertices = (Vertex*)malloc(sizeof(Vertex)*number_of_vertices);
    assert(g->vertices);

    for(i=0;i<number_of_vertices;i++) {
    	//Initial allocation of memory
        g->vertices[i].label = i;
    	g->vertices[i].max_num_edges = INITIAL;
    	//Initialising number of edges 
    	g->vertices[i].num_edges = 0;
    	//mallocing array of edges
    	g->vertices[i].edges = (Edge*)malloc(sizeof(Edge)*INITIAL);
    	assert(g->vertices[i].edges);
    }

    // TODO: malloc space for g
    // TODO: malloc space for number_of_vertices vertices

    return(g);
}

/*
** Add edge to g. 
*/
void  
graph_add_edge(Graph *g, Label v, Label u, void *data) {
    Edge e;
    assert(g);
    //no negative vertices
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);

    e.u = u;
    e.data = data;


    if(g->vertices[v].num_edges >= g->vertices[v].max_num_edges) {
    	g->vertices[v].max_num_edges *= 2;
    	g->vertices[v].edges = (Edge *)realloc(g->vertices[v].edges,sizeof(Edge)*g->vertices[v].max_num_edges);
    	assert(g->vertices[v].edges);
    }
   
    //add an edge to vertex v, and incrementing the edge count
    g->vertices[v].edges[g->vertices[v].num_edges++] = e;

    
    // TODO: Make room in g->vertices[v].edges if no room.
    // TODO: add u and data to g->vertices[v].edges array
    // TODO: increment g->vertices[v].num_edges
}

/*
** Delete edge from g. Only deletes one copy if there are multiple.
** Does nothing if u is not in v's list.
*/
void  
graph_del_edge(Graph *g, Label v, Label u) {
    int i;
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);

    for(i=0;i<g->vertices[v].num_edges;i++) {

    	if(g->vertices[v].edges[i].u == u) {
    		
    		//swap the edge to be deleted with last item in edges array
    		swap(&g->vertices[v].edges[i],
    		&g->vertices[v].edges[g->vertices[v].num_edges-1]);
    		// free the last edge
            


    		//check this line not working?? get help??
    		//free(g->vertices[v].edges[g->vertices[v].num_edges-1]);
    		
    		//update number of edges 
    		g->vertices[v].num_edges--;
    		// found one therefore we can assume to break out of loop
    		break;
    	}
    }

    // TODO
}

/*
** Return pointer to start of edge array for vertex v
** Set n to the number of items in the edge array.
*/
Edge *
graph_get_edge_array(Graph *g, Label v, int *num_edges) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);

    *num_edges = g->vertices[v].num_edges;

    return g->vertices[v].edges;
}

/*
** Return 1 if (v,u) is in g
*/
int
graph_has_edge(Graph *g, Label v, Label u) {
	int i;
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);

    for(i=0;i<g->vertices[v].num_edges;i++) {

    	if(g->vertices[v].edges[i].u == u) {
    		return 1;
    
    	}
    }
    


    // TODO

    return 0;
}


/*
** Set vertex's data to data
*/
void  
graph_set_vertex_data(Graph *g, Label v, void *data) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    
    g->vertices[v].data = data;
}


/*
** Simple explore for calling from dfs that doesn't actually do anything.
** Use as a template for writing your own explore() functions.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
*/
void 
graph_default_explore(Graph *g, Label v) {
    if (g->vertices[v].data)
        return;

    g->vertices[v].data = (void *)1; // mark as visited

    for(int i = 0 ; i < g->vertices[v].num_edges ; i++)
        graph_default_explore(g, g->vertices[v].edges[i].u);
}

/*
** Perform DFS beginning at v, calling pre() and post() as appropriate.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
*/
void 
graph_dfs(Graph *g, Label v, void (explore)(Graph *g, Label v)) {
    assert(g);
    assert(explore);
    assert(v >= 0 && v < g->number_of_vertices);

        // First explore from v
    explore(g, v);

        // Now do the rest (if any)
    for(int i = 0; i < g->number_of_vertices ; i++)
        explore(g, i);
}

// Used to swap edges 
void
swap(Edge *a,Edge *b) {
  Edge temp;
  temp = *a;
  *a = *b;
  *b = temp;
}