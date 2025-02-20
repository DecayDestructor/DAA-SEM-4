#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

// Function to generate a best-case input for QuickSort (random shuffled array)
vector<int> generateBestCaseQuickSort(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = i;  // Sorted order
    random_shuffle(arr.begin(), arr.end());     // Shuffle for balanced pivot
    return arr;
}

// Function to generate a worst-case input for QuickSort (sorted array)
vector<int> generateWorstCaseQuickSort(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = i;  // Already sorted, worst for QuickSort
    return arr;
}

// Function to generate a best-case input for Merge Sort (sorted array)
vector<int> generateBestCaseMergeSort(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = i;  // Already sorted
    return arr;
}

// Function to generate a worst-case input for Merge Sort (reverse sorted array)
vector<int> generateWorstCaseMergeSort(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = size - i;  // Reverse sorted, worst for Merge Sort
    return arr;
}

// Quicksort Implementation
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) swap(arr[++i], arr[j]);
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort Implementation
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Benchmark sorting algorithms and save results
void benchmarkSorting(const string& outputFilename) {
    ofstream outFile(outputFilename);
    if (!outFile) {
        cerr << "Error: Could not open " << outputFilename << " for writing.\n";
        return;
    }

    outFile << "BlockSize,QuickSortBest(ms),QuickSortWorst(ms),MergeSortBest(ms),MergeSortWorst(ms)\n";

    for (int size = 100; size <= 100000; size += 100) {
        // Generate best & worst case inputs
        vector<int> quickBest = generateBestCaseQuickSort(size);
        vector<int> quickWorst = generateWorstCaseQuickSort(size);
        vector<int> mergeBest = generateBestCaseMergeSort(size);
        vector<int> mergeWorst = generateWorstCaseMergeSort(size);

        // Measure QuickSort Best Case Time
        auto start = high_resolution_clock::now();
        quickSort(quickBest, 0, quickBest.size() - 1);
        auto stop = high_resolution_clock::now();
        double quickBestTime = duration<double, milli>(stop - start).count();

        // Measure QuickSort Worst Case Time
        start = high_resolution_clock::now();
        quickSort(quickWorst, 0, quickWorst.size() - 1);
        stop = high_resolution_clock::now();
        double quickWorstTime = duration<double, milli>(stop - start).count();

        // Measure Merge Sort Best Case Time
        start = high_resolution_clock::now();
        mergeSort(mergeBest, 0, mergeBest.size() - 1);
        stop = high_resolution_clock::now();
        double mergeBestTime = duration<double, milli>(stop - start).count();

        // Measure Merge Sort Worst Case Time
        start = high_resolution_clock::now();
        mergeSort(mergeWorst, 0, mergeWorst.size() - 1);
        stop = high_resolution_clock::now();
        double mergeWorstTime = duration<double, milli>(stop - start).count();

        // Save results to file
        outFile << size << "," << quickBestTime << "," << quickWorstTime << "," << mergeBestTime << "," << mergeWorstTime << "\n";
        outFile.flush();  // Ensure data is written immediately

        cout << "Sorted " << size << " elements | QuickSort Best: " << quickBestTime
             << " ms | QuickSort Worst: " << quickWorstTime
             << " ms | MergeSort Best: " << mergeBestTime
             << " ms | MergeSort Worst: " << mergeWorstTime << " ms\n";
    }

    outFile.close();
}

int main() {
    string outputFile = "sorting_best_worst.csv";

    // Step 1: Run benchmarking
    benchmarkSorting(outputFile);

    cout << "Sorting data saved to " << outputFile << ".\n";
    cout << "Use LibreOffice Calc/MS Excel to plot results.\n";

    return 0;
}
