# Modifying Algorithms: `fill`, `swap`, `reverse`, `unique`

All from `<algorithm>` (`swap` is also in `<utility>`).

## `fill()`

Assigns a value to every element in a range:

```cpp
std::vector<int> v(5);
std::fill(v.begin(), v.end(), 7); // v = {7, 7, 7, 7, 7}
std::fill(v.begin(), v.begin() + 2, 0); // v = {0, 0, 7, 7, 7}
```

## `swap()`

Exchanges the values of two variables/objects:

```cpp
int a = 1, b = 2;
std::swap(a, b); // a = 2, b = 1
```

- Works on any swappable type, including whole containers:
  `std::swap(vec1, vec2)` swaps their contents in **O(1)** (just swaps
  internal pointers/metadata).
- This is the building block for many algorithms (e.g. swap-based sorting).

## `reverse()`

Reverses the order of elements in place:

```cpp
std::vector<int> v = {1, 2, 3, 4};
std::reverse(v.begin(), v.end()); // v = {4, 3, 2, 1}

std::string s = "hello";
std::reverse(s.begin(), s.end()); // s = "olleh"
```

- **O(n)**, in-place — works by swapping elements from both ends moving
  inward.

## `unique()`

Removes **consecutive** duplicate elements (does NOT remove all
duplicates unless the range is sorted first):

```cpp
std::vector<int> v = {1, 1, 2, 2, 3, 1, 1};
auto last = std::unique(v.begin(), v.end());
v.erase(last, v.end());
// v = {1, 2, 3, 1} — note the trailing 1 remains (not consecutive with the first 1s)
```

- To remove **all** duplicates regardless of position, sort first:
  `std::sort(v.begin(), v.end());` then `std::unique`.
- `unique` doesn't actually shrink the container — it moves unique
  elements to the front and returns an iterator to the new "end". You must
  call `erase` to actually remove the leftover elements — this is the
  classic **"erase-remove idiom"**.

## Key interview points

- `std::swap` on containers is O(1) — it's a pointer/metadata swap, not an
  element-by-element copy.
- `std::unique` requires a **sorted-by-grouping** input to remove all
  duplicates — a very common interview gotcha ("why didn't `unique` remove
  all my duplicates?").
- `fill`, `reverse`, `unique` all operate **in place** — no new container
  is allocated.
