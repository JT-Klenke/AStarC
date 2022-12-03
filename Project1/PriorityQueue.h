#pragma once

struct ResizableArray {
	struct Point** head;
	int size;
	int backingSize;
};

struct Point* pqextractMin(struct ResizableArray* pQueue, struct PointInfo** ppTable);

void queueAdd(struct ResizableArray* pQueue, struct PointInfo** ppTable);
