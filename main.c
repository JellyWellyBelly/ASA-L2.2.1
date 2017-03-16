#include "mymacros.h"

int main() {
	
	int nr_vertices;
	int nr_input_lines;
	int vertex1;
	int vertex2;
	int i = 0;

	scanf("%d %d", &nr_vertices, &nr_input_lines); 		//le a primeira linha do stdin

	//Node *graph = malloc(sizeof(Node) * nr_vertices);	//Grafo representado num vetor de listas de adjancencias
	
	while(i < nr_input_lines) {
		scanf("%d %d", &vertex1, &vertex2);
		insert_list(graph[vertex1], vertex2);

		i++;
	}

	return 0;
}