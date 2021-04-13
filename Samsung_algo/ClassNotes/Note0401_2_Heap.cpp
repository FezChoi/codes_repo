#include <iostream>
#define swap(a, b) { int tmp; tmp = a; a = b; b = tmp; }

using namespace std;

const int HEAP_SIZE = 50;

int heap[HEAP_SIZE] = { 0, };
int heapCount = 0;

void push(int value) {
	heap[++heapCount] = value;

	int child = heapCount;
	int parent = child >> 1;

	// Up Heap
	while (parent > 0 && heap[parent] > heap[child]) {
		swap(heap[parent], heap[child]);
		
		child = parent;
		parent = child >> 1;
	}
}

// pQ로 운영하는 경우 extractMin(), extractMax() 이름을 사용함.
int pop() {
	int parent = 1;
	int ret = heap[parent];

	heap[parent] = heap[heapCount];
	heap[heapCount--] = 0;

	int child = parent << 1;	   // left child
	if (child + 1 <= heapCount) {  // if right child exists
		child = (heap[child] < heap[child + 1]) ? child : child + 1;
	}

	// Down Heap
	while (child <= heapCount && heap[parent] > heap[child]) {
		swap(heap[parent], heap[child]);

		parent = child;
		child = parent << 1;

		if (child + 1 <= heapCount) {  // if right child exists
			child = (heap[child] < heap[child + 1]) ? child : child + 1;
		}
	}

	return ret;
}

void printHeap() {
	int pow2[] = { 1, 2, 4, 8, 16, 32, 64 };
	int nextLevel = 1;

	for (int i = 1; i < HEAP_SIZE; i++) {
		if (i == pow2[nextLevel]) {
			cout << endl;
			nextLevel++;
		}
		if (heap[i]) {
			cout << heap[i] << " ";
		}
	}
	cout << endl;
}


int main() {
	push(20);
	push(17);
	push(19);
	push(4);
	push(13);
	push(11);
	push(23);

	printHeap();

	cout << pop() << endl << endl;

	printHeap();


	return 0;
}