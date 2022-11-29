#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Table.h"


int main(int argc, char** argv) {
	
	struct LinkedList theList;
	struct PointInfo** ppTable;
	//struct PointInfo* pP22Info;
	struct Point* min;
	struct Point p1;
	p1.x = 1;
	p1.y = 2;

	struct Point p2;
	p2.x = 3;
	p2.y = 4;

	struct Point p3;
	p3.x = 3;
	p3.y = 1;

	
	ppTable = makeTable();

	putInfo(ppTable, 100, 200, 1, 16, &p2);
	putInfo(ppTable, 300, 400, 10, 100, &p3);
	putInfo(ppTable, 3, 100, 16, 17, &p3);

	
	
	theList.pFirst = 0;
	add(&theList, &p2);
	add(&theList, &p1);
	add(&theList, &p3);
	

	min = extractMin(&theList, ppTable);

	printf("%d,%d\n\n\n", min->x, min->y);

	/*
	pP22Info = getInfo(pTable, 1, 2);

	printf("%d\n", pP22Info->gCost);

	printf("%d\n", pP22Info->hCost);

	printf("%d\n\n", (pP22Info->parent)->x);
	*/



	printf("list: ");
	printList(&theList);

	printf("p1: %d\n", contains(&theList, &p1));

	printf("p2: %d\n",contains(&theList, &p2));

	printf("p3: %d\n", contains(&theList, &p3));
	
	
	
	return 0;
}