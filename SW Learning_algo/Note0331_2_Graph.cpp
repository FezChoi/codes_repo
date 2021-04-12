#include <iostream>

using namespace std;


const int GRAPH_SIZE = 10;
int G[GRAPH_SIZE][GRAPH_SIZE] = { 0, }; // ÀÎÁ¢Çà·Ä
int V;
int E;

bool visited[GRAPH_SIZE] = { false, };

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

void dfs_loop(int v) {
	// stack ÁØºñ
	// visited[] <- false

	push(v);

	while (!isEmpty()) {
		v = pop();

		if (visited[v] == false) {
			visited[v] = true;
			cout << v << " ";

			for (int w = V; w; w--) {
				if (G[v][w] == 1 && visited[w] == false)
					push(w);
			}
		}
	}
}

void dfs_recursive(int v) {
	visited[v] = true;
	cout << v << " ";

	for (int w = 1; w <= V; w++) {
		if (G[v][w] == 1 && visited[w] == false)
			dfs_recursive(w);
	}
}


const int QUEUE_SIZE = 10;
int q[QUEUE_SIZE] = { 0, };
int front = -1;
int rear = -1;

bool isQFull() {
	if (rear + 1 >= QUEUE_SIZE)
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
	else
		q[++rear] = val;
}

int deQueue() {
	if (isQEmpty())
		cout << "Queue Underflow !! \n";
	else {
		//return q[++front];
		int ret = q[++front];
		q[front] = 0;
		return ret;				// ÀÌ ÇüÅÂ°¡ µð¹ö±ë¿¡ À¯¸®.
	}

}

void bfs_loop(int v) {
	// stack ÁØºñ
	// visited[] <- false

	enQueue(v);

	while (!isQEmpty()) {
		v = deQueue();

		if (visited[v] == false) {
			visited[v] = true;
			cout << v << " ";

			for (int w = 1; w <= V; w++) {
				if (G[v][w] == 1 && visited[w] == false) {
					enQueue(w);
				}
			}
		}
	}

	
}


void initVisited() {
	for (int i = GRAPH_SIZE - 1; i; i--)
		visited[i] = false;
}

int main() {
	freopen("graph_input.txt", "r", stdin);

	cin >> V >> E;

	for (int i = 0; i < E; i++) {
		int begin, end;
		cin >> begin >> end;

		G[begin][end] = G[end][begin] = 1;
	}

	cout << "±íÀÌ¿ì¼±Å½»ö(¹Ýº¹)" << endl;
	dfs_loop(1);
	cout << endl;

	cout << "±íÀÌ¿ì¼±Å½»ö(Àç±Í)" << endl;
	initVisited();
	dfs_recursive(1);
	cout << endl;

	cout << "±íÀÌ¿ì¼±Å½»ö(Àç±Í)" << endl;
	initVisited();
	bfs_loop(1);
	cout << endl;

	return 0;
}