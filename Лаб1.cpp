#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <fstream>


using namespace std;

void fillRandomArray(int arr[], const int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 201;
	}
}

void fillSortArray(int arr[], const int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = i;
	}
}

void fillReverseArray(int arr[], const int size) {
	for (int i = size - 1; i > 0; i--) {
		arr[size - i - 1] = i;
	}
}

// Простой выбор

void SelectionSort(int arr[], const int size, ofstream& FILE) {

	int a, b, index, swapp = 0, count = 0;

	for (a = 0; a < size - 1; a++) {
		index = a;
		count++;
		for (b = a + 1; b < size; b++)
			if (arr[b] < arr[index]) {
				index = b;
				swapp++;
			}
		swap(arr[a], arr[index]);

	}
	FILE << "swap = " << swapp << "count = " << count << ";";
}

// Простой обмен

void BubbleSort(int arr[], const int size, ofstream& FILE) {

	int a, b, swapp = 0, count = 0;
	for (a = 0; a < size - 1; a++)
		for (b = size - 1; b > a; b--) {
			count++;
			if (arr[b - 1] > arr[b]) {
				swapp++;
				swap(arr[b - 1], arr[b]);
			}
		}
	FILE << "swap = " << swapp << "count = " << count << ";";
}

// Простая вставка

void InsertionSort(int arr[], const int size, ofstream& FILE) {

	int a, b, swapp = 0, count = 0;
	int temp;

	for (a = 1; a < size; a++) {
		b = a;
		temp = arr[a];
		count++;
		while (b > 0 && temp < arr[b - 1]) {

			arr[b] = arr[b - 1];
			b--;
			swapp++;
		}
		arr[b] = temp;
	}
	FILE << "swap = " << swapp << "count = " << count << ";";
}

// Бинарная вставка

void binaryInput(int arr[], const int size, ofstream& FILE) {

	int x, left, right, middle, swapp = 0, count = 0;

	for (int i = 1; i < size; i++) {
		if (arr[i - 1] > arr[i]) {
			x = arr[i];
			left = 0;
			right = i - 1;
			do {
				count++;
				middle = (left + right) / 2;
				if (arr[middle] < x)
					left = middle + 1;
				else
					right = middle - 1;
			} while (left <= right);
			for (int j = i - 1; j >= left; j--)
			{
				swapp++;
				arr[j + 1] = arr[j];
			}
			arr[left] = x;
		}
	}
	FILE << "swap = " << swapp << "count = " << count << ";";
}

// Шейкер-сортировка

void sheiker(int arr[], int const size, ofstream& FILE) {
	int l = 1, r = size - 1, k = size - 1, j, swapp = 0, count = 0;
	while (l <= r) {
		for (int j = r; j >= l; j--) {
			count++;
			if (arr[j - 1] > arr[j]) {
				swapp++;
				int x = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = x;
				k = j;
			}
		}
		l = k + 1;
		for (j = l; j <= r; j++) {
			count++;
			if (arr[j - 1] > arr[j]) {
				swapp++;
				int x = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = x;
				k = j;
			}
		}
		r = k - 1;
	}
	FILE << "swap = " << swapp << "count = " << count << ";";
}

// Сортировка Шелла

void shell_sort(int arr[], int const size, ofstream& FILE) {

	int i, j, h, count = 0, swapp = 0;
	for (h = 1; h <= size / 9; h = h * 3 + 1);
	while (h >= 1) {
		for (i = h; i < size; i++) {
			count++;
			for (j = i - h; j >= 0 && arr[j] > arr[j + h]; j -= h) {
				swapp++;
				swap(arr[j], arr[j + h]);
			}
		}
		h = (h - 1) / 3;
	}
	FILE << "swap = " << swapp << "count = " << count << ";";
}

// Пирамидальная сортировка

void heapify(int arr[], int size, int i, int& swapp, int& count) {

	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < size && arr[l] > arr[largest])
		largest = l;
	count++;

	if (r < size && arr[r] > arr[largest])
		largest = r;
	count++;

	if (largest != i) {

		swapp++;
		swap(arr[i], arr[largest]);
		heapify(arr, size, largest, swapp, count);
	}
}

void heapSort(int arr[], int const size, ofstream& FILE) {
	int swapp = 0, count = 0;

	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(arr, size, i, swapp, count);

	for (int i = size - 1; i >= 0; i--) {
		swapp++;
		swap(arr[0], arr[i]);
		heapify(arr, i, 0, swapp, count);
	}
	FILE << "swap = " << swapp << "count = " << count << ";";
}

// Быстрая сортировка

void QuickSort(int arr[], int p, int r, int& swapp, int& count)
{
	int i, j;
	int x;
	i = p;
	j = r;
	x = arr[(i + j) / 2];
	do
	{
		while (arr[i] < x) i++;
		while (arr[j] > x) j--;
		count++;
		if (i <= j)
		{
			swapp++;
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (j > p)
		QuickSort(arr, p, j, swapp, count);
	if (i < r)
		QuickSort(arr, i, r, swapp, count);
}

int main() {

	const int size = 200;
	int arr[size]{ };

	ofstream FILE;
	FILE.open("Result.csv");
	FILE << "Random; Sort; Reverse" << endl;

	// Простой выбор

	fillRandomArray(arr, size);
	SelectionSort(arr, size, FILE);

	fillSortArray(arr, size);
	SelectionSort(arr, size, FILE);

	fillReverseArray(arr, size);
	SelectionSort(arr, size, FILE);
	FILE << endl;

	// Простой обмен

	fillRandomArray(arr, size);
	BubbleSort(arr, size, FILE);

	fillSortArray(arr, size);
	BubbleSort(arr, size, FILE);

	fillReverseArray(arr, size);
	BubbleSort(arr, size, FILE);
	FILE << endl;

	// Простая вставка

	fillRandomArray(arr, size);
	InsertionSort(arr, size, FILE);

	fillSortArray(arr, size);
	InsertionSort(arr, size, FILE);

	fillReverseArray(arr, size);
	InsertionSort(arr, size, FILE);
	FILE << endl;

	// Бинарная вставка

	fillRandomArray(arr, size);
	binaryInput(arr, size, FILE);

	fillSortArray(arr, size);
	binaryInput(arr, size, FILE);

	fillReverseArray(arr, size);
	binaryInput(arr, size, FILE);
	FILE << endl;

	// Шейкер-сортировка

	fillRandomArray(arr, size);
	sheiker(arr, size, FILE);

	fillSortArray(arr, size);
	sheiker(arr, size, FILE);

	fillReverseArray(arr, size);
	sheiker(arr, size, FILE);
	FILE << endl;

	// Сортировка Шелла

	fillRandomArray(arr, size);
	shell_sort(arr, size, FILE);

	fillSortArray(arr, size);
	shell_sort(arr, size, FILE);

	fillReverseArray(arr, size);
	shell_sort(arr, size, FILE);
	FILE << endl;

	// Пирамидальная сортировка

	fillRandomArray(arr, size);
	heapSort(arr, size, FILE);

	fillSortArray(arr, size);
	heapSort(arr, size, FILE);

	fillReverseArray(arr, size);
	heapSort(arr, size, FILE);
	FILE << endl;

	// Быстрая сортировка

	int swapp = 0, count = 0;

	fillRandomArray(arr, size);
	QuickSort(arr, 0, size - 1, swapp, count);
	FILE << "swap = " << swapp << "count = " << count << ";";

	swapp = 0, count = 0;

	fillSortArray(arr, size);
	QuickSort(arr, 0, size - 1, swapp, count);
	FILE << "swap = " << swapp << "count = " << count << ";";

	swapp = 0, count = 0;

	fillReverseArray(arr, size);
	QuickSort(arr, 0, size - 1, swapp, count);
	FILE << "swap = " << swapp << "count = " << count << ";";

	FILE.close();
}