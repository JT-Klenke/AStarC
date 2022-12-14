#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Table.h"
#include "AStarCode.h"
#include "PriorityQueue.h"


int main(int argc, char** argv) {
	/*
	struct LinkedList theList;
	struct PointInfo** ppTable;
	struct PointInfo* pP22Info;
	struct Point* min;
	struct Point p1;
	p1.x = 0;
	p1.y = 0;

	struct Point p2;
	p2.x = 30;
	p2.y = 40;

	struct Point p3;
	p3.x = 30;
	p3.y = 10;

	
	ppTable = makeTable();

	putInfo(ppTable, p1.x, p1.y, 100, 100, &p2);
	putInfo(ppTable, p2.x, p2.y, 100, 100, &p3);
	putInfo(ppTable, p3.x, p3.y, 10, 100, &p3);

	
	
	theList.pFirst = NULL;
	add(&theList, &p2);
	add(&theList, &p1);
	add(&theList, &p3);
	

	min = extractMin(&theList, ppTable);

	printf("%d,%d\n\n\n", min->x, min->y);

	pP22Info = getInfo(ppTable, 30, 40);

	printf("%d\n", pP22Info->gCost);

	printf("%d\n", pP22Info->hCost);

	printf("%d\n\n", (pP22Info->parent)->x);
	



	printf("list: ");
	printList(&theList);

	printf("p1: %d\n", contains(&theList, &p1));

	printf("p2: %d\n",contains(&theList, &p2));

	printf("p3: %d\n", contains(&theList, &p3));
	*/

	struct PointInfo** ppTable, *pInfo;
	struct LinkedList* pPath;
	struct ResizableArray* pQueue;
	int i, startBox, endBox;
	ppTable = makeTable();
	pQueue = makeQueue();

	
	startBox = 2;
	endBox = 666;

	for (i = startBox; i <= endBox; i++) {
		makeObstacle(ppTable, startBox, i);
		makeObstacle(ppTable, i, startBox);
		makeObstacle(ppTable, endBox, i);
		makeObstacle(ppTable, i, endBox);
	}

	makeObstacle(ppTable, 1, 4);
	removeObstacle(ppTable, startBox, startBox);
	removeObstacle(ppTable, startBox+1, startBox);
	removeObstacle(ppTable, startBox, startBox+1);
	
	//makeObstacle(ppTable, 1, 1);


	pPath = findPath(ppTable, 0, 0, 999, 999);
	

	//printf("%d", pInfo->isObstacle);

	printList(pPath);

	
	return 0;
}