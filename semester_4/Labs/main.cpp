#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
    size_t swap_count = 0;
};

template<typename T, typename TCompare = std::less<T>>
stats insertion_sort(vector<T>& data){
    TCompare less;
    stats result;
    for (size_t i = 1; i < data.size(); ++i) {
        T current = data[i];
        size_t index = i;
        for (size_t j = i; j > 0; --j) {
            result.comparison_count++;
            if (less(current, data[j-1])) {
                data[j] = data[j-1];
                result.copy_count++;
                index = j - 1;
            }
            else break;
        }
        data[index] = current;
        result.copy_count++;
    }
    return result;
}


template<typename T, typename TCompare = std::less<T>>
void quick_sort(vector<T>& data, size_t begin, size_t end, stats& results) {
    TCompare less;
    if (end - begin < 1) return;
    if (end - begin < 2) {
        results.comparison_count++;
        if (less(data[end], data[begin])) {
            swap(data[end], data[begin]);
            results.swap_count++;
        }
        return;
    }
    size_t left = begin + 1;
    size_t right = end;
    while(left != right) {
        //results.comparison_count++;//???
        while ((left < right) && (less(data[left], data[begin]))) {
            results.comparison_count++;
            ++left;
        }

        //results.comparison_count++;//???
        while ((left < right) && (!less(data[right], data[begin]))) {
            results.comparison_count++;
            --right;
        }

        if (left != right) {
            swap(data[left], data[right]);
            results.swap_count++;
        }
    }

    results.comparison_count++;
    if (left == end && less(data[left], data[begin])) {
        swap(data[left], data[begin]);
        results.swap_count++;
    }
    else {
        swap(data[left - 1], data[begin]);
        results.swap_count++;
    }
    quick_sort<T, TCompare>(data, begin, left - 1, results);
    quick_sort<T, TCompare>(data, left , end, results);
}


template<typename T, typename TCompare = std::less<T>>
stats quick_sort(vector<T>& data){
    stats results;
    quick_sort<T, TCompare>(data, 0, data.size() - 1, results);
    return results;
}

template<typename T, typename TCompare = std::less<T>>
void create_max_heap(vector<T>& data, size_t size, size_t index, stats& result) {
    TCompare less;
    if ((index * 2 + 1) >= size) return;
    create_max_heap<T, TCompare>(data, size, index * 2 + 1, result);
    create_max_heap<T, TCompare>(data, size, index * 2 + 2, result);
    size_t largest = index;
    result.comparison_count++;
    if (less(data[index], data[index * 2 + 1])) {
        largest = index * 2 + 1;
        //swap(data[index * 2 + 1], data[index]);
        //result.swap_count++;
    }
    if ((index * 2 + 2) < size) {
        result.comparison_count++;
        if (less(data[largest], data[index * 2 + 2])) {
            largest = index * 2 + 2;
            //swap(data[index * 2 + 2], data[index]);
            //result.swap_count++;
        }
    }
    if (largest != index) {
        swap(data[index], data[largest]);
        result.swap_count++;
    }
}

template<typename T, typename TCompare = std::less<T>>
stats heap_sort(vector<T>& data) {
    stats results;
    for (size_t i = 0; i < data.size() - 1; ++i) {
        create_max_heap<T, TCompare>(data, data.size() - i, 0, results);
        swap(data[0], data[data.size() - 1 - i]);
        results.swap_count++;
    }
    return results;
}        

void print_result_sorting(stats& result) {
    cout << "Copy: " << result.copy_count << endl;
    cout << "Compare: " << result.comparison_count << endl;
    cout << "Swap: " << result.swap_count << endl;
}

void test_average (size_t size_vector) {
    srand(time(nullptr));

    stats average_result;

    for (int k = 0; k < 100; ++k) {
        vector<int> v;
        v.reserve(size_vector);
        for (size_t i = 0; i < size_vector; ++i) {
            v.push_back(rand() % size_vector);
        }
        stats res;
        res = insertion_sort(v);
        average_result.swap_count += res.swap_count;
        average_result.comparison_count += res.comparison_count;
        average_result.copy_count += res.copy_count;
    }

    average_result.comparison_count /= 100;
    average_result.swap_count /= 100;
    average_result.copy_count /= 100;

    print_result_sorting(average_result);
}

void test_sorting_array(size_t size_vector, bool reverse=false) {
    vector<int> v;
    v.reserve(size_vector);
    for (int i = 0; i < size_vector; ++i) {
        v.push_back(i);
    }
    if (reverse) std::reverse(v.begin(), v.end());
    stats result = quick_sort(v);
    print_result_sorting(result);
}

int main() {

    srand(time(nullptr));
    //test_sorting_array(1000, false);

    vector<int> vec;
    vec.reserve(10);
    for (int i = 0; i < 10; ++i) {
        vec.push_back(rand() % 20);
    }
    for(auto i: vec) {
        cout << i << " ";
    }
    cout << endl;
    quick_sort(vec);
    for(auto i: vec) {
        cout << i << " ";
    }
    return 0;
}

