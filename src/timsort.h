#include <iostream> 
#include "Property.h"
using namespace std; 
const int RUN = 32; 

// This function sorts array from left 
// index to to right index which is 
// of size atmost RUN 
void insertionSort(shared_ptr<Vlist<Property>> arr, int left, int right, int type) 
{ 
	for (int i = left + 1; i <= right; i++) { 
		Property temp = (*arr)[i]; 
		int j = i - 1; 
		switch(type){
			case(1):
				while (j >= left && (*arr)[j].prop_name > temp.prop_name) { 
					(*arr)[j + 1] = (*arr)[j]; 
					j--; 
				} 
				break;
			case(2):
				while (j >= left && (*arr)[j].monthly_rent > temp.monthly_rent) { 
					(*arr)[j + 1] = (*arr)[j]; 
					j--; 
				}
				break;
			case(3):
				while (j >= left && (*arr)[j].room > temp.room) { 
					(*arr)[j + 1] = (*arr)[j]; 
					j--; 
				} 
				break;
		}
		(*arr)[j + 1] = temp; 
	} 
} 

// Merge function merges the sorted runs 
void merge(shared_ptr<Vlist<Property>> arr, int l, int m, int r, int type) {
	// Original array is broken in two 
	// parts left and right array 
	int lenLeft = m - l + 1, lenRight = r - m;
	Vlist<Property>left(lenLeft), right(lenRight); 
	for (int i = 0; i < lenLeft; i++)
		left.pushBack((*arr)[l + i]); 
	for (int i = 0; i < lenRight; i++) 
		right.pushBack((*arr)[m + 1 + i]); 

	int i = 0; 
	int j = 0; 
	int k = l; 

	// After comparing, we 
	// merge those two array 
	// in larger sub array 
	while (i < lenLeft && j < lenRight) { 
		switch(type){
			case(1):
				if (left[i].prop_name <= right[j].prop_name) { 
					(*arr)[k] = left[i]; 
					i++; 
				} 
				else { 
					(*arr)[k] = right[j]; 
					j++; 
				}	
				break;
			case(2):
				if (left[i].monthly_rent <= right[j].monthly_rent) { 
					(*arr)[k] = left[i]; 
					i++; 
				} 
				else { 
					(*arr)[k] = right[j]; 
					j++; 
				}
				break;
			case(3):
				if (left[i].room <= right[j].room) { 
					(*arr)[k] = left[i]; 
					i++; 
				} 
				else { 
					(*arr)[k] = right[j]; 
					j++; 
				}
				break;
		}
		k++; 
	} 

	// Copy remaining elements of 
	// left, if any 
	while (i < lenLeft) { 
		(*arr)[k] = left[i]; 
		k++; 
		i++; 
	} 

	// Copy remaining element of 
	// right, if any 
	while (j < lenRight) { 
		(*arr)[k] = right[j]; 
		k++; 
		j++; 
	} 
	cout << "done merge" << endl;

} 

// Utility function to print the Array 
void printTim(Vlist<Property>& arr, int n) 
{  
	cout << "Sorted Array: " << endl;
    for (int i = 0; i < n; ++i) {
        cout << arr[i].toCSVFormat() << endl;
    }
} 

// Iterative Timsort function to sort the 
// array[0...n-1] (similar to merge sort) 
void timSort(shared_ptr<Vlist<Property>> arr, int n, int type) 
{ 
	for (int i = 0; i < n; i += RUN) 
		insertionSort(arr, i, min((i + RUN - 1), (n - 1)),type); 

	for (int size = RUN; size < n; size = 2 * size) { 

		for (int left = 0; left < n; left += 2 * size) { 
			int mid = left + size - 1; 
			int right = min((left + 2 * size - 1), (n - 1)); 

			if (mid < right) 
				merge(arr, left, mid, right, type); 
		} 
	} 
}

