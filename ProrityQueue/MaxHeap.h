// author : ShivamBhalodia

#ifndef MAXHEAP_H  //if MaxHeap.h hasn't been included yet
#define MAXHEAP_H  //#define it so the compiler knows it has been included and can prevent including it twice
#include<vector>
#define left_child(i) (2*i+1)
#define right_child(i) (2*i+2)
#define parent_node(i) ((i-1)/2)

template<class T>
class MaxHeap
{
    public:
        
        //Construct empty heap of user defined priority
        MaxHeap<T>(bool (*comp)(T a,T b));
        //return the highest priority item currently in the Max Heap.
        T top();
        //Insert an item in the Max Heap.
        void push(T a);
        //deletes the highest priority item currently in the Max Heap.
        void pop();
        //To check whether the Max Heap is empty or not
        bool isEmpty();
        
    private:
      
        //return true if obj1 compares less than obj2
        bool (*compare)(T a,T b);
        std::vector<T>heap;
        void heapifyUpward(int idx);
        void heapifyDownward(int idx);
        
};

template<class T> 
MaxHeap<T>::MaxHeap(bool (*comp)(T a,T b))
{
    this->compare=comp;
}

template<class T> 
T MaxHeap<T>::top()
{
    if(!isEmpty())
    {
      return heap[0];
    }
}

template<class T> 
void MaxHeap<T>::push(T a)
{
    heap.push_back(a);             //First insert new element at the end of the Max heap
    heapifyUpward(heap.size()-1);    //Then if Max heap is disturbed then fix it
}

template<class T> 
void MaxHeap<T>::pop()
{
    if(!isEmpty())
    {
      	std::swap(heap[0],heap[heap.size()-1]);           ////First replace first element with the last element
        heap.pop_back();
        if(!isEmpty()) 
       	heapifyDownward(0);            //Then if Max heap is disturbed then fix it
    }
}

template<class T> 
bool MaxHeap<T>::isEmpty()
{
    return heap.empty();
}

template<class T> 
void MaxHeap<T>::heapifyUpward(int idx)           //Fix Max heap in upward direction
{
    int p=parent_node(idx);
    if(p<0)
        return;
    if(compare(heap[p],heap[idx]))
    {
        std::swap(heap[p],heap[idx]);
        heapifyUpward(p);
    }
}

template<class T> 
void MaxHeap<T>::heapifyDownward(int idx)         //Fix Max heap in downward direction
{
    int largeIdx=idx;
    int l=left_child(idx);
    int r=right_child(idx);
    if(l<heap.size())
    {
        if(compare(heap[largeIdx],heap[l]))
            largeIdx=l;
    }
    if(r<heap.size())
    {
        if(compare(heap[largeIdx],heap[r]))
            largeIdx=r;
    }

    if(largeIdx!=idx)
    {
       std::swap(heap[largeIdx],heap[idx]);
       heapifyDownward(largeIdx);
    }
}

#endif // MAXHEAP_H
