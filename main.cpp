#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

// These functions are defined in dijkstra.cpp
void dijkstra(vector<vector<pair<int, int>>> &adjList, int start,
              vector<int> &dist, vector<int> &parent);
vector<int> buildPath(vector<int> &parent, int end);

// Removes the road between u and v (blocks it) without rebuilding the graph
void blockRoad(vector<vector<pair<int, int>>> &adjList, int u, int v)
{
    // remove v from u's list
    for (int i = 0; i < (int)adjList[u].size(); i++)
    {
        if (adjList[u][i].first == v)
        {
            adjList[u].erase(adjList[u].begin() + i);
            break;
        }
    }
    // remove u from v's list (undirected graph, so both sides need updating)
    for (int i = 0; i < (int)adjList[v].size(); i++)
    {
        if (adjList[v][i].first == u)
        {
            adjList[v].erase(adjList[v].begin() + i);
            break;
        }
    }
}

int main()
{
    int n;
    cout << "Enter number of locations: ";
    cin >> n;

    vector<string> names(n);
    cout << "Enter " << n << " location names:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> names[i];
    }

    // adjList[u] = list of {neighbor, weight} pairs for node u
    vector<vector<pair<int, int>>> adjList(n);

    int edges;
    cout << "Enter number of roads: ";
    cin >> edges;

    cout << "Enter each road as: from to weight\n";
    for (int i = 0; i < edges; i++)
    {
        string from, to;
        int weight;
        cin >> from >> to >> weight;

        int u = find(names.begin(), names.end(), from) - names.begin();
        int v = find(names.begin(), names.end(), to) - names.begin();

        if (u >= n || v >= n)
        {
            cout << "Invalid location name, skipping.\n";
            continue;
        }
        if (weight < 0)
        {
            cout << "Negative weight not allowed, skipping.\n";
            continue;
        }

        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // undirected, so add both ways
    }

    // print the graph
    cout << "\nGraph (Adjacency List):\n";
    for (int i = 0; i < n; i++)
    {
        cout << names[i] << " -> ";
        for (auto edge : adjList[i])
        {
            cout << names[edge.first] << "(" << edge.second << ") ";
        }
        cout << "\n";
    }

    int choice;
    do
    {
        cout << "\n--- Menu ---\n";
        cout << "1. Find shortest path\n";
        cout << "2. Block a road (road closed)\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string src, dest;
            cout << "Enter source: ";
            cin >> src;
            cout << "Enter destination: ";
            cin >> dest;

            int start = find(names.begin(), names.end(), src) - names.begin();
            int end = find(names.begin(), names.end(), dest) - names.begin();

            if (start >= n || end >= n)
            {
                cout << "Invalid location name.\n";
                continue;
            }

            vector<int> dist, parent;
            dijkstra(adjList, start, dist, parent);

            if (dist[end] == INT_MAX)
            {
                cout << "No path exists between " << src << " and " << dest << ".\n";
            }
            else
            {
                vector<int> path = buildPath(parent, end);

                cout << "Shortest path: ";
                for (int i = 0; i < (int)path.size(); i++)
                {
                    cout << names[path[i]];
                    if (i != (int)path.size() - 1)
                        cout << " -> ";
                }
                cout << "\nTotal cost: " << dist[end] << "\n";
            }
        }
        else if (choice == 2)
        {
            string from, to;
            cout << "Enter road to block (from to): ";
            cin >> from >> to;

            int u = find(names.begin(), names.end(), from) - names.begin();
            int v = find(names.begin(), names.end(), to) - names.begin();

            if (u >= n || v >= n)
            {
                cout << "Invalid location name.\n";
                continue;
            }

            blockRoad(adjList, u, v);
            cout << "Road between " << from << " and " << to << " is now blocked.\n";
        }
        else if (choice == 3)
        {
            cout << "Done.\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 3);

    return 0;
}