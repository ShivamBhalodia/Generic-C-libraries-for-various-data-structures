// author : ShivamBhalodia
#ifndef SEGTREE_H  //if SegTree.h hasn't been included yet
#define SEGTREE_H  //#define it so the compiler knows it has been included and can prevent including it twice

#include <vector>
#define left_child(i) (2*i+1)
#define right_child(i) (2*i+2)
#define parent_node(i) ((i-1)/2)

using namespace std;

template<class T>
class SegTree
{
    public:
      
        //SegTree constructor.
        SegTree(vector<T>data,T value,T(*combine)(T a,T b));
        
        //0 based array indexing.
        T query(int l,int r);
        
        //point update
        void update(int ind,T val);
        
    private:
    	
        
        T *tree;
    	vector<T>data;
    	int n;
        int segTreeSize;
        T dummyNodeValue;          //Identity value for extra nodes
        
        
        int sizeOfSegTree();
        void buildTree(int si,int ss,int se);
        T (*combine)(T a, T b);
        T queryDone(int si,int ss,int se,int qs,int qe);
        void updateDone(int si,int ss,int se,int ind);
};

template<class T> 
SegTree<T>::SegTree(vector<T>data,T value,T (*combine)(T a,T b))
{
	n=data.size();
	dummyNodeValue=value;
  	segTreeSize=sizeOfSegTree();
    this->data=data;
    this->combine=combine;
    tree=new T[segTreeSize];
    int ss=0,se=n-1;
    buildTree(0,ss,se);
}

template<class T> 
int SegTree<T>::sizeOfSegTree()
{
  
	/*
	If n is a power of 2, then there are no dummy nodes. 
	So the size of the segment tree is 2n-1(n leaf nodes and n-1 internal nodes). 
	If n is not a power of 2,
	then the size of the tree will be 2*x–1(x is the smallest power of 2 greater than n)
	*/
  
  	int powOf2=1;
    while(powOf2<n)
    {
        powOf2=powOf2<<1;
    }
    return 2*powOf2-1;
}

template<class T> 
void SegTree<T>::buildTree(int si,int ss,int se)
{
  	if(ss==se)
  	{
    	tree[si]=data[ss];
    	return;
  	}
  	int mid=ss+((se-ss)/2);
  	buildTree(left_child(si),ss,mid);
  	buildTree(right_child(si),mid+1,se);
  	tree[si]=combine(tree[left_child(si)],tree[right_child(si)]);

}

template<class T> 
T SegTree<T>::query(int l,int r)
{
    int ss=0,se=n-1;
    return queryDone(0,ss,se,l,r);
}

template<class T> 
T SegTree<T>::queryDone(int si,int ss,int se,int qs,int qe)
{
	if(qs>se || qe<ss || qs>qe)
		return dummyNodeValue;
	if(ss>=qs && se<=qe)
		return tree[si];
	int mid=ss+((se-ss)/2);
	T left=queryDone(left_child(si),ss,mid,qs,qe);
	T right=queryDone(right_child(si),mid+1,se,qs,qe);
	return combine(left,right);
}

template<class T> 
void SegTree<T>::update(int ind,T val)
{
    data[ind]=val;
    int ss=0,se=n-1;
    updateDone(0,ss,se,ind);
}

template<class T> 
void SegTree<T>::updateDone(int si,int ss,int se,int ind)
{
	if(ss==se)
  	{
    	tree[si]=data[ss];
    	return;
  	}
  	int mid=ss+((se-ss)/2);
  	if(ind<=mid)
  	updateDone(left_child(si),ss,mid,ind);
  	else
  	updateDone(right_child(si),mid+1,se,ind);
  	tree[si]=combine(tree[left_child(si)],tree[right_child(si)]);	
}

#endif // SEGTREE
