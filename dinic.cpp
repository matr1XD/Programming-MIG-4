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

class Graph
{
    int V; //Number of vertices
    vector<vector<Edge*>> adj; //Adjacency matrix
    vector<int> level; // Stored level of a vertex
    public:
    Graph(int V)
    {
        this->V = V;
        level.resize(V, 0);
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

    bool bfs(int s, int t) {
        for(int i = 0; i < V; i++) level[i] = -1;
        level[s] = 0; // Level of source (works as visited too)

        queue<int> q; // (vertex, flow)
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for(Edge * edge : adj[u]) {
                if (level[edge->v] < 0 && edge->flow < edge->capacity and edge->v != s) {
                    level[edge->v] = level[u] + 1; // Level of current vertex is level of parent + 1
                    q.push(edge->v);
                }
            }
        }
        
        // If we cant reach to sink we return false, else true
        if(level[t] < 0) return false;
        return true;
    }

    // dfs function after bfs has figured out a possible flow and constructed levels
    int sendFlow(int u, int flow, int t, vector<int> start)
    {
        // start[] to keep track of next edge to be explored
        // start[i] stores count of edges explored from i
        // u is current vertex
        if(u == t) return flow; // Sink reached

        while(start[u] < adj[u].size())
        {
            // Pick next edge from ajdacency list of u
            for(int i = 0; i < V; i++)
            {
                Edge * edge = adj[u][start[u]];

                if(level[edge->v] == level[u] + 1 and edge->flow < edge->capacity)
                {
                    int cur_flow = min(flow, edge->capacity - edge->flow);
                    int temp = sendFlow(edge->v, cur_flow, t, start);

                    if(temp > 0)
                    {
                        edge->flow += temp;
                        edge->reverse->flow -= temp;
                        return temp;
                    }
                }
            }
            start[u]++;
        }
            
        return 0;
    }

    int dinic(int s, int t)
    {
        if(s == t) return -1;
        int total_flow = 0;

        // While there is a path from s to t
        while(bfs(s, t))
        {
            vector<int> start(V+1, 0); // Store how many edges are visited
            int flow;
            // While flow is not zero, add the flow to total 
            while(sendFlow(s, INF, t, start)) total_flow += sendFlow(s, INF, t, start);
        }

        return total_flow;
    }
};

int main() 
{
    int vertices = 6, source = 0, sink = 5;

        Graph m(vertices);
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
        cout<<"Max flow (Matrix: Dinic) " << m.dinic(source, sink) << endl;

    return 0;
}
