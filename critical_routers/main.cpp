#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using adjacency_list_t = vector<vector<int>>;
using edge_list_t = vector<pair<int,int>>;

const int MAXN = 7;
//vector<int> graph[MAXN];

vector<vector<int>> graph(MAXN, vector<int>());

vector<bool> visited(MAXN, false);
int timer, node_walk_num[MAXN], low_link[MAXN];


void IS_CUTPOINT(int v) {
    cout << v << ", ";
}



void dfs (int current, int parent = -1) {
    visited[current] = true;
    node_walk_num[current] = low_link[current] = timer++;
    int children = 0;
    auto g_v_size = graph[current].size();
    for (size_t i = 0; i < g_v_size; ++i) {
        int to = graph[current][i];
        if (to == parent)  continue;
        if (visited[to])
            low_link[current] = min (low_link[current], node_walk_num[to]);
        else {
            dfs (to, current);
            low_link[current] = min (low_link[current], low_link[to]);
            if (low_link[to] >= node_walk_num[current] && parent != -1)
                IS_CUTPOINT(current);
            ++children;
        }
    }
    if (parent == -1 && children > 1)
        IS_CUTPOINT(current);
}

adjacency_list_t convert(const edge_list_t & edges) {

    auto max_vertex = std::max_element(edges.begin(), edges.end(), [](const edge_list_t::value_type & a, const edge_list_t::value_type & b) { return max(a.first, a.second) < max(b.first, b.second); });

    int graph_size = (max(max_vertex->first, max_vertex->second)) + 1;

    adjacency_list_t graph(graph_size);

    for(auto [u, v] : edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return graph;
}


vector<int> find_cutpoints(const edge_list_t & edges) {

    adjacency_list_t graph = convert(edges);

    // number of nodes in the graph
    int graph_size = graph.size();
    // number of the current step of the graph traversal
    int timer = 0;
    // vertex with lowest visiting time reachable from the current vertex
    vector<int> lowest_time(graph_size);
    vector<int> vertex_walk_time(graph_size);
    // visited vertices
    vector<bool> visited(graph_size, false);
    // found articulation points
    vector<int> cutpoints;

    auto find_cutpoints_dfs = [&lowest_time, &vertex_walk_time, &visited, &timer, &graph, &cutpoints] (auto& self, int current, int parent = -1) -> void {
        visited[current] = true;
        vertex_walk_time[current] = lowest_time[current] = timer++;
        int children = 0; // number of outgoing edges from the current vertex
        // number of vertices connected ot the current vertex
        auto neighbors = graph[current].size();
        for (size_t i = 0; i < neighbors; ++i) {
            // neighbor vertex connected to the current vertex by directed edge outgoing from the current vertex
            int to_vertex = graph[current][i];
            // exclude parent vertex from the processing because we process directed graph
            if (to_vertex == parent) { continue; }
            // if we met already visited vertex
            if (visited[to_vertex]) {
                lowest_time[current] = min(lowest_time[current], vertex_walk_time[to_vertex]);
            }
            else {
                self(self, to_vertex, current);
                lowest_time[current] = min(lowest_time[current], lowest_time[to_vertex]);

                if (lowest_time[to_vertex] >= vertex_walk_time[current] && parent != -1) {
                    cutpoints.push_back(current);
                }
                ++children;
            }
        }
        // if parent is root vertex and it has more than one outgoing edge
        // this vertex is a cut point
        if (parent == -1 && children > 1) {
            cutpoints.push_back(current);
        }
    };

    find_cutpoints_dfs(find_cutpoints_dfs, 0);

    return cutpoints;
}


int main() {

    // Input: numNodes = 7, numEdges = 7, edges = [[0, 1], [0, 2], [1, 3], [2, 3], [2, 5], [5, 6], [3, 4]]
    // Output: [2, 3, 5]

    edge_list_t edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {2, 5}, {5, 6}, {3, 4}};

    int n = MAXN;
    timer = 0;

    // fill graph

    for(auto [u, v] : edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << "Graph: " << endl;
    for(int i = 0; i < MAXN; ++i) {
        cout << "Node: " << i << ": ";
        for(auto n: graph[i]) {
            cout << n << ", ";
        }
        cout << endl;
    }
    cout << endl;


    cout << "Articulation points: " << endl;

    dfs (0);

    cout << endl;


    auto cutpoints =  find_cutpoints(edges);

    for(auto i: cutpoints) {
        cout << i << ", ";
    }
    cout << endl;

    return 0;
}

