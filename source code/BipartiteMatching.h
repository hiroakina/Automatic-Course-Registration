#ifndef BIPARTITEMATCHING_H
#define BIPARTITEMATCHING_H
#include <string>
#include <vector>

class BipartiteMatching {
private:
	std::vector<std::vector<int>> graph; // adjacency list for the bipartite graph
	std::vector<int> match;  // array to store the match for each vertex
	std::vector<int> alive; // array to indicate if a vertex is alive
	std::vector<int> used;  // array to indicate if a vertex has been used in the current DFS
	int num_vertices; // number of vertices
	int timestamp; // timestamp for the current DFS run

	// Depth-first search function to find an augmenting path
	bool dfs(int idx);

public:
	

	// constructor to initialize the bipartite matching object
	BipartiteMatching(int n);

	//add an edge between vertices u and v
	void add_edge(int u, int v);

	//find the maximum bipartite matching
	int bipartite_matching();

	//output the matching
	void output();

	//get the match for a vertex
	int get_match(int m);
};



#endif
