#include "Sort.h"

void bubbleSort(std::vector<ValueWithFunc>& vec, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = size - 1; j >= i + 1; j--) {   //Å@âEÇ©ÇÁç∂Ç…ëÄçÏ
			if (vec.at(j) < vec.at(j - 1)) std::swap(vec.at(j), vec.at(j - 1));
		}
	}
}
void shakerSort(std::vector<ValueWithFunc>& vec, int size) {
	int left = 0, right = size - 1, shift = 0;
	while (left < right) {
		for (int i = left; i < right; ++i) {
			if (vec.at(i) > vec.at(i + 1)) {
				std::swap(vec.at(i), vec.at(i + 1));
				shift = i;
			}
		}
		right = shift;
		for (int i = right; i > left; --i) {
			if (vec.at(i) < vec.at(i - 1)) {
				std::swap(vec.at(i), vec.at(i - 1));
				shift = i;
			}
		}
		left = shift;
	}
}
void shellSort(std::vector<ValueWithFunc>& vec, int size) {
	int gap;
	for (gap = 1; gap < size / 3; gap = 3 * gap + 1);
	while (gap > 0) {
		for (int i = gap; i < size; ++i) {
			for (int j = i - gap; j >= 0; j = j - gap) {
				if (vec.at(j) > vec.at(j + gap))std::swap(vec.at(j), vec.at(j + gap));
				else break;
			}
		}
		gap = gap / 3;
	}
}

void insertionSort(std::vector<ValueWithFunc>& vec, int size) {
	for (int i = 1; i < size; ++i) {
		for (int j = i - 1; j >= 0 && (vec[j] > vec[j + 1]); --j)
			std::swap(vec[j], vec[j + 1]);
	}
}

void selectionSort(std::vector<ValueWithFunc>& vec, int size) {
	 for (int i = 0; i < size; ++i) {
		ValueWithFunc min = vec[i];
		int minPlace = i;
		for (int j = i + 1; j < size; ++j) {
			if (min > vec[j]) {
				min = vec[j];
				minPlace = j;
			}
		}
		std::swap(vec[i], vec[minPlace]);
	}
}