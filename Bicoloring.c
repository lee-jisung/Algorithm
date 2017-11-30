#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNODE 30

#define BLACK 1
#define WHITE 2

#define TRUE 1
#define FALSE 0

typedef struct {
	int node1;
	int node2;
}Edge;

typedef int index;
typedef int bool;

int vcolor[MAXNODE];
int W[MAXNODE][MAXNODE] = { 0, };

void m_coloring(index i, int num);
bool promising(index i);
bool finished;

void main() {

	int num, edge, i, j;
	Edge e[MAXNODE];
	bool check;

	while (1) {

		finished = FALSE;
		
		printf("Type the number of vertex >> ");
		scanf("%d", &num);

		printf("Type the number of edge >> ");
		scanf("%d", &edge);

		for (i = 0; i < edge; i++) {
			scanf("%d %d", &e[i].node1, &e[i].node2);
			W[e[i].node1][e[i].node2] = 1;
			W[e[i].node2][e[i].node1] = 1;
		}

		vcolor[0] = BLACK;
		m_coloring(0, num - 1);

		if (finished)
			printf("\ntwo-color graph\n\n");
		else
			printf("\nnot two-color graph\n\n");
		
		for (i = 0; i < MAXNODE; i++) {
			for (j = 0; j < MAXNODE; j++)
				W[i][j] = 0;
			vcolor[i] = 0;
		}
	}

}

/*
 * Description: this function go through all the nodes recursively, starting with zero
 *              find whether every node can colored by 2 color.
 * Input: ith node, number of node
 * Output: Nothing
*/
void m_coloring(index i, int num) {
	
	index color;

	if (promising(i)) {
		if (i == num) {
			finished = TRUE;
		}
		else {
			for (color = BLACK; color <= WHITE; color++) {
				vcolor[i + 1] = color;
				m_coloring(i + 1, num);
			}
		}
	}

	
}


/*
* Description: Found if ith node can colored or not 
* Input: ith node
* Output: if ith node can be colored return TRUE or not, return FALSE
*/
bool promising(index i) {

	index j = 0;
	bool check = TRUE;
	while (j < i && check) {
		if (W[i][j] && vcolor[i] == vcolor[j])
			check = FALSE;
		j++;
	}
	return check;
}
