#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>

void init_vector(std::vector<int> &vec, int seed, int lo, int hi) {
    srand(seed);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = rand()%(hi-lo+1)+lo;
    }
}

void print_vector(const std::vector<int> &v, int print_cols, int col_width) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << std::setw(col_width) << std::setfill(' ') << std::left << v[i] << "|";
        if ((i + 1)%print_cols == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}

void sort_vector(std::vector<int> &v) {
    std::sort(v.begin(), v.end());
}

int search_vector(const std::vector<int> &v1, const std::vector<int> &v2, bool (*p)(const std::vector<int> &, int)) {
    int total = 0;
    for (auto & item : v2) {
        if (p(v1, item)) {
            total++;
        }
    }
    return total;
}

void print_stat(int found, int total){
    double percentage = ((double)found/total)*100;
    std::cout << "Overall, " << found << " elements found out of " << total << ", which is " << percentage << "%." << std::endl;
}

bool linear_search(const std::vector<int> &v, int x) {
    return std::find(v.begin(),v.end(),x) != v.end();
}

bool binary_search(const std::vector<int> &v, int x) {
    return std::binary_search(v.begin(),v.end(),x);
}

int main() {
    int a_size = 100, b_size = 50;  
    int a_seed = 123, b_seed = 456;
    int rand_low = 0, rand_high = 100;

    std::vector<int> A(a_size);
    std::vector<int> B(b_size);

    init_vector(A, a_seed, rand_low, rand_high);
    print_vector(A, 10, 4);
  
    sort_vector(A);
    print_vector(A, 10, 4);

    init_vector(B, b_seed, rand_low, rand_high);
    print_vector(B, 10, 4);

    int total_linear = search_vector(A, B, linear_search);
    print_stat(total_linear, B.size());
    int total_binary = search_vector(A, B, binary_search);
    print_stat(total_binary, B.size());
  
    return 0;
}