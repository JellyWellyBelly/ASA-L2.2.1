#include <stdlib.h>
#include <stdio.h>
#define WHITE 0
#define GREY 1
#define BLACK 2
#define TRUE 0
#define FALSE 1


typedef struct node {

	int value;
	struct node *next;

} *Node;



int flag_insuficiente = FALSE;
int flag_incoerente = FALSE;
int nr_vertices = 0;
int nr_input_lines = 0;
int count_order = 0;
int *colors;
Node order;




void DFS(Node *graph, Node *graph_dads);
void DFS_visit(int index, Node *graph);
void print(Node head);
Node insert_list(Node head, int value);
int exist(Node *graph, int u, int v);


int main() {
	
	
	int vertex1;
	int vertex2;
	
	int i = 0;
	

	if(!scanf("%d %d", &nr_vertices, &nr_input_lines)) return -1; 		

	Node graph[nr_vertices];

	Node graph_dads[nr_vertices];

	colors = (int*) malloc(sizeof(int)*nr_vertices);

	for (i = 0; i < nr_vertices; ++i){

		colors[i] = WHITE;
		graph[i] = NULL;
		graph_dads[i] = NULL;
	}

	
	for (i = 0; i < nr_input_lines; ++i){

		if(!scanf("%d %d", &vertex1, &vertex2)) return -1;
		graph[vertex1 - 1] = insert_list(graph[vertex1 - 1], vertex2 - 1);
		graph_dads[vertex2 - 1] = insert_list(graph_dads[vertex2 - 1], vertex1 - 1);

	}
	
	DFS(graph, graph_dads);

	if (flag_incoerente == TRUE || count_order != nr_vertices)
	{
		printf("Incoerente\n");
	}

	else if (flag_insuficiente == TRUE)
	{
		printf("Insuficiente\n");
	}
	
	/* confirmar a ordem topologica a ver se 'e unico ou nao */
	else {
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




void DFS(Node *graph, Node *graph_dads){

	int count_orphans = 0;
	int i;

	for (i = 0; i < nr_vertices; ++i){

		if(graph_dads[i] == NULL && flag_incoerente == FALSE){
			count_orphans++;
			DFS_visit(i, graph);
		}
	}
	
	if (count_orphans >= 2){
		flag_insuficiente = TRUE;
	}

	else if (count_orphans < 1)	{
		flag_incoerente = TRUE;
	}
}


void DFS_visit(int index, Node *graph){

	colors[index] = GREY;
	Node t;

	for(t = graph[index]; t != NULL; t = t->next){

		if (colors[t->value] == GREY){
			flag_incoerente = TRUE;
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


void print(Node head) {
	Node t;

	printf("%d",head->value);

	for(t = head->next; t != NULL; t = t->next){
		printf(" %d",t->value);
	}
	printf("\n");
} 



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

int exist(Node *graph, int u, int v) {
	Node g;
	
	for (g = graph[u-1]; g != NULL ; g = g->next) {
		if (g->value == v-1) {
			return TRUE;
		}
	}
	return FALSE;
}