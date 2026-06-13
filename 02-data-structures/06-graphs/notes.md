# Graphs

A **graph** is a set of **vertices** (nodes) connected by **edges**.
Graphs generalize trees — they can have cycles, disconnected
components, and multiple paths between nodes.

## Terminology / Properties

- **Directed** vs **Undirected**: edges have a direction (A -> B) vs
  none (A -- B).
- **Weighted** vs **Unweighted**: edges may carry a cost/weight.
- **Cyclic** vs **Acyclic**: whether the graph contains cycles (a DAG —
  Directed Acyclic Graph — is a common special case).
- **Connected**: every vertex is reachable from every other vertex (for
  undirected graphs); **strongly connected** is the directed analogue.
- **Degree** of a vertex: number of edges incident to it (in-degree /
  out-degree for directed graphs).
- **Path**: a sequence of edges connecting a sequence of vertices.
- **Dense** vs **Sparse**: how many edges relative to the maximum
  possible (`V*(V-1)` for directed, `V*(V-1)/2` for undirected).

## Representations

### 1. Edge List

A simple list of all edges: `(u, v)` pairs (optionally with weight).

```cpp
std::vector<std::pair<int,int>> edges = {{0,1}, {1,2}, {0,2}};
```

- **Pros**: simple, compact for sparse graphs, easy to iterate over all
  edges.
- **Cons**: checking if `(u, v)` is an edge is O(E); no fast access to
  "all neighbors of v".

### 2. Adjacency Matrix

A `V x V` matrix where `matrix[i][j] = 1` (or weight) if an edge exists
from `i` to `j`.

```cpp
std::vector<std::vector<int>> matrix(V, std::vector<int>(V, 0));
matrix[0][1] = 1; // edge from 0 to 1
```

- **Pros**: O(1) edge lookup; simple to implement.
- **Cons**: O(V²) space regardless of how many edges exist — wasteful
  for sparse graphs. Iterating over neighbors of a vertex is O(V).

### 3. Adjacency List

For each vertex, store a list of its neighbors.

```cpp
std::vector<std::vector<int>> adj(V);
adj[0].push_back(1); // edge from 0 to 1
adj[1].push_back(0); // (if undirected, add both directions)
```

- **Pros**: O(V + E) space — efficient for sparse graphs (most
  real-world graphs). Iterating over neighbors of a vertex is fast
  (proportional to its degree).
- **Cons**: checking if `(u, v)` is an edge takes O(degree(u)) instead
  of O(1).

## Comparison

| Representation | Space | Edge lookup | Iterate neighbors |
|---|---|---|---|
| Edge List | O(E) | O(E) | O(E) |
| Adjacency Matrix | O(V²) | O(1) | O(V) |
| Adjacency List | O(V + E) | O(degree) | O(degree) |

## Key interview points

- **Adjacency list is the default choice** for most graph problems —
  most real-world graphs are sparse (E << V²).
- Adjacency matrix is preferred when the graph is dense, or when O(1)
  edge-existence checks are critical and memory isn't a concern.
- Both BFS and DFS (the same algorithms used for tree traversal) extend
  directly to graphs — the key addition is a **visited set** to avoid
  infinite loops in cyclic graphs (see
  [Binary Trees](../04-binary-trees/notes.md) for the tree versions).
- For undirected graphs, remember to add edges in **both** directions
  in an adjacency list/matrix.

## Practice Problems (LeetCode)

See `practice.cpp` for full working solutions.

1. **[Hard] Word Ladder** (LeetCode 127) — Given a start word, end word,
   and a word list, find the length of the shortest transformation
   sequence where each step changes exactly one letter and each
   intermediate word must exist in the word list. Approach: BFS where
   each "neighbor" of a word is obtained by changing one character at a
   time to every letter a-z and checking membership in the word set.
   The first time the end word is reached, the BFS depth is the answer.

2. **[Medium/Classic] Course Schedule II** (LeetCode 210) — Given course
   prerequisites (directed edges), return a valid ordering to take all
   courses, or an empty list if impossible (cycle). Approach:
   **topological sort** via Kahn's algorithm — compute in-degrees,
   repeatedly remove nodes with in-degree 0 (BFS with a queue), and
   append them to the result. If not all nodes are processed, a cycle
   exists.

3. **[Hard] Network Delay Time** (LeetCode 743) — Given a weighted
   directed graph and a source node, find the time for a signal to
   reach all nodes (or -1 if impossible). Approach: **Dijkstra's
   algorithm** — a min-heap (`priority_queue`) of `(distance, node)`,
   relaxing edges greedily; the answer is the maximum finite distance
   to any node.

4. **[Medium/Classic] Number of Islands** (LeetCode 200) — Given a grid
   of `1`s (land) and `0`s (water), count the number of islands
   (connected components of `1`s, 4-directionally connected). Approach:
   DFS or BFS flood-fill from every unvisited land cell, marking all
   connected land cells as visited; each flood-fill started = one
   island.
