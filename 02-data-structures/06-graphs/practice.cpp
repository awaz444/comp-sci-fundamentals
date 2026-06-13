// Practice problems: Graphs
//
// 1. Word Ladder         (LeetCode 127, Hard)
// 2. Course Schedule II  (LeetCode 210, Medium/Classic)
// 3. Network Delay Time  (LeetCode 743, Hard)
// 4. Number of Islands   (LeetCode 200, Medium/Classic)

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <climits>

// ============================================================
// 1. Word Ladder (LeetCode 127, Hard)
//    Approach: BFS where neighbors are 1-letter-different words
//    that exist in the word set.
// ============================================================
int ladderLength(const std::string& beginWord, const std::string& endWord,
                  std::vector<std::string>& wordList) {
    std::unordered_set<std::string> dict(wordList.begin(), wordList.end());
    if (dict.find(endWord) == dict.end()) return 0;

    std::queue<std::string> q;
    q.push(beginWord);
    dict.erase(beginWord); // reuse the set as the "visited" set

    int level = 1;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            std::string word = q.front();
            q.pop();

            if (word == endWord) return level;

            for (size_t pos = 0; pos < word.size(); pos++) {
                std::string candidate = word;
                for (char c = 'a'; c <= 'z'; c++) {
                    candidate[pos] = c;
                    if (dict.count(candidate)) {
                        dict.erase(candidate);
                        q.push(candidate);
                    }
                }
            }
        }
        level++;
    }
    return 0; // no transformation sequence found
}

// ============================================================
// 2. Course Schedule II (LeetCode 210, Medium/Classic)
//    Approach: Kahn's algorithm (BFS topological sort).
// ============================================================
std::vector<int> findOrder(int numCourses, const std::vector<std::pair<int,int>>& prerequisites) {
    std::vector<std::vector<int>> adj(numCourses);
    std::vector<int> inDegree(numCourses, 0);

    for (const auto& [course, prereq] : prerequisites) {
        adj[prereq].push_back(course);
        inDegree[course]++;
    }

    std::queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) q.push(i);
    }

    std::vector<int> order;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        order.push_back(curr);

        for (int next : adj[curr]) {
            if (--inDegree[next] == 0) q.push(next);
        }
    }

    if ((int)order.size() != numCourses) return {}; // cycle detected
    return order;
}

// ============================================================
// 3. Network Delay Time (LeetCode 743, Hard)
//    Approach: Dijkstra's algorithm with a min-heap.
// ============================================================
int networkDelayTime(const std::vector<std::vector<int>>& times, int n, int k) {
    // adjacency list: node -> list of (neighbor, weight)
    std::vector<std::vector<std::pair<int,int>>> adj(n + 1);
    for (const auto& t : times) {
        adj[t[0]].push_back({t[1], t[2]});
    }

    std::vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;

    // min-heap of (distance, node)
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> pq;
    pq.push({0, k});

    while (!pq.empty()) {
        auto [d, node] = pq.top();
        pq.pop();

        if (d > dist[node]) continue; // stale entry

        for (auto [neighbor, weight] : adj[node]) {
            if (dist[node] + weight < dist[neighbor]) {
                dist[neighbor] = dist[node] + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    int maxDist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) return -1; // unreachable node
        maxDist = std::max(maxDist, dist[i]);
    }
    return maxDist;
}

// ============================================================
// 4. Number of Islands (LeetCode 200, Medium/Classic)
//    Approach: DFS flood-fill from every unvisited land cell.
// ============================================================
void floodFill(std::vector<std::vector<char>>& grid, int r, int c) {
    int rows = grid.size();
    int cols = grid[0].size();

    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;

    grid[r][c] = '0'; // mark as visited

    floodFill(grid, r + 1, c);
    floodFill(grid, r - 1, c);
    floodFill(grid, r, c + 1);
    floodFill(grid, r, c - 1);
}

int numIslands(std::vector<std::vector<char>> grid) {
    int count = 0;
    for (size_t r = 0; r < grid.size(); r++) {
        for (size_t c = 0; c < grid[0].size(); c++) {
            if (grid[r][c] == '1') {
                count++;
                floodFill(grid, r, c);
            }
        }
    }
    return count;
}

int main() {
    // --- 1. Word Ladder ---
    std::vector<std::string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    std::cout << "Word Ladder (hit -> cog): "
              << ladderLength("hit", "cog", wordList) << '\n'; // 5

    // --- 2. Course Schedule II ---
    // 4 courses, prerequisites: take 1 before 0, 2 before 0, 3 before 1, 3 before 2
    std::vector<std::pair<int,int>> prereqs = {{0,1}, {0,2}, {1,3}, {2,3}};
    std::vector<int> order = findOrder(4, prereqs);
    std::cout << "Course order: ";
    for (int c : order) std::cout << c << ' ';
    std::cout << '\n'; // 3 1 2 0

    // --- 3. Network Delay Time ---
    std::vector<std::vector<int>> times = {{2,1,1}, {2,3,1}, {3,4,1}};
    std::cout << "Network delay time (n=4, k=2): "
              << networkDelayTime(times, 4, 2) << '\n'; // 2

    // --- 4. Number of Islands ---
    std::vector<std::vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    std::cout << "Number of islands: " << numIslands(grid) << '\n'; // 3

    return 0;
}
