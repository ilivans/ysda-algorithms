#include <vector>
#include <iostream>


std::vector<int> ReadArray(std::istream &in_stream = std::cin) {
    int size;
    in_stream >> size;
    std::vector<int> array(size);
    for (int i = 0; i < size; ++i) {
        in_stream >> array[i];
    }
    return array;
}

void PrintNumber(int number, std::ostream &out_stream = std::cout) {
    out_stream << number;
}

void PrintArray(const std::vector<int>& array, std::ostream &out_stream = std::cout) {
    for (const auto& element : array) {
        PrintNumber(element);
        out_stream << " ";
    }
    out_stream << std::endl;
}

std::vector<int> FindMaxAltSubsequence(const std::vector<int>& array) {
    int size = array.size();
    std::vector<int> lens_max(size, 1);
    std::vector<int> lens_min(size, 1);
    int maxs_id = size - 1;
    int mins_id = size - 1;
    bool max_step;
    bool min_step;
    for (int id = size - 2; id >= 0; --id) {
        max_step = false;
        min_step = false;
        for (int j = id + 1; j < size; ++j) {
            if (array[id] < array[j] && lens_min[id] <= lens_max[j]) {
                min_step = true;
                lens_min[id] = lens_max[j];
            }
            else if (array[id] > array[j] && lens_max[id] <= lens_min[j]) {
                max_step = true;
                lens_max[id] = lens_min[j];
            }
        }
        if (max_step) {
            ++lens_max[id];
        }
        if (min_step) {
            ++lens_min[id];
        }
        if (lens_max[id] >= lens_max[maxs_id]) {
            maxs_id = id;
        }
        if (lens_min[id] >= lens_min[mins_id]) {
            mins_id = id;
        }
    }
    max_step = true;
    int val = lens_max[maxs_id];
    if ((lens_max[maxs_id] < lens_min[mins_id]) ||
            (lens_max[maxs_id] == lens_min[mins_id] && maxs_id > mins_id)) {
        max_step = false;
        val = lens_min[mins_id];
        maxs_id = mins_id;
    }
    std::vector<int> answer{};
    for (int i = maxs_id; i < size; ++i) {
        if (max_step && lens_max[i] == val && ((i == maxs_id) || array[i] > answer.back())) {
            answer.push_back(array[i]);
            --val;
            max_step = false;
        }
        else if (!max_step && lens_min[i] == val && ((i == maxs_id) || array[i] < answer.back())) {
            answer.push_back(array[i]);
            --val;
            max_step = true;
        }
    }
    return answer;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    auto array = ReadArray();
    auto result = FindMaxAltSubsequence(array);
    PrintArray(result);
    return 0;
}
