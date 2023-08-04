#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

void shortestPath(const vector<vector<Edge>>& graph, int source) {
    int numVertices = graph.size();
    vector<int> distances(numVertices, INF);
    vector<int> parent(numVertices, -1);

    distances[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                parent[v] = u;
                pq.push(make_pair(distances[v], v));
            }
        }
    }

    cout << "Shortest paths from vertex " << source << ":\n";
    for (int i = 0; i < numVertices; ++i) {
        cout << "Vertex " << i << ": Distance = " << distances[i] << ", Path = ";
        vector<int> path;
        int current = i;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        for (int j = path.size() - 1; j >= 0; --j) {
            cout << path[j];
            if (j != 0) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<vector<Edge>> graph(numVertices);

    cout << "Enter the edges (from to weight):\n";
    for (int i = 0; i < numEdges; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from].emplace_back(to, weight);
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    shortestPath(graph, source);

    return 0;
}
