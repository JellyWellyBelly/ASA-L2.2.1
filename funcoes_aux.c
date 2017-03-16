//Estrutura de Dados da lista de adjacencias

typedef struct node {

	int value;
	struct node *next;

} Node;

Node insert_list(Node **head, int value) {
	Node *new_node;
    new_node = malloc(sizeof(Node));

    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

void free_list(Node head) {
    if (current != NULL) {
    	free_list(head->next);
        free(*head);
    }
}