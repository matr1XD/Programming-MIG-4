#include <bits/stdc++.h> 
using namespace std; 
  
struct Edge 
{ 
    int flow, capacity; 
    int u, v; 
  
    Edge(int flow, int capacity, int u, int v) 
    { 
        this->flow = flow; 
        this->capacity = capacity; 
        this->u = u; 
        this->v = v; 
    } 
}; 
  
struct Vertex 
{ 
    int h, flow; 
  
    Vertex(int h, int flow) 
    { 
        this->h = h; 
        this->flow = flow; 
    } 
}; 
  
class Graph 
{ 
    int V;
    vector<Vertex> v; 
    vector<Edge> edge;   
public: 
    Graph(int V) 
    { 
        this->V = V; 
        for (int i = 0; i < V; i++) 
            v.push_back(Vertex(0, 0)); 
    } 
    
    void addEdge(int u, int v, int capacity) 
    { 
        edge.push_back(Edge(0, capacity, u, v)); 
    } 
    
    void preflow(int s) 
    { 
        v[s].h = v.size(); 
    
        for (int i = 0; i < edge.size(); i++) 
        { 
            if (edge[i].u == s) 
            { 
                edge[i].flow = edge[i].capacity; 
                v[edge[i].v].flow += edge[i].flow; 
                edge.push_back(Edge(-edge[i].flow, 0, edge[i].v, s)); 
            } 
        } 
    }

    int overFlowVertex(vector<Vertex>& v) 
    { 
        for (int i = 1; i < v.size() - 1; i++) 
        if (v[i].flow > 0) 
                return i; 
    
        return -1; 
    } 

    int getMaxFlow(int s, int t) 
    { 
        preflow(s); 
    
        while (overFlowVertex(v) != -1) 
        { 
            int u = overFlowVertex(v); 
            if (!push(u)) relabel(u); 
        } 

        return v.back().flow; 
    }
  
    void updateReverseEdgeFlow(int i, int flow) 
    { 
        int u = edge[i].v, v = edge[i].u; 
    
        for (int j = 0; j < edge.size(); j++) 
        { 
            if (edge[j].v == v && edge[j].u == u) 
            { 
                edge[j].flow -= flow; 
                return; 
            } 
        } 
    
        Edge e = Edge(0, flow, u, v); 
        edge.push_back(e); 
    } 
    
    bool push(int u) 
    { 
        for (int i = 0; i < edge.size(); i++) 
        { 
            if (edge[i].u == u) 
            { 
                
                if (edge[i].flow == edge[i].capacity) 
                    continue; 
    
                if (v[u].h > v[edge[i].v].h) 
                { 
                    int flow = min(edge[i].capacity - edge[i].flow, v[u].flow); 
    
                    v[u].flow -= flow; 
                    v[edge[i].v].flow += flow; 

                    edge[i].flow += flow; 
    
                    updateReverseEdgeFlow(i, flow); 
    
                    return true; 
                } 
            } 
        } 
        return false; 
    } 
    
    void relabel(int u) 
    { 
        int mh = INT_MAX; 
    
        for (int i = 0; i < edge.size(); i++) 
        { 
            if (edge[i].u == u) 
            { 
                if (edge[i].flow == edge[i].capacity) 
                    continue; 
    
                if (v[edge[i].v].h < mh) 
                { 
                    mh = v[edge[i].v].h; 
                    v[u].h = mh + 1; 
                } 
            } 
        } 
    } 
}; 
  
int main() 
{ 
    int V = 6; 
    Graph g(V); 
  
    g.addEdge(0, 1, 16); 
    g.addEdge(0, 2, 13); 
    g.addEdge(1, 2, 10); 
    g.addEdge(2, 1, 4); 
    g.addEdge(1, 3, 12); 
    g.addEdge(2, 4, 14); 
    g.addEdge(3, 2, 9); 
    g.addEdge(3, 5, 20); 
    g.addEdge(4, 3, 7); 
    g.addEdge(4, 5, 4); 
  
    int s = 0, t = 5; 
  
    cout << "Maximum flow is " << g.getMaxFlow(s, t); 
    return 0; 
} 
