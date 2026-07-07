#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// Runs Dijkstra's algorithm from "start" node.
// adjList[u] = list of {neighbor, weight} pairs.
// Fills dist[] (shortest distance to each node) and parent[] (for path rebuilding).
void dijkstra(vector<vector<pair<int, int>>>& adjList, int start,
              vector<int>& dist, vector<int>& parent) {

    int n = adjList.size();
    dist.assign(n, INT_MAX);
    parent.assign(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0;

    // min-heap of {distance, node} — smallest distance comes out first
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;   // already finalized, skip
        visited[u] = true;

        for (auto edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;
            int newDist = dist[u] + weight;

            if (newDist < dist[v]) {
                dist[v] = newDist;
                parent[v] = u;
                pq.push({newDist, v});
            }
        }
    }
}

// Rebuilds the path from start to "end" using the parent[] array.
vector<int> buildPath(vector<int>& parent, int end) {
    vector<int> path;
    for (int cur = end; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}