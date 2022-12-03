#pragma once

struct ResizableArray {
	struct Point* pHead;
	int length; //current number of stored points
	int backingLength; //amount of points thats been allocated
};

struct Point* pqextractMin(struct ResizableArray* pQueue, struct PointInfo** ppTable, struct Point* pReturnPoint);

void queueAdd(struct ResizableArray* pQueue, struct PointInfo** ppTable, struct Point* pPoint);

struct ResizableArray* makeQueue();