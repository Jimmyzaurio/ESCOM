// Author: Saucedo Pérez Jesús
#include <stdio.h>
#include <stdlib.h>

struct node {
	double x,y,z;
	struct node* next;
};
typedef struct node Node;

Node* insert(Node *head, double x, double y, double z) {
	Node* nuevo = NULL;
	nuevo = (Node*)malloc(sizeof(Node));

	nuevo->x = x;
	nuevo->y = y;
	nuevo->z = z;
	nuevo->next = NULL;

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

void show(Node* head) {
	while (head != NULL) {
		printf("%lf %lf %lf\n", head->x, head->y, head->z);
		head = head->next;
	}
}

int main() {
	FILE *fp = NULL;
	char cad[4];
	char buf[10000];
	double x, y, z;

	fp = fopen("3d.obj", "r");

	if (fp == NULL) {
		perror("Can't open file\n");
	}

	Node* data = NULL;
	rewind(fp);
	while (fgets(buf, sizeof buf, fp) != NULL) {
		if (buf[0] == 'v' && buf[1] != 't') { // valid information
			fscanf(fp, "%s %lf %lf %lf", cad, &x, &y, &z);
			//printf("***  %s %lf %lf %lf\n", cad, x, y, z);
			data = insert(data, x, y, z);
		}
	}
	fclose(fp);
	show(data);
	return 0;
}
