/*
** DFS maze creator
** Generated maze should be fully connected - can get to every point from any point
**
** Works with a grid of vertices n*n. Vertices are indexed by [row][column]
** in visited[][] and walls[][].
**
** Output drawing can either be an ASCII print (pretty ugly) or an R script (prettier).
**
** Andrew Turpin (aturpin@unimelb.edu.au)
** Wed 20 Mar 2013 06:25:44 EST
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_NEIGHBOURS 4
#define UP    1
#define DOWN  2
#define LEFT  4
#define RIGHT 8

char **visited;     // visited[i][j] == 1 if cell has been visited during DFS
char **walls;       // walls[i][j] is | of UP, DOWN, LEFT, RIGHT to show which walls are *absent*.

void
usage(char *programName) {
        fprintf(stderr,"Usage: %s n { a | r} \n",programName);
        fprintf(stderr,"    where\n");
        fprintf(stderr,"      n - dimension of maze\n");
        fprintf(stderr,"      r - print an R script for drawing maze\n");
        fprintf(stderr,"      a - print an ascii representation of maze\n");
}

/*
** Allocate an n*n array and of char and initialise all to 0
*/
char **
allocNbyN(int n) {
    int i,j;
    char **A;
    if ((A = (char **)malloc(sizeof(char *) * n)) == NULL) {
        fprintf(stderr, "Out of memory for A\n");
        return NULL;
    }
    for(i = 0 ; i < n ; i++)
        if ((A[i] = (char *)malloc(sizeof(char) * n)) == NULL) {
            fprintf(stderr, "Out of memory for A\n");
            return NULL;
        }
        
    for(i = 0 ; i < n ; i++)
        for(j = 0 ; j < n ; j++) 
            A[i][j] = 0;

    return A;
}/* allocNbyN */

/*
** Remove the "direction" wall of (row,col)
*/
void
removeWall(int row, int col, int direction) {
    walls[row][col] |= direction;
}//removeWall()

/*
** Recursive DFS of graph where edges are implicitly UP, DOWN, LEFT or RIGHT from (vi,vj).
** Edges are followed in random order.
*/
void 
dfs(int n, int vi, int vj) {
    int i;

    /* TODO: set visited for vertex (vi,vj) */

        // Create and randomly permute edges
    int edges[NUM_NEIGHBOURS] = {UP, DOWN, LEFT, RIGHT};
    for(i = 0 ; i < 1000 ; i++) {
        int r1 = random() % NUM_NEIGHBOURS;
        int r2 = random() % NUM_NEIGHBOURS;
        int temp = edges[r1];
        edges[r1] = edges[r2];
        edges[r2] = temp;
    }

    for(i = 0 ; i < NUM_NEIGHBOURS ; i++) {
        switch(edges[i]) {
            case UP: 
                    /* TODO: if vertex above (vi,vj-1) has not been visited, 
                        remove the UP wall from (vi,vj) and
                        remove the DOWN wall from (vi, vj-1)
                        recurse on (vi, vj-1)
                     */
                     break;
            case DOWN: 
                    /* TODO: if vertex above (vi,vj+1) has not been visited, 
                        remove the DONW wall from (vi,vj) and
                        remove the UP wall from (vi, vj+1)
                        recurse on (vi, vj+1)
                     */
                     break;
            case LEFT: /* TODO: ... (vi-1, vj) ... */
                     break;
            case RIGHT: /* TODO: ... (vi+1, vj) ... */
                     break;
        };
    }
}//dfs()

/*
** Print an R script for drawing Maze
*/
int 
drawMazeR(int n) {
    int i,j;

        /* Setup plot area */
    printf("n <- %d\n",n);
    printf("boxSize <- 10\n");
    printf("plot(0,0, xlim=c(0, (%d+1)*2*boxSize), ylim=c(0, (%d+1)*2*boxSize), "
                "xlab=\"\", ylab=\"\", axes=FALSE, type=\"n\")\n",n,n);
    printf("dP <- function(tlx, tly) polygon(tlx*boxSize + c(0,0,boxSize,boxSize), "
                            "tly*boxSize + c(0,boxSize,boxSize,0), col = \"black\")\n");

        // top row, right wall
    for(i = 0 ; i < n ; i++) {
        printf("dP(%d,%d); dP(%d,%d)\n", 2*i, 2*n, 2*i+1, 2*n); // top row
        printf("dP(%d,%d); dP(%d,%d)\n",  2*n,   2*i,     2*n,   2*i+1); // right wall
    }
    printf("dP(%d,%d)\n",  2*n,   2*n,     2*n,   2*n); // top-right corner

        // left wall is at 2i, 2j+1
        // up   wall is at 2i+1, 2j
    for(j = 0 ; j < n ; j++) 
        for(i = 0 ; i < n ; i++) {
            if ((walls[i][j] & LEFT) == 0) 
                printf("dP(%d,%d)\n", 2*i, 2*j+1);
            if ((walls[i][j] & UP) == 0) 
                printf("dP(%d,%d)\n", 2*i+1, 2*j);
             
            printf("dP(%d,%d)\n", 2*i, 2*j);
        }
}// drawMazeR()

/*
** Draw Maze
** For each row of walls, print 2 rows: above, and left/right
*/
int 
drawMaze(int n) {
    int i,j;
    //for(j = 0 ; j < n ; j++) {
    //    for(i = 0 ; i < n ; i++) 
    //        printf("%2d ",walls[i][j]);
    //    printf("\n");
    //}
    for(j = 0 ; j < n ; j++) {
            // remaining roof
        for(i = 0 ; i < n ; i++) 
            printf("%c%c", 
                        // if self left wall or up has left wall, +, else -
                (i == 0) || ((walls[i][j] & LEFT) == 0) || (j>0 && ((walls[i][j-1] & LEFT) == 0)) ? '+' : '-',   
                ((walls[i][j] & UP) == 0) ? '-' : ' ');           // if up ' ', else -
        printf("+\n");

            // left walls 
        for(i = 0 ; i < n ; i++) 
            printf("%c ", ((walls[i][j] & LEFT) == 0) ? '|' : ' ');
        printf("|\n");
    }

        // bottom row
    for(i = 0 ; i < n ; i++) 
        printf("%c-", ((walls[i][n-1] & LEFT) == 0) ? '+' : '-');
    printf("+\n");
}// drawMaze()

/*
** Get command line params, allocate memory, call dfs, draw result
*/
int 
main(int argc, char *argv[]) {
    if (argc != 3) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    int n;
    sscanf(argv[1], "%d", &n);

    printf("# Generating an %dx%d maze\n",n,n);

    srandom(time(NULL));

        /* mark all vertices as unvisited */
    visited = allocNbyN(n);
    if (visited == NULL) 
        return EXIT_FAILURE;

        /* Initialise every cell with 4 walls */
    walls = allocNbyN(n);
    if (walls == NULL) 
        return EXIT_FAILURE;

        /* away we go */
    dfs(n, 0, 0);

        /* draw result */
    if (argv[2][0] == 'r')
        drawMazeR(n);
    else if (argv[2][0] == 'a')
        drawMaze(n);
    else {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
