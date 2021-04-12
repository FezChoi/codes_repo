#include <iostream>

using namespace std;

const int STACK_SIZE = 10;

int stack[STACK_SIZE] = { 0, };
int top = -1;

bool isFull() {
	if (top >= STACK_SIZE - 1)
		return true;
	else
		return false;
}

bool isEmpty() {
	if (top < 0)
		return true;
	else
		return false;
}

void push(int val) {
	if (isFull())
		cout << "Stack Overflow !! \n" << endl;
	else
		stack[++top] = val;
}

int pop() {
	if (isEmpty()) {
		cout << "Stack Underflow !! \n" << endl;
		return -1;
	}
	else {
		//return stack[top--];
		int ret = stack[top];
		stack[top--] = 0;
		return ret;
	}
}

int pick() {
	if (isEmpty()) {
		cout << "Stack Underflow !! \n" << endl;
		return -1;
	}
	else
		return stack[top];
}

int main() {

	for (int i = 1; i < 13; i++)
		push(i);

	while (!isEmpty())
		cout << pop() << " ";

	cout << endl;

	return 0;
}