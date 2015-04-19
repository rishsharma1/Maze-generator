/*
** DFS maze creator
** Generated maze should be fully connected - can get to every point from any point
**
** Works with a grid of vertices n*n. Vertices are indexed by [row][column]
** in visited[][] and walls[][].
**
** Output drawing can either be an ASCII print (pretty ugly) or an R script (prettier).
**
** Usage: ./dfsMaze 10 r | R --slave
**
** Andrew Turpin (aturpin@unimelb.edu.au)
** Wed 20 Mar 2013 06:25:44 EST
**
** Modified Tue 17 Mar 2015 19:35:05 AEDT: use graph ADT
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graph.h"

    // convert (row, col) to a vertex label (row/col numbering begins at 0)
#define CELL_TO_LABEL(_row, _col) (((_row) * (n+2)) + (_col))
void random_sort(Edge *A,int n);

/*
** Print an R script for drawing Maze
*/
void 
drawMazeR(Graph *g, int n) {
        // Setup plot area 
    printf("n <- %d\n",n);
    printf("boxSize <- 0.5\n");
    printf("plot(0,0, xlim=c(0, %d), ylim=c(-%d, 0), "
                "xlab=\"\", ylab=\"\", axes=FALSE, type=\"n\")\n",n+3,n+3);
    printf("dP <- function(tlx, tly, col=\"black\") polygon(tlx + c(0,0,boxSize,boxSize), "
                            "tly + c(0,boxSize,boxSize,0), border=NA,col = col)\n");

    for(double row = 1 ; row <= n ; row++) {
        for(double col = 1 ; col <= n ; col++) {
            int this_has_left  = graph_has_edge(g, CELL_TO_LABEL(row,col), CELL_TO_LABEL(row  ,col-1));
            int this_has_rght  = graph_has_edge(g, CELL_TO_LABEL(row,col), CELL_TO_LABEL(row  ,col+1));
            int this_has_up    = graph_has_edge(g, CELL_TO_LABEL(row,col), CELL_TO_LABEL(row-1,col));
            int this_has_down  = graph_has_edge(g, CELL_TO_LABEL(row,col), CELL_TO_LABEL(row+1,col));

            if (this_has_left) printf("dP(%lf,-%lf)\n", col-0.5, row);
            if (this_has_up)   printf("dP(%lf,-%lf)\n", col    , row-0.5);
            if (this_has_rght) printf("dP(%lf,-%lf)\n", col+0.5, row);
            if (this_has_down) printf("dP(%lf,-%lf)\n", col    , row+0.5);

            printf("dP(%lf,-%lf)\n", col-0.5, row-0.5);
            printf("dP(%lf,-%lf)\n", col-0.5, row+0.5);
            printf("dP(%lf,-%lf)\n", col+0.5, row-0.5);
            printf("dP(%lf,-%lf)\n", col+0.5, row+0.5);

            //printf("text(%f, -%f, %f,col=\"red\", cex=0.5)\n",col,row, CELL_TO_LABEL(row,col));
        }
    }

    printf("dP(%d,%d, \"red\")\n", 1, -1);
    printf("dP(%d,%d, \"green\")\n", n, -n);
}// drawMazeR()


/*
** Just like the usual explore except randomise order of edge 
** choices, and remove edges when followed.
** ASSUMES always called with v unvisited, so check before calling!
*/
void 
explore(Graph *g, Label v) {
    g->vertices[v].data = (void *)1; // mark as visited

    drawMazeR(g, sqrt(g->number_of_vertices) - 2);  // comment out to avoid many pages

    int n;
    Edge *edges = graph_get_edge_array(g, v, &n);
    random_sort(edges,n);

    for(int i=0;i<n;i++) {

    	if(!edges[i].data) {
    		graph_del_edge(g,v,edges[i]);
    		explore(g,edges[i]);
    	}
    }

    // TODO : randomly permute edges

    // TODO: follow unvisited edges, delteing them before calling explore

}//explore()

/*
** Draw Maze as ascii
*/
void 
drawMaze(Graph *g, int n) {
    // TO DO - not essential...
}// drawMaze()

void
random_sort(Edge *A,int n) {
	int i;
	int j;

	for(i=n-1;i>0;i--) {

		j = rand()%(i+1);
		swap(&A[i],&A[j]);
	}

}

/*
** Get command line params, allocate memory, call dfs, draw result
*/
int 
main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr,"Usage: %s n { a | r} \n",argv[0]);
        fprintf(stderr,"    where\n");
        fprintf(stderr,"      n - dimension of maze\n");
        fprintf(stderr,"      r - print an R script for drawing maze\n");
        fprintf(stderr,"      a - print an ascii representation of maze\n");
        return EXIT_FAILURE;
    }

    int n;
    sscanf(argv[1], "%d", &n);

    printf("# Generating an %dx%d maze\n",n,n);

    srandom(time(NULL));

        /* Create a graph with (n+2)*(n+2) nodes, where each node is a cell.
           Every cell has 4 walls (edges).
           Every cell but the borders are unvisited.
         */
    Graph *g = graph_new((n+2) * (n+2));

        // Set all vertices to unvisited
    for(int i = 0 ; i < n+2 ; i++) 
        for(int j = 0 ; j < n+2 ; j++) 
            graph_set_vertex_data(g, CELL_TO_LABEL(i, j), (void *)0); 

        // Set border vertices to visited
    for(int i = 0 ; i < n+2 ; i++) {
        graph_set_vertex_data(g, CELL_TO_LABEL(0,   i), (void *)1);
        graph_set_vertex_data(g, CELL_TO_LABEL(n+1, i), (void *)1);
        graph_set_vertex_data(g, CELL_TO_LABEL(i,   0), (void *)1);
        graph_set_vertex_data(g, CELL_TO_LABEL(i, n+1), (void *)1);
    }

        // For all internal cells, set edges in four directions
    for(int i = 1 ; i <= n ; i++) 
        for(int j = 1 ; j <= n ; j++) {
           graph_add_edge(g, CELL_TO_LABEL(i,j), CELL_TO_LABEL(i-1, j), NULL);
           graph_add_edge(g, CELL_TO_LABEL(i,j), CELL_TO_LABEL(i+1, j), NULL);
           graph_add_edge(g, CELL_TO_LABEL(i,j), CELL_TO_LABEL(i, j-1), NULL);
           graph_add_edge(g, CELL_TO_LABEL(i,j), CELL_TO_LABEL(i, j+1), NULL);
        }
    
        /* away we go */
    graph_dfs(g, CELL_TO_LABEL(1,1), explore);

        /* draw result */
    if (argv[2][0] == 'r')
        drawMazeR(g, n);
    else
        drawMaze(g, n);

    return EXIT_SUCCESS;
}
