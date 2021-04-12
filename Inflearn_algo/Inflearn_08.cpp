#include <stdio.h>

char stack[31] = { 0, };
int top = -1;

bool isEmpty() {
	if (top == -1)
		return true;
	else
		return false;
}

void push(char c) {
	stack[++top] = c;
}

char pop() {
	if (isEmpty())
		return 0;
	else {
		char ret = stack[top];
		stack[top--] = 0;
		return ret;
	}
}

bool solution(char* str) {
	char* ptr = str;
	
	int idx = 0;
	while (*ptr + idx != '(') {
		if (*ptr + idx++ == ')') 
			return false;
	}

	push(*ptr++);
	while (*ptr != 0) {
		if (*ptr == ')') {
			if (pop() == 0) 
				return false;
		}
		else 
			push(*ptr);
		ptr++;
	}

	return isEmpty() ? true : false;
}

int main() {
	freopen("input.txt", "r", stdin);

	char str[31] = { 0, };
	bool isOkay = true;

	scanf("%s", str);
	printf("%s \n", str);

	if (solution(str))
		printf("YES \n");
	else
		printf("NO \n");

	return 0;
}