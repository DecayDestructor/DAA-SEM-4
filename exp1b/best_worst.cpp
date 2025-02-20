#include <bits/stdc++.h>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
using namespace std::chrono;

// Function to generate random numbers and save them
void generateNumbers(const string &filename, int count) {
    ofstream file(filename);
    srand(time(0));
    for (int i = 0; i < count; i++) {
        file << rand() % 1000000 << " ";
    }
    file.close();
}

// Function to read numbers from file
vector<int> readNumbers(const string &filename, int count) {
    ifstream file(filename);
    vector<int> numbers(count);
    for (int i = 0; i < count; i++) {
        file >> numbers[i];
    }
    file.close();
    return numbers;
}

// Insertion Sort
void insertionSort(vector<int> &arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(vector<int> &arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Function to measure execution time
long long measureSortTime(void (*sortFunc)(vector<int> &, int), vector<int> &arr, int n) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, n);
    auto stop = high_resolution_clock::now();
    return duration_cast<milliseconds>(stop - start).count();
}

int main() {
    string filename = "numbers.txt";
    int totalNumbers = 100000;
    generateNumbers(filename, totalNumbers);

    ofstream resultFile("sorting_results_best_worst.csv");
    resultFile << "Block Size,Best Case Insertion (ms),Worst Case Insertion (ms),Best Case Selection (ms),Worst Case Selection (ms)\n";

    for (int blockSize = 100; blockSize <= totalNumbers; blockSize += 100) {
        vector<int> numbers = readNumbers(filename, blockSize);

        // Best case: already sorted
        vector<int> bestCase = numbers;
        sort(bestCase.begin(), bestCase.end());

        // Worst case: reverse sorted
        vector<int> worstCase = bestCase;
        reverse(worstCase.begin(), worstCase.end());

        // Measure Insertion Sort
        vector<int> copy1 = bestCase, copy2 = worstCase;
        long long bestInsertion = measureSortTime(insertionSort, copy1, blockSize);
        long long worstInsertion = measureSortTime(insertionSort, copy2, blockSize);

        // Measure Selection Sort
        vector<int> copy3 = bestCase, copy4 = worstCase;
        long long bestSelection = measureSortTime(selectionSort, copy3, blockSize);
        long long worstSelection = measureSortTime(selectionSort, copy4, blockSize);

        // Save results
        resultFile << blockSize << "," << bestInsertion << "," << worstInsertion << ","
                   << bestSelection << "," << worstSelection << "\n";

        cout << "Block Size: " << blockSize << " | Insertion Best: " << bestInsertion
             << " ms, Worst: " << worstInsertion << " ms | Selection Best: "
             << bestSelection << " ms, Worst: " << worstSelection << " ms" << endl;
    }

    resultFile.close();
    cout << "Results saved in sorting_results_best_worst.csv" << endl;
    return 0;
}
