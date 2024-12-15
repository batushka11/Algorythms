#include <iostream>
#include "heap.h"

int getMaxElement(int* array, int sz) {
    int max = array[0];

    for (int i = 1; i < sz; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    return max;
}

void counting_sort(int* array, const int sz, int max) {
    int* cnt = new int[max + 1];
    int* result = new int[sz];

    std::memset(cnt, 0, (max + 1) * sizeof(int));

    for (int i = 0; i < sz; i++) {
        cnt[array[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        cnt[i] += cnt[i - 1];
    }

    for (int i = sz - 1; i >= 0; i--) {
        result[cnt[array[i]] - 1] = array[i];
        cnt[array[i]]--;
    }

    for (int i = 0; i < sz; i++) {
        array[i] = result[i];
    }

    delete[] cnt;
    delete[] result;
}

void bucket_sort(int* array, const int sz, const int bucket_count, int max) {
    const int bucket_size = std::ceil((double)(max + 1) / bucket_count);

    int* bucket_sizes = new int[bucket_count];
    int** buckets = new int*[bucket_count];

    for (int i = 0; i < bucket_count; i++) {
        bucket_sizes[i] = 0;
        buckets[i] = new int[sz];
    }

    for (int i = 0; i < sz; i++) {
        int bucket_idx = array[i] / bucket_size;
        buckets[bucket_idx][bucket_sizes[bucket_idx]++] = array[i];
    }

    int idx = 0;
    for (int i = 0; i < bucket_count; i++) {
        // for (int j = 0; j < bucket_sizes[i] - 1; j++) {
        //     for (int k = 0; k < bucket_sizes[i] - j - 1; k++) {
        //         if (buckets[i][k] > buckets[i][k + 1]) {
        //             int temp = buckets[i][k];
        //             buckets[i][k] = buckets[i][k + 1];
        //             buckets[i][k + 1] = temp;
        //         }
        //     }
        // }
        std::sort(buckets[i], buckets[i] + bucket_sizes[i]);
        for (int j = 0; j < bucket_sizes[i]; j++) {
            array[idx++] = buckets[i][j];
        }
    }

    for (int i = 0; i < bucket_count; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucket_sizes;
}

template <typename T>
void bucket_sort(T* array, const int sz, const int bucket_count,
                 double (*key_function)(const T&),
                 std::function<bool(const T&, const T&)> compare_function) {
    double min_key = key_function(array[0]);
    double max_key = key_function(array[0]);

    for (int i = 1; i < sz; i++) {
        double key = key_function(array[i]);
        if (key < min_key) min_key = key;
        if (key > max_key) max_key = key;
    }

    const double range = max_key - min_key;
    int* bucket_sizes = new int[bucket_count];
    T** buckets = new T*[bucket_count];

    for (int i = 0; i < bucket_count; i++) {
        bucket_sizes[i] = 0;
        buckets[i] = new T[sz];
    }

    for (int i = 0; i < sz; i++) {
        int bucket_idx = (int)((key_function(array[i]) - min_key) / range * (bucket_count - 1));
        buckets[bucket_idx][bucket_sizes[bucket_idx]++] = array[i];
    }

    int idx = 0;
    for (int i = 0; i < bucket_count; i++) {
        // for (int j = 0; j < bucket_sizes[i] - 1; j++) {
        //     for (int k = 0; k < bucket_sizes[i] - j - 1; k++) {
        //         if (compare_function(buckets[i][k + 1], buckets[i][k])) {
        //             T temp = buckets[i][k];
        //             buckets[i][k] = buckets[i][k + 1];
        //             buckets[i][k + 1] = temp;
        //         }
        //     }
        // }
        std::sort(buckets[i], buckets[i] + bucket_sizes[i], compare_function);
        for (int j = 0; j < bucket_sizes[i]; j++) {
            array[idx++] = buckets[i][j];
        }
    }

    for (int i = 0; i < bucket_count; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucket_sizes;
}

void test() {
    srand(0);
    const int MAX_ORDER = 7;

    for (int o = 1; o < MAX_ORDER; o++) {
        const int n = pow(10, o);

        int* array1 = new int[n];
        int* array2 = new int[n];
        int* array3 = new int[n];

        for (int i = 0; i < n; i++) {
            array1[i] = rand() % n;
        }

        for (int i = 0; i < n; i++) {
            array2[i] = array1[i];
            array3[i] = array1[i];
        }
        const int max = getMaxElement(array1, n);
        clock_t t1 = clock();
        counting_sort(array1, n, max);
        clock_t t2 = clock();

        std::cout <<"Elements in array: " << n << std::endl;
        std::cout << std::fixed ;
        std::cout << "Counting sort time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << " s" << std::endl;

        t1 = clock();
        binary_heap<int>::sort(array2, n, false, [](const int &a, const int &b) {
            return a > b;
        });
        t2 = clock();
        std::cout << "Heap sort time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << " s" << std::endl;

        t1 = clock();
        bucket_sort(array3, n, n / 10, max);
        t2 = clock();
        std::cout << "Bucket sort time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << " s" << std::endl;
        std::cout << std::endl ;
        delete[] array1;
        delete[] array2;
        delete[] array3;
    }
}

struct some_object {
    double key;
    char data;
};

double some_object_key(const some_object& obj) {
    return obj.key;
}

bool some_object_cmp(const some_object& a, const some_object& b) {
    return a.key < b.key;
}

void experiment_sorting() {
    const int MAX_ORDER = 7;
    const double m_double = (double) pow(2, 30);

    for (int o = 1; o < MAX_ORDER; o++) {
        const int n = (int) pow(10, o);

        some_object* array1 = new some_object[n];
        some_object* array2 = new some_object[n];

        for (int i = 0; i < n; i++) {
            array1[i].key = ((rand() << 15) + rand()) / m_double;
            array1[i].data = 'a' + rand() % 26;
        }
        std::copy(array1, array1 + n, array2);

        std::cout << n << std::endl;
        clock_t t1 = clock();
        binary_heap<some_object>::sort(array2, n, false, some_object_cmp);
        clock_t t2 = clock();
        std::cout << "Heap sort time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << " s" << std::endl;

        t1 = clock();
        bucket_sort(array2, n, n / 10, some_object_key, std::function(
            [](const some_object &a, const some_object &b) {
            return a.key > b.key;
        }));

        t2 = clock();
        std::cout << "Bucket sort time: " << (double)(t2 - t1) / CLOCKS_PER_SEC << " s" << std::endl;
        std::cout << std::endl;
        delete[] array1;
        delete[] array2;
    }
}

int main()
{
    int array[] = {100,5,3,2,44,54,22,1,16,9,56,50};
    const int sz = sizeof(array) / sizeof(int);
    counting_sort(array, sz, 100);
    for (int i : array) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    int array1[] = {100,5,3,2,44,54,22,1,16,9,56,50};
    const int sz1 = sizeof(array1) / sizeof(int);
    bucket_sort(array1,sz1,8, 100);
    for (int i : array1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    int array2[] = {100,5,3,2,44,54,22,1,16,9,56,50};
    const int sz2 = sizeof(array2) / sizeof(int);
    binary_heap<int>::sort(array2, sz2, false, [](const int &a, const int &b) {
        return a > b;
    });
    for (int i : array2) {
        std::cout << i << " ";
    }
    std::cout<< "Test 1" << std::endl;
    test();
    std::cout << "Test 2" << std::endl;
    experiment_sorting();
}
