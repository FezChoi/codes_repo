#include <iostream>
#include <math.h>

#define INFI 987654321
#define MAX_N 100

using namespace std;

typedef struct POS {
	int x, y;
	int dx, dy;
	double slope;
} Pos;

Pos init = { 0, };
Pos points[MAX_N] = { 0, };
Pos stack[MAX_N] = { 0, };
int top = -1;
int NUM_POINTS = 0;

void swap_Pos(int idx1, int idx2) {
	Pos tmp = points[idx1];
	points[idx1] = points[idx2];
	points[idx2] = tmp;
}

void sort_by_slope() {
	Pos O = points[0];

	for (int i = 1; i < NUM_POINTS; i++) {
		points[i].dx = points[i].x - O.x;
		points[i].dy = points[i].y - O.y;
		points[i].slope = atan2((double)points[i].dy, (double)points[i].dx);
	}

	for (int i = 1; i < NUM_POINTS; i++) {
		for (int j = i + 1; j < NUM_POINTS; j++) {
			if (points[i].slope > points[j].slope) {
				swap_Pos(i, j);
			}
		}
	}
}

double area_triangle(Pos O, Pos A, Pos B) {
	double OA = sqrt(pow(A.dx, 2) + pow(A.dy, 2));
	double OB = sqrt(pow(B.dx, 2) + pow(B.dy, 2));
	double theta = atan2((double)A.dy, (double)A.dx) - atan2((double)B.dy, (double)B.dx);

	return 0.5 * OA * OB * abs(sin(theta));
}

int ccw_algorithm(Pos A, Pos B, Pos C) {
	return (B.x - A.x)*(C.y - A.y) - (B.y - A.y)*(C.x - A.x);
}

void graham_algorithm() {
	sort_by_slope();

	stack[++top] = points[0];
	stack[++top] = points[1];
	stack[++top] = points[2];

	for (int i = 3; i < NUM_POINTS; i++) {
		while (ccw_algorithm(stack[top - 1], stack[top], points[i]) <= 0) {
			stack[top--] = init;
		}
		stack[++top] = points[i];
	}
}

double solution() {
	graham_algorithm();

	double total_area = 0;

	for (int i = 1; i < top; i++) {
		total_area += area_triangle(stack[0], stack[i], stack[i + 1]);
	}

	return total_area;
}


int main() {
	ios::sync_with_stdio(false);

	int N;
	cin >> N;

	NUM_POINTS = N;
	int min_x = INFI;
	for (int i = 0; i < N; i++) {
		cin >> points[i].x >> points[i].y;
		points[i].slope = 0;

		if (min_x > points[i].x) {
			min_x = points[i].x;
			swap_Pos(0, i);
		}
	}

	double answer = solution();

	cout << (int)(answer + 0.5) << endl;

	return 0;
}