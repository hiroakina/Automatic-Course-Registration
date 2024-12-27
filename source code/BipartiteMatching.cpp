#include <iostream>
#include <string>
#include "BipartiteMatching.h"
using namespace std;


// Constructor to initialize the bipartite matching object
BipartiteMatching::BipartiteMatching(int n)
    : num_vertices(n), graph(n), match(n, -1), alive(n, 1), used(n, 0), timestamp(0) {
    if (n <= 0) {
        throw invalid_argument("Number of vertices must be positive.");
    }
}

// add an edge between vertices u and v
void BipartiteMatching::add_edge(int u, int v) {
    if (u < 0 || u >= num_vertices || v < 0 || v >= num_vertices) {
        throw out_of_range("Vertex index out of bounds.");
    }
    graph[u].push_back(v);
    graph[v].push_back(u);
}

// Depth-first search function to find an augmenting path
bool BipartiteMatching::dfs(int idx) {
    used[idx] = timestamp; // mark the vertex as used in the current DFS run
    for (int to : graph[idx]) {
        int to_match = match[to]; // get the match for the adjacent vertex
        if (alive[to] == 0) continue; // skip if the vertex is not alive
        // If the adjacent vertex is unmatched or we can find an augmenting path
        if (to_match == -1 || (used[to_match] != timestamp && dfs(to_match))) {
            match[idx] = to; // update the match for the current vertex
            match[to] = idx; // update the match for the adjacent vertex
            return true; // found an augmenting path
        }
    }
    return false; // No augmenting path found
}

// find the maximum bipartite matching
int BipartiteMatching::bipartite_matching() {
    int ret = 0;
    for (int i = 0; i < num_vertices; ++i) {
        if (alive[i] == 0) continue;
        if (match[i] == -1) {
            ++timestamp;
            ret += dfs(i);
        }
    }
    return ret;
}

// output the matching
void BipartiteMatching::output() {
    for (int i = 0; i < num_vertices; ++i) {
        if (i < match[i]) {
            cout << i << "-" << match[i] << endl;
        }
    }
}

// get the match for a vertex
int BipartiteMatching::get_match(int m) {
    if (m < 0 || m >= static_cast<int>(match.size())) {
        throw out_of_range("Vertex index out of range in get_match.");
    }
    return match[m];
}