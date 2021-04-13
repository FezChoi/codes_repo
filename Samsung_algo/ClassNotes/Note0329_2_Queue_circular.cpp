#include <iostream>

using namespace std;

// 원형 큐 정의
const int QUEUE_SIZE = 10;
int q[QUEUE_SIZE] = { 0, };
int front = 0;
int rear = 0;


bool isQFull() {
	if ((rear + 1) % QUEUE_SIZE == front)
		return true;
	else
		return false;
}

bool isQEmpty() {
	if (front == rear)
		return true;
	else
		return false;
}

void enQueue(int val) {
	if (isQFull())
		cout << "Queue Overflow !! \n";
	else {
		rear = (rear + 1) % QUEUE_SIZE;
		q[rear] = val;
	}
}

int deQueue() {
	if (isQEmpty())
		cout << "Queue Underflow !! \n";
	else {
		front = (front + 1) % QUEUE_SIZE;
		
		int ret = q[front];
		q[front] = 0;
		return ret;				// 이 형태가 디버깅에 유리.
	}
		
}

int Qpeek() {
	if (isQEmpty())
		cout << "Queue Underflow !! \n";
	else
		return q[(front + 1) % QUEUE_SIZE];
}

int main() {
	
	for (int i = 1; i < 13; i++) {
		enQueue(i);
	}

	while (!isQEmpty()) {
		cout << deQueue() << " ";
	}
	cout << endl;

	enQueue(50);
	cout << deQueue() << endl;

	return 0;
}