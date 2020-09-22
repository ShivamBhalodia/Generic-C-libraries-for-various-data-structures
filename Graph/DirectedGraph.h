// author : ShivamBhalodia

#ifndef DIRECTEDGRAPH_H   //if DirectedGraph.h hasn't been included yet
#define DIRECTEDGRAPH_H   //#define it so the compiler knows it has been included and can prevent including it twice

#include <stack>
#include "Graph.h"

using namespace std;

class DirectedGraph:public Graph
{
    public:
      
        DirectedGraph(int nodes):Graph(nodes)
        { }
        
        void addEdge(int a,int b,int weight);

        bool isCycle();

        vector<vector<int>>getSCC();  //SCC->StronglyConnectedComponents
    
    private:
        
        vector<int>findOrder();
        bool findCycle(int source,vector<bool>&vis,vector<bool>&currentPath);
        void orderDone(int source,vector<bool>&vis,vector<int>&order);
        DirectedGraph doReversal();
};

void DirectedGraph::addEdge(int a,int b,int weight=1)
{
    graph[a].push_back({b,weight});
}

bool DirectedGraph::isCycle()
{
    if(nodes<=1)
      return false;
      
    vector<bool>vis(nodes+1,false);
    vector<bool>currentPath(nodes+1,false);
    
    for(int i=1;i<=nodes;i++) 
    {
        if(findCycle(i,vis,currentPath)) 
            return true;  
    }
    return false;
}

bool DirectedGraph::findCycle(int source,vector<bool>&vis,vector<bool>&currentPath) 
{ 
    if(vis[source]==false) 
    { 
        vis[source]=true; 
        currentPath[source]=true; 

        for(pair<int,int>connected:graph[source])
        {
            if(vis[connected.first]==false && findCycle(connected.first,vis,currentPath)) 
                return true; 
            else if(currentPath[connected.first]==true) 
                return true;
        }
    
    } 
    currentPath[source]=false; 
    return false; 
}

vector<vector<int>>DirectedGraph::getSCC()
{
    vector<bool>vis(nodes+1,false);
    vector<vector<int>>stronglyConnectedComponent;
    vector<int>order=findOrder();
    DirectedGraph reversedGraph=doReversal();

    for(int i=order.size()-1;i>=0;i--)
    {
        vector<int>SCC;
	    if(vis[order[i]]==false)
	    {
	        reversedGraph.dfsDone(order[i],vis,SCC);
	        stronglyConnectedComponent.push_back(SCC);
	    }
    }
    return stronglyConnectedComponent;
}

vector<int>DirectedGraph::findOrder()
{
    vector<bool>vis(nodes+1,false);
    vector<int>order;
    
    for(int i=1;i<=nodes;i++)
    {
        if(vis[i]==false)
        {
            orderDone(i,vis,order);
        }
    }
    return order;
}


void DirectedGraph::orderDone(int source,vector<bool>&vis,vector<int>&order)
{
    vis[source]=1;
    for(pair<int,int>connected:graph[source])
    {
        if(vis[connected.first]==false)
            orderDone(connected.first,vis,order);
    }
    order.push_back(source);
}

DirectedGraph DirectedGraph::doReversal()
{
    DirectedGraph newGraph(nodes);

    for(int i=1;i<=nodes;i++)
    {
        for(pair<int,int>connected:graph[i])
        {
            newGraph.addEdge(connected.first,i);
        }
    }
    return newGraph;
}

#endif // DIRECTEDGRAPH_H
