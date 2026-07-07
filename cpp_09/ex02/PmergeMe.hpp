#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe {
private:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();
    
    static void mergeInsertVector(std::vector<int>& arr);
    static void mergeInsertDeque(std::deque<int>& arr);
    
public:
    static void sort(int argc, char** argv);
};

#endif
