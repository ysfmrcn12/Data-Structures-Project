#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
struct SortMetrics {
 long long opCount = 0;
 long long changeCount = 0;
};
using SortFunction = std::function<void(std::vector<int>&, SortMetrics&, bool)>;
void printArray(const std::vector<int>& arr) {
 std::cout << "[";
 for (std::size_t i = 0; i < arr.size(); ++i) {
 std::cout << arr[i];
 if (i + 1 < arr.size()) {
 std::cout << ", ";
 }
 }
 std::cout << "]";
}
void traceBeforeChange(
 const std::string& algorithm,
 const std::string& action,
 const std::vector<int>& arr,
 SortMetrics& metrics,
 bool trace
) {
 metrics.opCount += 1;
 if (trace) {
 std::cout << algorithm << " - before " << action << ": ";
 printArray(arr);
 std::cout << "\n";
 }
}
void swapWithMetrics(
 std::vector<int>& arr,
 int i,
 int j,
 SortMetrics& metrics
) {
 metrics.opCount += 1;
 if (i == j) {
 return;
 }
 metrics.changeCount += 1;
 metrics.opCount += 7;
 int tmp = arr[i];
 arr[i] = arr[j];
 arr[j] = tmp;
}
int partitionQuick(
 std::vector<int>& arr,
 int low,
 int high,
 SortMetrics& metrics,
 bool trace
) {
 metrics.opCount += 2;
 int pivot = arr[high];
 int i = low - 1;
 metrics.opCount += 1;
 for (int j = low; j < high; ++j) {
 metrics.opCount += 2;
 metrics.opCount += 2;
 if (arr[j] <= pivot) {
 i += 1;
 metrics.opCount += 2;
 traceBeforeChange(
 "Quicksort",
 "swap arr[" + std::to_string(i) + "] and arr[" + std::to_string(j) + "]",
 arr,
 metrics,
 trace
 );
 swapWithMetrics(arr, i, j, metrics);
 }
 }
 traceBeforeChange(
 "Quicksort",
 "pivot swap arr[" + std::to_string(i + 1) + "] and arr[" + std::to_string(high) + "]",
 arr,
 metrics,
 trace
 );
 swapWithMetrics(arr, i + 1, high, metrics);
 return i + 1;
}
void quickSortRecursive(
 std::vector<int>& arr,
 int low,
 int high,
 SortMetrics& metrics,
 bool trace
) {
 metrics.opCount += 1;
 if (low >= high) {
 return;
 }
 metrics.opCount += 1;
 int pi = partitionQuick(arr, low, high, metrics, trace);
 quickSortRecursive(arr, low, pi - 1, metrics, trace);
 quickSortRecursive(arr, pi + 1, high, metrics, trace);
}
void quickSort(std::vector<int>& arr, SortMetrics& metrics, bool trace) {
 metrics.opCount += 1;
 if (arr.empty()) {
 return;
 }
 quickSortRecursive(arr, 0, static_cast<int>(arr.size()) - 1, metrics, trace);
}
void insertionSort(std::vector<int>& arr, SortMetrics& metrics, bool trace) {
 for (int i = 1; i < static_cast<int>(arr.size()); ++i) {
 metrics.opCount += 2;
 int key = arr[i];
 int j = i - 1;
 metrics.opCount += 3;
 while (j >= 0) {
 metrics.opCount += 1;
 metrics.opCount += 2;
 if (arr[j] <= key) {
 break;
 }
 traceBeforeChange(
 "Insertion sort",
 "shift arr[" + std::to_string(j) + "] -> arr[" + std::to_string(j + 1) + "]",
 arr,
 metrics,
 trace
 );
 arr[j + 1] = arr[j];
 metrics.changeCount += 1;
 metrics.opCount += 3;
 j -= 1;
 metrics.opCount += 2;
 }
 metrics.opCount += 1;
 if (j + 1 != i) {
 traceBeforeChange(
 "Insertion sort",
 "place key at arr[" + std::to_string(j + 1) + "]",
 arr,
 metrics,
 trace
 );
 }
 arr[j + 1] = key;
 metrics.changeCount += 1;
 metrics.opCount += 2;
 }
}
void heapify(
 std::vector<int>& arr,
 int n,
 int i,
 SortMetrics& metrics,
 bool trace
) {
 int largest = i;
 int left = 2 * i + 1;
 int right = 2 * i + 2;
 metrics.opCount += 5;
 metrics.opCount += 2;
 if (left < n) {
 metrics.opCount += 2;
 if (arr[left] > arr[largest]) {
 largest = left;
 metrics.opCount += 1;
 }
 }
 metrics.opCount += 2;
 if (right < n) {
 metrics.opCount += 2;
 if (arr[right] > arr[largest]) {
 largest = right;
 metrics.opCount += 1;
 }
 }
 metrics.opCount += 1;
 if (largest != i) {
 traceBeforeChange(
 "Heapsort",
 "heapify swap arr[" + std::to_string(i) + "] and arr[" + std::to_string(largest) + "]",
 arr,
 metrics,
 trace
 );
 swapWithMetrics(arr, i, largest, metrics);
 heapify(arr, n, largest, metrics, trace);
 }
}
void heapSort(std::vector<int>& arr, SortMetrics& metrics, bool trace) {
 int n = static_cast<int>(arr.size());
 metrics.opCount += 1;
 for (int i = (n / 2) - 1; i >= 0; --i) {
 metrics.opCount += 2;
 heapify(arr, n, i, metrics, trace);
 }
 for (int i = n - 1; i > 0; --i) {
 metrics.opCount += 2;
 traceBeforeChange(
 "Heapsort",
 "extract max swap arr[0] and arr[" + std::to_string(i) + "]",
 arr,
 metrics,
 trace
 );
 swapWithMetrics(arr, 0, i, metrics);
 heapify(arr, i, 0, metrics, trace);
 }
}
void selectionSort(std::vector<int>& arr, SortMetrics& metrics, bool trace) {
 int n = static_cast<int>(arr.size());
 metrics.opCount += 1;
 for (int i = 0; i < n - 1; ++i) {
 metrics.opCount += 2;
 int minIdx = i;
 metrics.opCount += 1;
 for (int j = i + 1; j < n; ++j) {
 metrics.opCount += 2;
 metrics.opCount += 2;
 if (arr[j] < arr[minIdx]) {
 minIdx = j;
 metrics.opCount += 1;
 }
 }
 metrics.opCount += 1;
 if (minIdx != i) {
 traceBeforeChange(
 "Selection sort",
 "swap min arr[" + std::to_string(minIdx) + "] with arr[" + std::to_string(i) + "]",
 arr,
 metrics,
 trace
 );
 swapWithMetrics(arr, i, minIdx, metrics);
 }
 }
}
void runTask1AndTask2Demo(
 const std::string& algorithmName,
 const SortFunction& sorter,
 const std::vector<int>& input
) {
 std::vector<int> arr = input;
 SortMetrics metrics;
 std::cout << "\n--- " << algorithmName << " ---\n";
 std::cout << "Original input: ";
 printArray(arr);
 std::cout << "\n";
 sorter(arr, metrics, true);
 std::cout << "Sorted output: ";
 printArray(arr);
 std::cout << "\n";
 std::cout << "opCount: " << metrics.opCount
 << ", changes: " << metrics.changeCount << "\n";
}
std::vector<int> generateRandomArray(
 int size,
 int minValue,
 int maxValue,
 std::mt19937& rng
) {
 std::uniform_int_distribution<int> dist(minValue, maxValue);
 std::vector<int> arr;
 arr.reserve(static_cast<std::size_t>(size));
 for (int i = 0; i < size; ++i) {
 arr.push_back(dist(rng));
 }
 return arr;
}
struct BatchResult {
 std::string algorithm;
 int n = 0;
 int repeats = 0;
 double avgCost = 0.0;
};
void printTask3Table(const std::vector<BatchResult>& results) {
 std::cout << "\nTask 3 - Experimental Cost Table\n";
 std::cout << std::left
 << std::setw(16) << "Algorithm"
 << std::setw(10) << "n"
 << std::setw(10) << "Repeats"
 << std::setw(16) << "T=Avg opCount"
 << std::setw(12) << "T/n"
 << std::setw(16) << "T/n^2"
 << std::setw(12) << "T/log2(n)"
 << std::setw(16) << "T/(nlog2n)"
 << "\n";
 std::cout << std::string(92, '-') << "\n";
 std::cout << std::fixed << std::setprecision(4);
 for (const BatchResult& row : results) {
 const double n = static_cast<double>(row.n);
 const double logN = std::log2(n);
 const double ratioN = row.avgCost / n;
 const double ratioN2 = row.avgCost / (n * n);
 const double ratioLogN = row.avgCost / logN;
 const double ratioNLogN = row.avgCost / (n * logN);
 std::cout << std::left
 << std::setw(16) << row.algorithm
 << std::setw(10) << row.n
 << std::setw(10) << row.repeats
 << std::setw(16) << row.avgCost
 << std::setw(12) << ratioN
 << std::setw(16) << ratioN2
 << std::setw(12) << ratioLogN
 << std::setw(16) << ratioNLogN
 << "\n";
 }
}
int main() {
 const std::vector<int> manualInput = {29, 10, 14, 37, 13, 5, 42, 3};
 std::cout << "====================================\n";
 std::cout << "Task 1 + Task 2: Sorting + Step Trace\n";
 std::cout << "====================================\n";
 runTask1AndTask2Demo("Quicksort", quickSort, manualInput);
 runTask1AndTask2Demo("Insertion sort", insertionSort, manualInput);
 runTask1AndTask2Demo("Heapsort", heapSort, manualInput);
 runTask1AndTask2Demo("Selection sort", selectionSort, manualInput);
 std::cout << "\n====================================\n";
 std::cout << "Task 3: Randomized Input + Cost Analysis\n";
 std::cout << "====================================\n";
 std::random_device rd;
 std::mt19937 rng(rd());
 std::vector<int> randomPreview = generateRandomArray(20, 1, 200, rng);
 std::cout << "Randomized input sample (n=20): ";
 printArray(randomPreview);
 std::cout << "\n";
 const std::vector<int> sizes = {100, 200, 300, 1000};
 const int repeats = 20;
 struct NamedSorter {
 std::string name;
 SortFunction sorter;
 };
 const std::vector<NamedSorter> sorters = {
 {"Quicksort", quickSort},
 {"Insertion", insertionSort},
 {"Heapsort", heapSort},
 {"Selection", selectionSort},
 };
 std::vector<BatchResult> results;
 for (const NamedSorter& item : sorters) {
 for (int n : sizes) {
 long long totalOps = 0;
 for (int run = 0; run < repeats; ++run) {
 std::vector<int> baseInput = generateRandomArray(n, 1, n * 10, rng);
 std::vector<int> arr = baseInput;
 SortMetrics metrics;
 item.sorter(arr, metrics, false);
 totalOps += metrics.opCount;
 }
 BatchResult row;
 row.algorithm = item.name;
 row.n = n;
 row.repeats = repeats;
 row.avgCost = static_cast<double>(totalOps) / static_cast<double>(repeats);
 results.push_back(row);
 }
 }
 printTask3Table(results);
 std::cout << "\nComplexity hint from ratios:\n";
 std::cout << "- Insertion/Selection should keep T/n^2 closer to constant.\n";
 std::cout << "- Quicksort/Heapsort should keep T/(nlog2n) closer to constant.\n";
 return 0;
}
