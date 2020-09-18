//author : ShivamBhalodia

#ifndef DSU_H   //if DSU.h hasn't been included yet
#define DSU_H //#define it so the compiler knows it has been included and can prevent including it twice
#include <vector>

class DSU
{
    public:
      
        //constructor that creats n different groups each with 1 element itself
        DSU(int n);
        
        //find the parent of the group to which element belongs
        int findParent(int a);
        
        //returns the number of elements in the group to which element belongs
        int groupSize(int a);

        //return true if element refers to a valid group
        bool isValidGroup(int a);
        
        //Check whether element a and element b belongs to same group or not
        bool inSameGroup(int a,int b);
        
        //merge two groups to which element a and element b belong
        void Union(int a,int b);
        
        //add a new group
        void newGroup();

        //returns number of groups
        int getnoOfGroups()
        {
            return noOfGroups;
        }
        
    private:
        int noOfGroups;
        std::vector<int>parents;
        std::vector<int>sizee;
};

DSU::DSU(int n)
{
    parents=std::vector<int>(n);
    sizee=std::vector<int>(n,1);   //initially size is 1
    for(int i=0;i<n;i++)
        parents[i]=i;    //initially make element to parent of itself
    noOfGroups=n;
}

int DSU::findParent(int a)
{
    if(!isValidGroup(a))
        return -1;
    
    while(parents[a]!=a)
    {
        parents[a]=parents[parents[a]];
        a=parents[a];
    }
    return a;
   
}

int DSU::groupSize(int a)
{
    if(!isValidGroup(a))
      	return -1;
    return sizee[findParent(a)];
}

bool DSU::isValidGroup(int a)
{
    if(a>=0 && a<parents.size())
        return true;
    return false;
}

bool DSU::inSameGroup(int a,int b)
{
    if(findParent(a)==findParent(b)) 
      	return true;
    return false;
}

void DSU::Union(int a,int b)
{
    if((!isValidGroup(a)) || (!isValidGroup(b)))
        return;
        
    if(inSameGroup(a,b))
        return;
        
    int parent_a=findParent(a);
    int parent_b=findParent(b);
    
    noOfGroups--;
    //append smaller group to bigger group
    if(sizee[parent_a]>=sizee[parent_b])     
    {
        parents[parent_b]=parent_a;
        sizee[parent_a]+=sizee[parent_b];
    }
    else
    {
        parents[parent_a]=parent_b;
        sizee[parent_b]+=sizee[parent_a];
    }
}

void DSU::newGroup()
{
	int a=parents.size();
	parents.push_back(a);
	sizee.push_back(1);
	noOfGroups++;
}


#endif //DSU_H
