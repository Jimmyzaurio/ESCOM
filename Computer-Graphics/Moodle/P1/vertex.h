#ifndef VERTEX
#define VERTEX

#include "bresenham.h"

struct node {
	Coord p;
	struct node* next;
};
typedef struct node Node;

Node* insert(Node *head, Coord p);

#endif