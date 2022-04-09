#include <iostream>
#include <vector>

using namespace std;

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

template<typename T, typename TCompare = std::less<T>>
stats insertion_sort(vector<T>& data){
    stats result;
    size_t comparison = 0;
    size_t copy = 0;
    for (size_t i = 1; i < data.size(); ++i) {
        T current = data[i];
        size_t index = i;
        for (size_t j = i; j > 0; --j) { // заменить while-ом
            if (TCompare{}(current, data[j-1])) {
                data[j] = data[j-1];
                index = j - 1;
            }
        }
        data[index] = current;
    }
    return result;
}


template<typename T, typename TCompare = std::less<T>>
stats quick_sort(vector<T>& data, size_t begin, size_t end, stats results) {
    if (end - begin < 2) return results;
    size_t left = begin + 1;
    size_t right = end;
    while(left != right) {
        while ((left < right) && (data[left] < data[begin])) ++left;
        while ((left < right) && (data[right] >= data[begin])) --right;
        swap(data[left], data[right]);
    }
    swap(data[left - 1], data[begin]);
    quick_sort(data, begin, left - 1, results);
    quick_sort(data, left, end, results);
    return results;
}


template<typename T, typename TCompare = std::less<T>>
stats quick_sort(vector<T>& data){
    stats results;
    quick_sort(data, 0, data.size() - 1, results);
    return results;
}

template<typename T, typename TCompare = std::less<T>>
void create_max_heap(vector<T>& data, size_t size, size_t index) {
    if ((index * 2 + 1) >= size) return;
    create_max_heap(data, size, index * 2 + 1);
    create_max_heap(data, size, index * 2 + 2);
    if (data[index * 2 + 1] > data[index]) swap(data[index * 2 + 1], data[index]);
    if ((index * 2 + 2) < size && data[index * 2 + 2] > data[index]) swap(data[index * 2 + 2], data[index]);
}

template<typename T, typename TCompare = std::less<T>>
stats heap_sort(vector<T>& data) {
    stats results;
    for (size_t i = 0; i < data.size() - 1; ++i) {
        create_max_heap(data, data.size() - i, 0);
        swap(data[0], data[data.size() - 1 - i]);
    }
    return results;
}        


int main() {
    vector<int> v;
    v.reserve(10);

    for (int i = 0; i < 10; ++i) {
        v.push_back(rand() % 20);
    }
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;

    quick_sort(v);
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    return 0;
}

