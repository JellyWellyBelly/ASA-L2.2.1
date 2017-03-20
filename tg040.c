	/* * * * * * * * * * * * * * * * * * * *
	 *  	Instituto Superior Técnico     *
	 *                                     *
	 *  Authors: Antonio Terra, nr. 84702  *
	 *			 Miguel Viegas, nr. 84747  *
	 * 									   *
	 *  Under tutoring of Professor        *
	 *		Luis Manuel Silveira Russo     *
	 *									   *
	 * * * * * * * * * * * * * * * * * * * */

#include <stdlib.h>
#include <stdio.h>


	  /* * * * * * * * * * * *
	   *   Data structures   *
	   * * * * * * * * * * * */

    	 /* Linked List */

typedef struct node {

	int value;
	struct node *next;

} *Node;


	/* * * * * * * * * * * * *
	 *      Macros &         *
	 *   Global Variables    *
	 * * * * * * * * * * * * */


#define WHITE 0
#define GREY 1
#define BLACK 2
#define TRUE 0
#define FALSE 1

int flag_insufficient = FALSE;
int flag_inconsistent = FALSE;
int nr_vertices = 0;
int nr_input_lines = 0;
int count_order = 0;
int *colors;
Node order;


	/* * * * * * * * * *
	 *   Prototypes    *
	 * * * * * * * * * */


void DFS(Node *graph, Node *graph_dads);
void DFS_visit(int index, Node *graph);
void print(Node head);
Node insert_list(Node head, int value);
int exist(Node *graph, int u, int v);






	/* * * * * * *
	 *   Main    *
	 * * * * * * */

int main() {
	
	int vertex1;
	int vertex2;
	int i = 0;
	

	if(!scanf("%d %d", &nr_vertices, &nr_input_lines)) return -1; 	/* Reads the first line of the input */

	Node graph[nr_vertices];
	Node graph_dads[nr_vertices];
	colors = (int*) malloc(sizeof(int)*nr_vertices);


	for (i = 0; i < nr_vertices; ++i){  	/* Initializes the graph and the color's vector */
		colors[i] = WHITE;
		graph[i] = NULL;
		graph_dads[i] = NULL;
	}

	
	for (i = 0; i < nr_input_lines; ++i){ 		/* Registers the input and stores the graph */
		if(!scanf("%d %d", &vertex1, &vertex2)) return -1;
		graph[vertex1 - 1] = insert_list(graph[vertex1 - 1], vertex2 - 1);
		graph_dads[vertex2 - 1] = insert_list(graph_dads[vertex2 - 1], vertex1 - 1);
	}
	
	DFS(graph, graph_dads);		/* Processes the graph and checks if there is a unique topological order and no cycles */

	if (flag_inconsistent == TRUE || count_order != nr_vertices) printf("Incoerente\n"); /* It's not consistent */
	else if (flag_insufficient == TRUE) printf("Insuficiente\n"); /* It's not sufficient */
	
	else {	/* If the topological order is a hamiltonian path then it's the unique topological order */
		Node t;
		for (t = order; (t->next) != NULL; t = t->next) {
			if(exist(graph, t->value, (t->next)->value) == FALSE){
				printf("Insuficiente\n");
				return 0;
			}
		}
		print(order);
	}

	return 0;
}





/* DFS algorithm - modified */

void DFS(Node *graph, Node *graph_dads){

	int count_orphans = 0;
	int i;

	for (i = 0; i < nr_vertices; ++i){

		if(graph_dads[i] == NULL && flag_inconsistent == FALSE){
			count_orphans++;
			DFS_visit(i, graph);
		}
	}
	
	if (count_orphans >= 2){
		flag_insufficient = TRUE;
	}

	else if (count_orphans < 1)	{
		flag_inconsistent = TRUE;
	}
}
void DFS_visit(int index, Node *graph){

	colors[index] = GREY;
	Node t;

	for(t = graph[index]; t != NULL; t = t->next){

		if (colors[t->value] == GREY){
			flag_inconsistent = TRUE;
			return;
		}

		else if (colors[t->value] == WHITE){
			DFS_visit(t->value, graph);
		}

	}

	colors[index] = BLACK;
	order = insert_list(order, index + 1);
	count_order++;
}



/* Linked list functions */

Node insert_list(Node head, int value) {
	Node new_node;
    new_node = (Node)malloc(sizeof(struct node));

    if (head == NULL)
    {
    	new_node->value = value;
    	return new_node;
    }

    new_node->value = value;
    new_node->next = head;
    return new_node;
}

void print(Node head) {
	Node t;

	printf("%d",head->value);

	for(t = head->next; t != NULL; t = t->next){
		printf(" %d",t->value);
	}
	printf("\n");
}



/* Auxilar functions */

int exist(Node *graph, int u, int v) {
	Node g;
	
	for (g = graph[u-1]; g != NULL ; g = g->next) {
		if (g->value == v-1) {
			return TRUE;
		}
	}
	return FALSE;
}
