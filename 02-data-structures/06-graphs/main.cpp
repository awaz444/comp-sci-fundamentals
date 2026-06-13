#include <iostream>
#include <vector>
#include <queue>

// ============================================================
// Edge List representation
// ============================================================
void printEdgeList(const std::vector<std::pair<int, int>>& edges) {
    std::cout << "Edge List: ";
    for (const auto& [u, v] : edges) {
        std::cout << "(" << u << "," << v << ") ";
    }
    std::cout << '\n';
}

// ============================================================
// Adjacency Matrix representation
// ============================================================
void printAdjMatrix(const std::vector<std::vector<int>>& matrix) {
    std::cout << "Adjacency Matrix:\n";
    for (const auto& row : matrix) {
        for (int val : row) std::cout << val << ' ';
        std::cout << '\n';
    }
}

// ============================================================
// Adjacency List representation + BFS/DFS
// ============================================================
void printAdjList(const std::vector<std::vector<int>>& adj) {
    std::cout << "Adjacency List:\n";
    for (size_t i = 0; i < adj.size(); i++) {
        std::cout << i << ": ";
        for (int neighbor : adj[i]) std::cout << neighbor << ' ';
        std::cout << '\n';
    }
}

// BFS using a queue and a visited set
void bfs(const std::vector<std::vector<int>>& adj, int start) {
    std::vector<bool> visited(adj.size(), false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    std::cout << "BFS from " << start << ": ";
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        std::cout << curr << ' ';

        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    std::cout << '\n';
}

// DFS using recursion and a visited set
void dfsHelper(const std::vector<std::vector<int>>& adj, int curr, std::vector<bool>& visited) {
    visited[curr] = true;
    std::cout << curr << ' ';
    for (int neighbor : adj[curr]) {
        if (!visited[neighbor]) {
            dfsHelper(adj, neighbor, visited);
        }
    }
}

void dfs(const std::vector<std::vector<int>>& adj, int start) {
    std::vector<bool> visited(adj.size(), false);
    std::cout << "DFS from " << start << ": ";
    dfsHelper(adj, start, visited);
    std::cout << '\n';
}

int main() {
    // Undirected graph with 5 vertices (0-4) and edges:
    // 0-1, 0-2, 1-3, 2-3, 3-4
    const int V = 5;
    std::vector<std::pair<int, int>> edges = {{0,1}, {0,2}, {1,3}, {2,3}, {3,4}};

    // --- Edge List ---
    printEdgeList(edges);

    // --- Adjacency Matrix ---
    std::vector<std::vector<int>> matrix(V, std::vector<int>(V, 0));
    for (const auto& [u, v] : edges) {
        matrix[u][v] = 1;
        matrix[v][u] = 1; // undirected
    }
    printAdjMatrix(matrix);

    // --- Adjacency List ---
    std::vector<std::vector<int>> adj(V);
    for (const auto& [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected
    }
    printAdjList(adj);

    // --- Traversals ---
    bfs(adj, 0); // 0 1 2 3 4
    dfs(adj, 0); // 0 1 3 2 4

    return 0;
}
