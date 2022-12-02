#pragma once
#include "Table.h"

/*
From list:
- get min (removes that element)
- add Point
- contains Point t/f
*/
struct Point {
	int x, y;
};

struct LinkedListNode {
	struct Point p;
	struct LinkedListNode* pNext;
};

struct LinkedList {
	struct LinkedListNode* pFirst;
};


void add(struct LinkedList* pList, struct Point* pPoint);

unsigned char contains(struct LinkedList* pList, struct Point* pPoint);

struct Point* extractMin(struct LinkedList* pList, struct PointInfo** pTable);

void printPoint(struct Point* pPoint);

void printList(struct LinkedList* pList);