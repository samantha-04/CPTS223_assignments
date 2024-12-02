#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class SortingComparison {
public:
    // insrtion sort
    void insertionSort(std::vector<int>& arr) 
    {
        for (int p = 1; p < arr.size(); p++)
        {
            int tmp = std::move(arr[p]);
            
            int j;
            for(j = p; j > 0 && tmp < arr[j - 1]; j--)
            {
                arr[j] = std::move(arr[j - 1]);
            }

            arr[j] = std::move(tmp);
        }
    }

    int & median3(std::vector<int>& arr, int left, int right)
    {
        int center = (left + right) /2;

        if (arr[center] < arr[left])
        {
            std::swap(arr[left], arr[center]);
        }
         if (arr[right] < arr[left])
        {
            std::swap(arr[left], arr[right]);
        }
         if (arr[right] < arr[center])
        {
            std::swap(arr[center], arr[right]);
        }


        //place picot positions right - 1
        std::swap(arr[center], arr[right - 1]);
        return arr[right - 1];
        
    }

    // quick sort
    void quickSort(std::vector<int>& arr, int left, int right) 
    {
        while (left + 20 <= right) 
        { 
            const int& pivot = median3(arr, left, right);
            int i = left, j = right - 1;

            for (;;) {
                while (arr[++i] < pivot) {}
                while (pivot < arr[--j]) {}
                if (i < j) 
                {
                    std::swap(arr[i], arr[j]);
                } 
                else 
                {
                    break;
                }
            }

            std::swap(arr[i], arr[right - 1]); //restore pivot

            if (i - left < right - i) 
            {
                quickSort(arr, left, i - 1);
                left = i + 1; 
            } 
            else 
            {
                quickSort(arr, i + 1, right);
                right = i - 1; 
            }
    }
    insertionSort(arr);
    }

    void merge(std::vector<int>& arr, int left, int mid, int right) 
    {

        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1), R(n2);
        for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
        for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) 
        {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }

        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    // merge sort
    void mergeSort(std::vector<int>& arr, int left, int right) 
    {
        if (left < right) 
        {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    // generate random integers
    std::vector<int> generateRandomArray(int size) {
        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100000);
        for (int& x : arr) {
            x = dist(gen);
        }
        return arr;
    }

    // test sorted
    bool isSorted(const std::vector<int>& arr) {
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }

    // comparison run time for three sorting algorithms
    void compareSortingAlgorithms() 
    {
        std::vector<int> sizes = {1000, 10000, 100000}; // data scales
        for (int size : sizes) {
            std::vector<int> arr = generateRandomArray(size);
            
            std::cout << "Data size: " << size << "\n";

            // test insertion sort
            std::vector<int> arr_copy = arr;
            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(arr_copy);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            std::cout << "Insertion Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n";

            // test quick sort
            arr_copy = arr;
            start = std::chrono::high_resolution_clock::now();
            quickSort(arr_copy, 0, arr_copy.size() - 1);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            std::cout << "Quick Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n";

            // test merge sort
            arr_copy = arr;
            start = std::chrono::high_resolution_clock::now();
            mergeSort(arr_copy, 0, arr_copy.size() - 1);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            std::cout << "Merge Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n\n";
        }
    }

private:
    // Some internal helper functions
};

int main() {
    SortingComparison sorter;
    sorter.compareSortingAlgorithms();
    return 0;
}

