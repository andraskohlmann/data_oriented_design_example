#include <algorithm>
#include <iterator>
#include <vector>
#include <chrono>
#include <iostream>
#include <thread>

using std::back_inserter;
using std::fill_n;
using std::vector;
using namespace std::chrono;

struct Organism {
    int legs = 2;
    int arms = 2;
};

struct Person : Organism {
    int age = 34;
    float height = 180.1;
    float weight = 78.3;
    std::string name = "Gipsz Jakab";

    void get_older() { age++; }
};

static int ArrayOfStructs(int N) {
    vector<Person> v;
    fill_n(back_inserter(v), N, Person());
    
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        for (auto &i : v) {
            i.get_older();
        }
    }
    return duration_cast<microseconds>(high_resolution_clock::now() - start).count() / 10;
}

struct Components {
    vector<int> legs;
    vector<int> arms;
    vector<int> ages;
    vector<float> heights;
    vector<float> weights;
    vector<std::string> names;

    Components(int N) {
        legs.resize(N, 2);
        arms.resize(N, 2);
        ages.resize(N, 34);
        heights.resize(N, 180.1);
        weights.resize(N, 78.3);
        names.resize(N, "Gipsz Jakab");
    }

    void get_older() {
        for (auto &i : ages) {
            i++;
        }
    }
};

static int StructOfArrays(int N) {
    Components struct_of_arrays(N);
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        struct_of_arrays.get_older();
    }
    return duration_cast<microseconds>(high_resolution_clock::now() - start).count() / 10;
}

static void print_runtimes(int (*f)(int)) {
    int N = 1024;
    for (int i = 0; i < 7; ++i) {
        N = N << 1;
        int sum_time = 0;
        for (int i = 0; i < 10; i++) sum_time += f(N);
        
        std::cout << sum_time / 10 << std::endl;
    }
}

int main() {
    std::cout << "StructOfArrays" << std::endl;
    print_runtimes(StructOfArrays);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "ArrayOfStructs" << std::endl;
    print_runtimes(ArrayOfStructs);
    return 0;
}
