// author : ShivamBhalodia

#ifndef GRAPH_H    //if Graph.h hasn't been included yet
#define GRAPH_H    //#define it so the compiler knows it has been included and can prevent including it twice

#include<set>
#include<queue>
#include<vector>

using namespace std;

class Graph
{
    public:
      
        Graph(int n)       //constructor to construct empty graph with n nodes
        {
            nodes=n;
            graph=vector<vector<pair<int,int>>>(n+1);   //adjacency list for graph
        }
        
        virtual void addEdge(int a,int b,int weight)=0;   //pure virtual function to add an edge
        
        virtual bool isCycle()=0;   //pure virtual function to check whether the cycle is present or not
        
        vector<int>DFS(int source);   //DFS traversal
        
        vector<int>BFS(int source);   //BFS traversal
        
        vector<int>dijkstra(int source);  // Shortest path
        
        vector<vector<int>>floydWarshall();  //All pair shortest path
        
    	long long minimumSpanningTree(int source);   //Spanning tree
        
        vector<int>topoSort(int source);    
        
        int totalNodes()
        {
            return nodes;
        }
        
    protected:
      
        int nodes;
        vector<vector<pair<int,int>>>graph;   //graph is represented using adjacency list     
        //pair<vertex,weight>
        
        void dfsDone(int source,vector<bool>&vis,vector<int>&dfsOrder);
        void topoSortDone(int source,vector<bool>&vis,vector<int>&topoSortOrder);

};

vector<int>Graph::DFS(int source)
{
    vector<bool>vis(nodes+1,false);
    vector<int>dfsOrder;
    dfsDone(source,vis,dfsOrder);
    return dfsOrder;
}

void Graph::dfsDone(int source,vector<bool>&vis,vector<int>&dfsOrder)
{
    vis[source]=true;
    dfsOrder.push_back(source);

    for(pair<int,int>connected:graph[source])
    {
    	if(vis[connected.first]==false)
        {
            dfsDone(connected.first,vis,dfsOrder);
        }
    }
}

vector<int>Graph::BFS(int source)
{
    queue<int>q;
    vector<bool>vis(nodes+1,false);
    vector<int>bfsOrder;
    
    q.push(source);
    vis[source]=true;

    while(q.size())
    {
        int current=q.front();
        q.pop();
        bfsOrder.push_back(current);
        
        for(pair<int,int>connected:graph[current])
        {
            if(vis[connected.first]==false)
            {
                vis[connected.first]=true;
                q.push(connected.first);
            }
        }
    }
    return bfsOrder;
}

vector<int>Graph::dijkstra(int source)
{
    vector<bool>vis(nodes+1,false);
    vector<int>distance(nodes+1,1000000000);
    multiset<pair<int,int>>s;
    
    distance[source]=0;
    s.insert({0,source});
    
    while(s.size())
    {
        pair<int,int>current=*s.begin();
        s.erase(s.begin());
        
        int vertex=current.second;
        int weight=current.first;
        if(vis[vertex]==true)
        	continue;
        
        vis[vertex]=true;
        
        for(pair<int,int>connected:graph[vertex])
        {
            if(distance[vertex]+connected.second<distance[connected.first])
            {
            	distance[connected.first]=distance[vertex]+connected.second;
                s.insert({distance[connected.first],connected.first});
            }
        }
    }
    return distance;
}

vector<vector<int>>Graph::floydWarshall()
{
	vector<vector<int>>distance(nodes+1,vector<int>(nodes+1,1000000000));
	for(int i=1;i<=nodes;i++)
	{
		for(pair<int,int>connected:graph[i])
	    {
	        distance[i][connected.first]=connected.second;
	    }
	    distance[i][i]=0;
	}
	for(int k=1;k<=nodes;k++)  
   	{  
        	for(int i=1;i<=nodes;i++)  
        	{  
            		for(int j=1;j<=nodes;j++)  
            		{  
                		if(distance[i][k]+distance[k][j]<distance[i][j])  
                    		distance[i][j]=distance[i][k]+distance[k][j];  
            		}  
        	}  
    	}
	return distance;
}

long long Graph::minimumSpanningTree(int source)
{
	long long minimumCost=0;
	vector<bool>vis(nodes+1,false);
	multiset<pair<int,int>>s;
	s.insert({0,source});
	while(s.size())
	{
		pair<int,int>current=*s.begin();
        	s.erase(s.begin());
        
		int vertex=current.second;
		int weight=current.first;

		if(vis[vertex]==true)
			continue;

		minimumCost+=weight;
		vis[vertex]=true;

		for(pair<int,int>connected:graph[vertex])
		{
		    if(vis[connected.first]==false)
		    {
			s.insert({connected.second,connected.first});
		    }
		}
	}
	return minimumCost;
}

vector<int>Graph::topoSort(int source)
{
    vector<bool>vis(nodes+1,false);
    vector<int>topoSortOrder;
    topoSortDone(source,vis,topoSortOrder);
    reverse(topoSortOrder.begin(),topoSortOrder.end());
    return topoSortOrder;
}

void Graph::topoSortDone(int source,vector<bool>&vis,vector<int>&topoSortOrder)
{
    vis[source]=true;
    
    for(pair<int,int>connected:graph[source])
    {
        if(vis[connected.first]==false)
    	{
            topoSortDone(connected.first,vis,topoSortOrder);
        }
    }
    topoSortOrder.push_back(source);
}


#endif // GRAPH_H
