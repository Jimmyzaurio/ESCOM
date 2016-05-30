// Author: Jesús Saucedo Pérez
#include "vertex.h"

Node* insert(Node *head, Coord p) {
	Node* nuevo = NULL;
	nuevo = (Node*)malloc(sizeof(Node));

	nuevo -> p = p;
	nuevo -> next = NULL;

	if (head == NULL) {
		head = nuevo;
	} else {
		Node* last = head;
		while (last->next != NULL)
			last = last->next;
		last->next = nuevo;
	}
	return head;
}