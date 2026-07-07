#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) { (void)other; }
PmergeMe& PmergeMe::operator=(const PmergeMe& other) { (void)other; return *this; }

static size_t jacobsthal(size_t n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    size_t prev = 0, curr = 1;
    for (size_t i = 2; i <= n; i++) {
        size_t next = curr + 2 * prev;
        prev = curr;
        curr = next;
    }
    return curr;
}

static bool parseInput(int argc, char** argv, std::vector<int>& vec, std::deque<int>& deq) {
    for (int i = 1; i < argc; i++) {
        std::stringstream ss(argv[i]);
        long num;
        if (!(ss >> num) || !ss.eof() || num < 0 || num > 2147483647) {
            std::cerr << "Error" << std::endl;
            return false;
        }
        vec.push_back(static_cast<int>(num));
        deq.push_back(static_cast<int>(num));
    }
    return true;
}

// --- Vector version ---

static void binaryInsertVec(std::vector<int>& arr, int value, size_t end) {
    size_t left = 0, right = end;
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    arr.insert(arr.begin() + left, value);
}

void PmergeMe::mergeInsertVector(std::vector<int>& arr) {
    if (arr.size() <= 1)
        return;

    std::vector<std::pair<int, int> > pairs;
    int straggler = -1;
    bool hasStraggler = (arr.size() % 2 != 0);

    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
    }
    if (hasStraggler)
        straggler = arr[arr.size() - 1];

    // on trie recursivement les plus grands elements
    std::vector<int> mainChain;
    for (size_t i = 0; i < pairs.size(); i++)
        mainChain.push_back(pairs[i].first);

    mergeInsertVector(mainChain);

    // on remet les pendants dans le bon ordre apres le tri recursif
    std::vector<int> pend;
    for (size_t i = 0; i < mainChain.size(); i++) {
        for (size_t j = 0; j < pairs.size(); j++) {
            if (pairs[j].first == mainChain[i]) {
                pend.push_back(pairs[j].second);
                pairs[j].first = -1; // marquer comme utilisé
                break;
            }
        }
    }

    // on met pend[0] devant mainChain[0] car il est forcement plus petit
    std::vector<int> result;
    result.push_back(pend[0]);
    for (size_t i = 0; i < mainChain.size(); i++)
        result.push_back(mainChain[i]);

    // insertion des pendants restants avec jacobsthal
    size_t inserted = 1;
    for (size_t k = 2; ; k++) {
        size_t jk = jacobsthal(k);
        if (jk > pend.size())
            jk = pend.size();
        size_t prev_jk = jacobsthal(k - 1);

        for (size_t idx = jk; idx > prev_jk; idx--) {
            if (idx - 1 >= pend.size() || idx - 1 < 1)
                continue;
            size_t bound = idx + inserted - 1;
            if (bound > result.size())
                bound = result.size();
            binaryInsertVec(result, pend[idx - 1], bound);
            inserted++;
        }
        if (jk >= pend.size())
            break;
    }

    if (hasStraggler)
        binaryInsertVec(result, straggler, result.size());

    arr = result;
}

// --- Deque version ---

static void binaryInsertDeq(std::deque<int>& arr, int value, size_t end) {
    size_t left = 0, right = end;
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    arr.insert(arr.begin() + left, value);
}

void PmergeMe::mergeInsertDeque(std::deque<int>& arr) {
    if (arr.size() <= 1)
        return;

    std::vector<std::pair<int, int> > pairs;
    int straggler = -1;
    bool hasStraggler = (arr.size() % 2 != 0);

    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] > arr[i + 1])
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        else
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
    }
    if (hasStraggler)
        straggler = arr[arr.size() - 1];

    std::deque<int> mainChain;
    for (size_t i = 0; i < pairs.size(); i++)
        mainChain.push_back(pairs[i].first);

    mergeInsertDeque(mainChain);

    std::vector<int> pend;
    for (size_t i = 0; i < mainChain.size(); i++) {
        for (size_t j = 0; j < pairs.size(); j++) {
            if (pairs[j].first == static_cast<int>(mainChain[i])) {
                pend.push_back(pairs[j].second);
                pairs[j].first = -1;
                break;
            }
        }
    }

    std::deque<int> result;
    result.push_back(pend[0]);
    for (size_t i = 0; i < mainChain.size(); i++)
        result.push_back(mainChain[i]);

    size_t inserted = 1;
    for (size_t k = 2; ; k++) {
        size_t jk = jacobsthal(k);
        if (jk > pend.size())
            jk = pend.size();
        size_t prev_jk = jacobsthal(k - 1);

        for (size_t idx = jk; idx > prev_jk; idx--) {
            if (idx - 1 >= pend.size() || idx - 1 < 1)
                continue;
            size_t bound = idx + inserted - 1;
            if (bound > result.size())
                bound = result.size();
            binaryInsertDeq(result, pend[idx - 1], bound);
            inserted++;
        }
        if (jk >= pend.size())
            break;
    }

    if (hasStraggler)
        binaryInsertDeq(result, straggler, result.size());

    arr = result;
}

void PmergeMe::sort(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error" << std::endl;
        return;
    }

    std::vector<int> vec;
    std::deque<int> deq;

    if (!parseInput(argc, argv, vec, deq))
        return;

    std::cout << "Before:";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << " " << vec[i];
    std::cout << std::endl;

    struct timeval start, end;

    gettimeofday(&start, NULL);
    mergeInsertVector(vec);
    gettimeofday(&end, NULL);
    double timeVector = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    mergeInsertDeque(deq);
    gettimeofday(&end, NULL);
    double timeDeque = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);

    std::cout << "After:";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << " " << vec[i];
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " << timeVector << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size()
              << " elements with std::deque : " << timeDeque << " us" << std::endl;
}
