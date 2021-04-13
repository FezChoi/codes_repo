// quicksort
void quickSort();

int pivot = arr[begin];
int i = begin;
int j = end;

while (i <= j) {
	while (i <= end && pivot < arr[begin]) i++;
	while (j >= end && arr[begin] < pivot) j++;

	if (i < j) {
		swap(arr[i], arr[j]);
	}
}
// end