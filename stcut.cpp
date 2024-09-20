#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

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

    void dfsmincut(vector<vector<int>> residual, int s, vector<bool>& visited) // To find all reachable vertices from s
    {
        visited[s] = 1; // visited[i] is true is i is reachable from s
        for(int i = 0; i < V; i++)
        {
            if(residual[s][i] and !visited[i]) dfsmincut(residual, i, visited);
        }
    }

    int fordFulkerson(int s, int t) {
        int total_flow = 0;
        vector<int> parent(V, -1);

        while (true) {
            vector<bool> visited(V, 0);
            if(!dfs(s, t, parent, visited)) break;
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

    void mincut(int s, int t)
    {
        vector<vector<int>> temp(V, vector<int>(V));
        for(int i = 0; i < V; i++)
            for(int j = 0; j < V; j++)
                temp[i][j] = adj[i][j]; // Stores the capacity between vertices bc adj will be changed in the future

        int flow = fordFulkerson(s, t); // Finds the maximum flow and changes the adj matrix to residual matrix

        vector<bool> visited(V,0);
        dfsmincut(adj, s, visited); // Finds paths in residual matrix

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (visited[i] && !visited[j] && temp[i][j] > 0) // An edge that must be cut crosses from a visited vertex to unvisted one and has a positive capacity in temp (not residual)
                    cout << i << " - " << j << endl;
            }
        }
    }
};

int main() 
{
    int vertices = 6, source = 0, sink = 5;    
        GraphMatrix m1(vertices);
        m1.addEdge(0, 1, 16);
        m1.addEdge(0, 2, 8);
        m1.addEdge(1, 2, 5);
        m1.addEdge(1, 3, 10);
        m1.addEdge(2, 4, 7);
        m1.addEdge(3, 5, 9);
        m1.addEdge(3, 4, 4);
        m1.addEdge(4, 5, 12);
        
        cout<<"Min-cut edges on first graph: "<<endl;
        m1.mincut(source, sink);

        GraphMatrix m2(vertices);
        m2.addEdge(0, 1, 9);
        m2.addEdge(0, 2, 8);
        m2.addEdge(1, 4, 4);
        m2.addEdge(1, 3, 4);
        m2.addEdge(2, 1, 2);
        m2.addEdge(2, 4, 5);
        m2.addEdge(2, 5, 3);
        m2.addEdge(3, 5, 5);
        m2.addEdge(4, 5, 6);

        cout<<"Min-cut edges on second graph: "<<endl;
        m2.mincut(source, sink);
    return 0;
}
