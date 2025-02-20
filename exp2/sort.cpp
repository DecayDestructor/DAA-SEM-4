#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

// Function to generate and save 100,000 random numbers
void generateRandomNumbers(const string& filename, int count) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Could not open " << filename << " for writing.\n";
        return;
    }

    srand(time(0));  // Seed for randomness
    for (int i = 0; i < count; i++) {
        file << rand() % 1000000 << "\n";  // Random numbers between 0 and 999999
    }
    file.close();
}

// Function to read numbers from file
vector<int> readNumbers(const string& filename) {
    vector<int> numbers;
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open " << filename << " for reading.\n";
        return numbers;
    }

    int num;
    while (file >> num) {
        numbers.push_back(num);
    }
    file.close();
    return numbers;
}

// Quicksort Implementation
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[++i], arr[j]);
        }
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
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
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

// Function to benchmark sorting algorithms and save results
void benchmarkSorting(const vector<int>& numbers, const string& outputFilename) {
    ofstream outFile(outputFilename);
    if (!outFile) {
        cerr << "Error: Could not open " << outputFilename << " for writing.\n";
        return;
    }

    outFile << "BlockSize,QuickSortTime(ms),MergeSortTime(ms)\n";

    for (int size = 100; size <= 100000; size += 100) {
        vector<int> quickArr(numbers.begin(), numbers.begin() + size);
        vector<int> mergeArr(numbers.begin(), numbers.begin() + size);

        // Measure Quicksort Time
        auto start = high_resolution_clock::now();
        quickSort(quickArr, 0, quickArr.size() - 1);
        auto stop = high_resolution_clock::now();
        double quickSortTime = duration<double, milli>(stop - start).count();

        // Measure Merge Sort Time
        start = high_resolution_clock::now();
        mergeSort(mergeArr, 0, mergeArr.size() - 1);
        stop = high_resolution_clock::now();
        double mergeSortTime = duration<double, milli>(stop - start).count();

        // Save results to file
        outFile << size << "," << quickSortTime << "," << mergeSortTime << "\n";
        outFile.flush();  // Ensure data is written immediately

        cout << "Sorted " << size << " elements | QuickSort: " << quickSortTime
             << " ms | MergeSort: " << mergeSortTime << " ms\n";
    }

    outFile.close();
}

int main() {
    string filename = "random_numbers.txt";
    string outputFile = "sorting_results.csv";

    // Step 1: Generate random numbers and save to file
    generateRandomNumbers(filename, 100000);

    // Step 2: Read numbers from file
    vector<int> numbers = readNumbers(filename);
    if (numbers.empty()) {
        cerr << "Error: No numbers were read from the file.\n";
        return 1;
    }

    // Step 3: Run benchmarking
    benchmarkSorting(numbers, outputFile);

    // cout << "Sorting data saved to " << outputFile << ".\n";
    // cout << "Use LibreOffice Calc/MS Excel to plot results.\n";

    return 0;
}