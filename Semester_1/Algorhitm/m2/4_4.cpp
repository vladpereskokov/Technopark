#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

using data_type = int;
using size_type = size_t;
using statistic_type = size_t;

bool less(const data_type lhs, const data_type rhs) {
  return lhs < rhs;
}

size_t random(const size_type begin, const size_type end) {
  std::mt19937 mt(time(0));
  auto rand = std::bind(std::uniform_int_distribution<size_t>(begin, end), std::mt19937(mt));
  return rand();
}

template <class IT, class comparator>
IT partition_(IT begin, IT end, comparator &comp) {
  IT pivot = end - 1;
  IT it = begin - 1;
  for (IT jt = begin; jt != pivot; ++jt) {
    if (comp(*jt, *pivot)) {
      ++it;
      std::swap(*it, *jt);
    }
  }
  ++it;
  std::swap(*it, *pivot);
  return it;
}

template <class IT, class comparator>
IT partitionReverse_(IT begin, IT end, comparator &comp) {
  IT pivot = begin;
  IT it = end - 1;
  for (IT jt = end - 1; jt != pivot; --jt) {
    if (comp(*pivot, *jt)) {
      std::swap(*it, *jt);
      --it;
    }
  }
  std::swap(*it, *pivot);
  return it;
}

template <class IT, class comparator>
IT randomPartition(IT begin, IT end, comparator &comp) {
  size_type pivot = random(0, std::distance(begin, end) - 1);
  if (pivot != 0) {
    std::swap(*begin, *(begin + pivot));
  }
  return partitionReverse_(begin, end, comp);
}

template <class IT, class comparator>
data_type nthStatistic(IT begin, IT end, statistic_type k, comparator &comp) {
  IT first = begin;
  while (true) {
    size_type pivot = std::distance(begin, randomPartition(first, end, comp));
    if (pivot < k) {
      first = begin + pivot + 1;
    } else if (pivot > k) {
      end = begin + pivot;
    } else {
      return *(begin + pivot);
    }
  }
}

template <class IT, class comparator>
data_type nthStatistic(IT begin, IT end, IT k, comparator &comp) {
  while (true) {
    IT pivot = randomPartition(begin, end, comp);
    if (pivot < k) {
      begin = pivot + 1;
    } else if (pivot > k) {
      end = pivot;
    } else {
      return *pivot;
    }
  }
}

int main() {
  int n;
  int k;
  scanf("%d %d", &n, &k);
  if (k < n && k >= 0) {
    std::vector<int> target;
    for (size_t i = 1; i <= n; ++i) {
      int in;
      scanf("%d", &in);
      target.push_back(in);
    }
    printf("%d\n", nthStatistic(target.begin(), target.end(), target.begin() + k, less));
  }
  return 0;
}
