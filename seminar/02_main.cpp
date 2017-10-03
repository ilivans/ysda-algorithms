#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <algorithm>

using std::vector;

size_t LowerBound(const vector<int>& data, int value) {
    size_t left = 0, right = data.size();
    while (left < right) {
        size_t middle = left + (right - left) / 2;
        if (data[middle] < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

size_t LowerBoundSlow(const vector<int>& data, int value) {
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] >= value) {
            return i;
        }
    }
    return data.size();
}

void Check(size_t expected, size_t actual) {
    if (expected != actual) {
        std::cerr << "FAIL: ";
        std::cerr << "expected " << expected;
        std::cerr << ", got " << actual << "\n";
        std::exit(1);
    } else {
        std::cerr << "OK: got " << expected << "\n";
    }
}

void TestLowerBound() {
    {
        vector<int> data;
        Check(data.size(), LowerBound(data, 0));
    }
    {
        vector<int> data{1};
        Check(data.size(), LowerBound(data, 2));
        Check(0u, LowerBound(data, 0));
        Check(0u, LowerBound(data, -1));
    }
    {
        vector<int> data{1, 2, 2, 3, 5, 5, 6};
        Check(0u, LowerBound(data, 0));
        Check(data.size(), LowerBound(data, 7));
        Check(4u, LowerBound(data, 4));
        Check(4u, LowerBound(data, 5));
    }
}

void StressTest() {
    std::mt19937 gen(3473846);
    std::uniform_int_distribution<int> dist(1, 100);
    const size_t size = 1000;
    const size_t iterations = 1000;
    for (size_t it = 1; it <= iterations; ++it) {
        std::cerr << "Iteration #" << it << "\n";
        vector<int> data(size);
        for (int& elem : data) {
            elem = dist(gen);
        }
        std::sort(data.begin(), data.end());

        int value = dist(gen);
        size_t expected = LowerBoundSlow(data, value);
        size_t actual = LowerBound(data, value);
        if (expected != actual) {
            std::cerr << "FAIL: " << value << " ";
            std::cerr << "expected " << expected;
            std::cerr << ", got " << actual << "\n";
            for (int elem : data) {
                std::cerr << elem << " ";
            }
            break;
        }
    }
}

vector<int> ReadData(size_t size) {
    vector<int> data(size);
    for (int& elem : data) {
        std::cin >> elem;
    }
    return data;
}

int main() {
    /* TestLowerBound(); */
    /* StressTest(); */

/*     std::ios_base::sync_with_stdio(false); */
/*     std::cin.tie(nullptr); */

    size_t size;
    std::cin >> size;
    auto data = ReadData(size);

    size_t queries;
    std::cin >> queries;
    for (size_t i = 0; i < queries; ++i) {
        int value;
        std::cin >> value;
        std::cout << LowerBound(data, value) << "\n";
    }
    return 0;
}
