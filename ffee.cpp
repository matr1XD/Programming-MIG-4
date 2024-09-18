#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

struct Edge {
    int v;             // Target vertex
    int flow;          // Current flow through the edge
    int capacity;      // Capacity of the edge
    Edge* reverse;     // Pointer to the reverse edge

    Edge(int v, int capacity) : v(v), flow(0), capacity(capacity), reverse(nullptr) {}
};

class GraphList {
    int V; // Number of vertices
    vector<vector<Edge*>> adj; // Adjacency list for storing pointers to edges

public:
    GraphList(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int capacity) {
        Edge* forwardEdge = new Edge(v, capacity);
        Edge* reverseEdge = new Edge(u, 0); // Reverse edge has 0 capacity initially

        // Link the forward and reverse edges
        forwardEdge->reverse = reverseEdge;
        reverseEdge->reverse = forwardEdge;

        // Add the edges to adjacency list
        adj[u].push_back(forwardEdge);
        adj[v].push_back(reverseEdge); // Reverse edge is added to the reverse adjacency list
    }

    bool bfs(int s, int t, vector<Edge*>& parent) {
        fill(parent.begin(), parent.end(), nullptr);
        queue<pair<int, int>> q; // (vertex, flow)
        q.push({s, INF});

        while (!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();

            // Traverse all adjacent edges
            for (Edge* edge : adj[cur]) {
                if (!parent[edge->v] && edge->v != s && edge->flow < edge->capacity) {
                    parent[edge->v] = edge;
                    int new_flow = min(flow, edge->capacity - edge->flow);

                    // If we reached the sink, return the flow found
                    if (edge->v == t)
                        return new_flow;

                    q.push({edge->v, new_flow});
                }
            }
        }

        return 0;
    }

    int edmondsKarp(int s, int t) {
        int total_flow = 0;
        vector<Edge*> parent(V);

        int flow;
        // Augment the flow while there's a path from source to sink
        while (flow = bfs(s, t, parent)) {
            total_flow += flow;

            // Update the capacities and reverse flows along the path
            int cur = t;
            while (cur != s) {
                Edge* edge = parent[cur];
                edge->flow += flow;               // Update forward edge's flow
                edge->reverse->flow -= flow;      // Update reverse edge's flow (residual capacity)
                cur = edge->reverse->v;
            }
        }

        return total_flow;
    }

    bool dfs(int s, int t, vector<Edge*>& parent, vector<bool> &visited) {
        if(s == t) return true;
        visited[s] = true;

        for(Edge * edge : adj[s])
        {
            if(!visited[edge->v] and edge->flow < edge->capacity)
            {
                parent[edge->v] = edge;
                if(dfs(edge->v, t, parent, visited)) return true;
            }
        }

        return false;
    }

    int fordFulkerson(int s, int t) {
        int total_flow = 0;
        vector<Edge*> parent(V, nullptr);  // To store the path
        vector<bool> visited(V, 0);    // To keep track of visited nodes

        // Augment the flow while there is an augmenting path
        while(dfs(s, t, parent, visited)) {
            int flow = INF;
            int cur = t;
            while (cur != s) {
                Edge* edge = parent[cur];
                flow = min(flow, edge->capacity - edge->flow);
                cur = edge->reverse->v;
            }

            // Update the flow values along the path
            cur = t;
            while (cur != s) {
                Edge* edge = parent[cur];
                edge->flow += flow;             // Update forward edge's flow
                edge->reverse->flow -= flow;    // Update reverse edge's flow (residual capacity)
                cur = edge->reverse->v;
            }

            total_flow += flow;  // Add the flow from this path to the total flow
        }

        return total_flow;
    }

    void display() {
        for (int i = 0; i < V; i++) {
            cout << i;
            for (Edge* edge : adj[i]) {
                cout << "  -> " << edge->v<< " (capacity: " << edge->capacity<< " flow: " << edge->flow << ")"<<endl;
            }
        }
    }
};


class GraphMatrix
{
    int V; //Number of vertices
    vector<vector<int>> adj; //Adjacency matrix
    public:
    GraphMatrix(int V)
    {
        this->V = V;
        adj.resize(V, vector<int>(V,0)); //adj all 0's
    }

    void addEdge(int u, int v, int capacity)
    {
        adj[u][v] = capacity;
    }

    bool bfs(int s, int t, vector<int>& parent) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < V; ++v) {
                if (!visited[v] && adj[u][v] > 0) {
                    q.push(v);
                    visited[v] = true;
                    parent[v] = u;

                    if (v == t) return true;
                }
            }
        }

        return false;
    }

    int edmondsKarp(int s, int t) {
        int total_flow = 0;
        vector<int> parent(V);

        while (bfs(s, t, parent)) {
            int flow = INF;
            int v = t;

            while (v != s) {
                int u = parent[v];
                flow = min(flow, adj[u][v]);
                v = u;
            }

            v = t;
            while (v != s) {
                int u = parent[v];
                adj[u][v] -= flow;
                adj[v][u] += flow;
                v = u;
            }

            total_flow += flow;
        }
        return total_flow;
    }

    bool dfs(int s, int t, vector<int>& parent, vector<bool>& visited) {
        visited[s] = 1;

        if(s == t) return true;

        for(int v = 0; v < V; v++)
        {
            if(!visited[v] and adj[s][v])
            {
                parent[v] = s;
                if(dfs(v, t, parent, visited)) return true;
            }
        }
        return false;
    }

    int fordFulkerson(int s, int t) {
        int total_flow = 0;
        vector<int> parent(V, -1);
        vector<bool> visited(V, 0);

        while (dfs(s, t, parent, visited)) {
            int flow = INF;
            int v = t;

            while (v != s) {
                int u = parent[v];
                flow = min(flow, adj[u][v]);
                v = u;
            }

            v = t;
            while (v != s) {
                int u = parent[v];
                adj[u][v] -= flow;
                adj[v][u] += flow;
                v = u;
            }

            total_flow += flow;
        }
        return total_flow;
    }
   
    void display()
    {
        for(int i=0; i < V; i++)
        {
            for(int j = 0; j < V; j++)
            {
                cout<<adj[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

int main() 
{
    char type, alg;
    cout<<"Enter l for List, or m for Matrix"<<endl;
    cin>>type;
    cout<<"Enter e for Edmonds Karp, or f for Ford Fulkerson"<<endl;
    cin>>alg;

    int vertices = 6, source = 0, sink = 5;

    if(type == 'l')
    {
        GraphList l(vertices);
        
        l.addEdge(0, 1, 16);
        l.addEdge(0, 2, 13);
        l.addEdge(1, 2, 10);
        l.addEdge(1, 3, 12);
        l.addEdge(2, 1, 4);
        l.addEdge(2, 4, 14);
        l.addEdge(3, 2, 9);
        l.addEdge(3, 5, 20);
        l.addEdge(4, 3, 7);
        l.addEdge(4, 5, 4);
        l.display();

        if(alg == 'e') cout << "Max flow (List: Edmonds Karp) " << l.edmondsKarp(source, sink) << endl;
        else cout << "Max flow (List: Ford Fulkerson) " << l.fordFulkerson(source, sink) << endl;     
    }
    else
    {
        GraphMatrix m(vertices);
        m.addEdge(0, 1, 16);
        m.addEdge(0, 2, 13);
        m.addEdge(1, 2, 10);
        m.addEdge(1, 3, 12);
        m.addEdge(2, 1, 4);
        m.addEdge(2, 4, 14);
        m.addEdge(3, 2, 9);
        m.addEdge(3, 5, 20);
        m.addEdge(4, 3, 7);
        m.addEdge(4, 5, 4);
        m.display();
        if(alg == 'e') cout << "Max flow (Matrix: Edmonds Karp) " << m.edmondsKarp(source, sink) << endl;
        else cout << "Max flow (Matrix: Ford Fulkerson) " << m.fordFulkerson(source, sink) << endl;
    }


    return 0;
}
