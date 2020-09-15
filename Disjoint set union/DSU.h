//author : ShivamBhalodia
#ifndef DSU_H   //if DSU.h hasn't been included yet
#define DSU_H //#define it so the compiler knows it has been included and can prevent including it twice
#include <vector>

class DSU
{
    public:
        //constructor that creats n different groups each with 1 element itself
        DSU(int n);
        
        //add a new group
        void newGroup();

    	//finds the parent of the group to which element belongs
        int Find(int a);
        
        //returns the number of elements in the group to which element belongs
        int groupSize(int a);

        //return true if element refers to a valid group
        bool isValidId(int a);
        
        //merge two groups to which element a and element b belong
        void Union(int a,int b);

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
  	noOfGroups=n;
    parents=std::vector<int>(n);
    sizee=std::vector<int>(n,1);   //initially size is 1
    for(int i=0;i<n;i++)
        parents[i]=i;    //initially make element to parent of itself
}

void DSU::newGroup()
{
   noOfGroups++;
   int a=parents.size();
   parents.push_back(a);
   sizee.push_back(1);
}

bool DSU::isValidId(int a)
{
    if(a>=0 && a<parents.size())
        return 1;
    return 0;
}

int DSU::Find(int a)
{
    if(!isValidId(a))
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
    if(!isValidId(a))
    	return -1;
    return sizee[Find(a)];
}

void DSU::Union(int a,int b)
{
    if((!isValidId(a)) || (!isValidId(b)))
        return;
    int group1=Find(a);
    int group2=Find(b);
    if(group1==group2)
        return;
    noOfGroups--;
    //append smaller group to bigger group
    if(sizee[group1]>=sizee[group2])     
    {
        parents[group2]=group1;
        sizee[group1]+=sizee[group2];
    }
    else
    {
        parents[group1]=group2;
        sizee[group2]+=sizee[group1];
    }
}

#endif //DSU_H
