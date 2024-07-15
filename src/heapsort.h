#include <iostream>
#include "Property.h"
using namespace std;

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(Vlist<Property>& arr, int N, int i, int Type) {
    // Initialize largest as root
    int largest = i;

    // left = 2*i + 1
    int l = 2 * i + 1;

    // right = 2*i + 2
    int r = 2 * i + 2;

    switch(Type){
        case(1):
            // If left child is larger than root
            if (l < N && arr[l].prop_name > arr[largest].prop_name)
                largest = l;

            // If right child is larger than largest
            // so far
            if (r < N && arr[r].prop_name > arr[largest].prop_name)
                largest = r;
            break;
        case(2):
            // If left child is larger than root
            if (l < N && arr[l].monthly_rent > arr[largest].monthly_rent)
                largest = l;

            // If right child is larger than largest
            // so far
            if (r < N && arr[r].monthly_rent > arr[largest].monthly_rent)
                largest = r;
            break;
        case(3):
            // If left child is larger than root
            if (l < N && arr[l].room > arr[largest].room)
                largest = l;

            // If right child is larger than largest
            // so far
            if (r < N && arr[r].room > arr[largest].room)
                largest = r;
            break;
    }
    
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest, Type);
    }
}

// A utility function to print array of size n
void printHeap(Vlist<Property>& arr, int N)
{
    cout << "Sorted Array: " << endl;
    for (int i = 0; i < N; ++i) {
        cout << arr[i].toCSVFormat() << endl;
    }
}

// Main function to do heap sort
void heapSort(Vlist<Property>& arr, int N, int Type)
{

    // Build heap (rearrange array)
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i, Type);

    // One by one extract an element
    // from heap
    for (int i = N - 1; i > 0; i--) {

        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0, Type);
    }

    printHeap(arr, N);
}
