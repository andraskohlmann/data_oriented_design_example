#include <algorithm>
#include <iterator>
#include <vector>
#include <chrono>
#include <iostream>

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

static void ArrayOfStructs(int N) {
    vector<Person> v;
    fill_n(back_inserter(v), N, Person());

    for (int i = 0; i < 1000; ++i) {
        for (auto &i : v) {
            i.get_older();
        }
    }
}

struct Components {
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

    vector<int> legs;
    vector<int> arms;
    vector<int> ages;
    vector<float> heights;
    vector<float> weights;
    vector<std::string> names;
};

static void StructOfArrays(int N) {
    Components struct_of_arrays(N);
    for (int i = 0; i < 1000; ++i) {
        struct_of_arrays.get_older();
    }
}

static int measure_runtime(void (*f)(int), int N) {
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 10; i++) f(N);
    return duration_cast<microseconds>(high_resolution_clock::now() - start).count() / 10;
}

int main() {
    int N = 1024;
    for (int i = 0; i < 8; ++i) {
        N = N << 1;
        std::cout << measure_runtime(ArrayOfStructs, N) << " vs ";
        std::cout << measure_runtime(StructOfArrays, N) << std::endl;
    }
}
