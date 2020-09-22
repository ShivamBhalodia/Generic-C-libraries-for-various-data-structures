// author : ShivamBhalodia

#ifndef UNDIRECTEDGRAPH_H    //if UndirectedGraph.h hasn't been included yet
#define UNDIRECTEDGRAPH_H    //#define it so the compiler knows it has been included and can prevent including it twice
#include "Graph.h"

using namespace std;

class UndirectedGraph:public Graph
{    
    public:
      
        UndirectedGraph(int nodes):Graph(nodes)
        { }
        
        void addEdge(int a,int b,int weight);

        bool isCycle();
        
    private:
    
        void findCycle(int src,vector<int>&parent,vector<bool>&vis,bool &cycle);
        
};

void UndirectedGraph::addEdge(int a,int b,int weight=1)
{
    graph[a].push_back({b,weight});
    graph[b].push_back({a,weight});
}

bool UndirectedGraph::isCycle()
{
    if(nodes<=1)
        return false;
        
    bool cycle=false;
    vector<bool>vis(nodes+1,false);
    vector<int>parent(nodes+1,false);
    parent[1]=-1;
    findCycle(1,parent,vis,cycle);
    return cycle;
}

void UndirectedGraph::findCycle(int source,vector<int>&parent,vector<bool>&vis,bool &cycle)
{
    if(cycle)
        return;
        
    vis[source]=true;
    for(pair<int,int>connected:graph[source])
    {
        if(vis[connected.first] && parent[source]!=connected.first)
        {
            cycle=true;
            return;
        }
        else if(vis[connected.first]==false)
        {
            parent[connected.first]=source;
            findCycle(connected.first,parent,vis,cycle);
        }
    }
}

#endif // UNDIRECTEDGRAPH_H
