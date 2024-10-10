// SortStrategy.h
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<int>& data) const = 0;
};

#include <vector>
#include <algorithm>
#include <iostream>

// BubbleSort.h
class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) const override {
        for (size_t i = 0; i < data.size() - 1; ++i) {
            for (size_t j = 0; j < data.size() - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

// QuickSort.h
class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) const override {
        quickSort(data, 0, data.size() - 1);
    }

private:
    void quickSort(std::vector<int>& data, int low, int high) const {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }

    int partition(std::vector<int>& data, int low, int high) const {
        int pivot = data[high];
        int i = (low - 1);
        for (int j = low; j < high; ++j) {
            if (data[j] < pivot) {
                ++i;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return (i + 1);
    }
};

// MergeSort.h
class MergeSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) const override {
        mergeSort(data, 0, data.size() - 1);
    }

private:
    void mergeSort(std::vector<int>& data, int left, int right) const {
        if (left < right) {
            int middle = left + (right - left) / 2;
            mergeSort(data, left, middle);
            mergeSort(data, middle + 1, right);
            merge(data, left, middle, right);
        }
    }

    void merge(std::vector<int>& data, int left, int middle, int right) const {
        int n1 = middle - left + 1;
        int n2 = right - middle;

        std::vector<int> leftArr(n1), rightArr(n2);

        for (int i = 0; i < n1; ++i)
            leftArr[i] = data[left + i];
        for (int j = 0; j < n2; ++j)
            rightArr[j] = data[middle + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                data[k] = leftArr[i];
                ++i;
            } else {
                data[k] = rightArr[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            data[k] = leftArr[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            data[k] = rightArr[j];
            ++j;
            ++k;
        }
    }
};


// SortContext.h
class SortContext {
public:
    void setStrategy(std::unique_ptr<SortStrategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void sortData(std::vector<int>& data) const {
        if (strategy_) {
            strategy_->sort(data);
        } else {
            std::cout << "Sort strategy not set!" << std::endl;
        }
    }

private:
    std::unique_ptr<SortStrategy> strategy_;
};

#include "BubbleSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "SortContext.h"
#include <iostream>

int main() {
    std::vector<int> data = {34, 7, 23, 32, 5, 62};

    SortContext context;

    // Use Bubble Sort
    context.setStrategy(std::make_unique<BubbleSort>());
    context.sortData(data);

    std::cout << "Bubble Sorted data: ";
    for (const auto& num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Reset data
    data = {34, 7, 23, 32, 5, 62};

    // Use Quick Sort
    context.setStrategy(std::make_unique<QuickSort>());
    context.sortData(data);

    std::cout << "Quick Sorted data: ";
    for (const auto& num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Reset data
    data = {34, 7, 23, 32, 5, 62};

    // Use Merge Sort
    context.setStrategy(std::make_unique<MergeSort>());
    context.sortData(data);

    std::cout << "Merge Sorted data: ";
    for (const auto& num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
