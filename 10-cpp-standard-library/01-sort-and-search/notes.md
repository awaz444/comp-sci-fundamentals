# Sorting & Searching Algorithms

All from `<algorithm>`. These operate on **iterator ranges**
`[first, last)` — works on `std::vector`, arrays, and any other container
with compatible iterators.

## `sort()`

```cpp
std::vector<int> v = {5, 2, 4, 1, 3};
std::sort(v.begin(), v.end());              // ascending: 1 2 3 4 5
std::sort(v.begin(), v.end(), std::greater<int>()); // descending: 5 4 3 2 1

// custom comparator (lambda)
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
```

- Average complexity: **O(n log n)** (typically introsort: quicksort +
  heapsort fallback).
- Not stable by default — use `std::stable_sort` if relative order of
  equal elements must be preserved.

## `find()`

```cpp
auto it = std::find(v.begin(), v.end(), 3);
if (it != v.end()) {
    std::cout << "Found at index " << (it - v.begin()) << '\n';
}
```

- Linear search, **O(n)**. Works on unsorted ranges.
- Returns an iterator to the first match, or `end()` if not found.

## `find_if()` / `find_if_not()`

Find the first element satisfying (or not satisfying) a predicate:

```cpp
auto it = std::find_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
// it points to the first even number

auto it2 = std::find_if_not(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
// it2 points to the first ODD number
```

## `count()` / `count_if()`

```cpp
int n = std::count(v.begin(), v.end(), 3);          // # of elements equal to 3
int evens = std::count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
```

Both are **O(n)** — they always scan the whole range (no early exit, since
they count *all* matches).

## Key interview points

- `std::sort` requires **random-access iterators** (works on
  `vector`/`array`/raw arrays, NOT `std::list`, which has `sort()` as a
  member function instead).
- `find`/`count` family is **O(n)** — for sorted data, prefer
  `std::binary_search`, `std::lower_bound`, `std::upper_bound` (O(log n)).
- `find_if`/`count_if` taking a predicate (lambda/function) is the
  idiomatic way to search by a condition rather than exact value equality.
