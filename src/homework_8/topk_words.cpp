// Read files and prints top k word by frequency
//5 files + one thread = 200 ms
//5 files + five thread = 93 ms

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <future>
#include <execution>
#include <stdexcept>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;
using namespace std::string_literals;

std::string tolower(const std::string &str);
void count_words(std::istream& stream, Counter&);
void print_topk(std::ostream& stream, const Counter&, const size_t k);
void mergeDict(const Counter& input, Counter& output);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::future<Counter>> futures;
    for (int i = 1; i < argc; i++) {
        futures.emplace_back(std::async(std::launch::async, [&argv, i]() {
            std::ifstream input{argv[i]};
            if (!input.is_open()) {
                throw std::runtime_error("Failed to open file "s + std::string(argv[i]));
            }
            Counter freq_dict;
            count_words(input, freq_dict);
            return freq_dict;
        }));
    }

    Counter freq_dict;
    try {
        for (auto& item : futures) {
            mergeDict(item.get(), freq_dict);
        }
    } catch (std::runtime_error& err) {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }

    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream& stream, Counter& counter) {
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });    
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}

void mergeDict(const Counter& input, Counter& output) {
    for (const auto& [word, freq] : input ) {
        output[word] += freq;
    }
}