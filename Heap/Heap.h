// author : ShivamBhalodia

#ifndef Heap_H  //if Heap.h hasn't been included yet
#define Heap_H  //#define it so the compiler knows it has been included and can prevent including it twice
#include<vector>
#define left_child(i) (2*i+1)
#define right_child(i) (2*i+2)
#define parent_node(i) ((i-1)/2)

template<class T>
class Heap
{
    public:
        
        //Construct empty heap of user defined priority(Max heap or Mean heap)
        Heap<T>(bool (*comp)(T a,T b));
        //Return the highest priority item currently in the heap.
        T top();
        //Insert an item in the Heap.
        void push(T a);
        //Deletes the highest priority item currently in the heap.
        void pop();
        //To check whether the Heap is empty or not
        bool isEmpty();
        
    private:
      
        bool (*compare)(T a,T b);
        std::vector<T>heap;
        void heapifyUpward(int idx);
        void heapifyDownward(int idx);
        
};

template<class T> 
Heap<T>::Heap(bool (*comp)(T a,T b))
{
    this->compare=comp;
}

template<class T> 
T Heap<T>::top()
{
    if(!isEmpty())
    {
    	return heap[0];
    }
}

template<class T> 
void Heap<T>::push(T a)
{
    heap.push_back(a);             //First insert new element at the end of the heap
    heapifyUpward(heap.size()-1);    //Then if heap is disturbed then fix it
}

template<class T> 
void Heap<T>::pop()
{
    if(!isEmpty())
    {
        std::swap(heap[0],heap[heap.size()-1]);           //First replace first element with the last element
        heap.pop_back();
        if(!isEmpty()) 
        heapifyDownward(0);            //Then if heap is disturbed then fix it
    }
}

template<class T> 
bool Heap<T>::isEmpty()
{
    return heap.empty();
}

template<class T> 
void Heap<T>::heapifyUpward(int idx)           //Fix heap in upward direction
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
void Heap<T>::heapifyDownward(int idx)         //Fix heap in downward direction
{
    int Idx=idx;
    int l=left_child(idx);
    int r=right_child(idx);
    if(l<heap.size())
    {
        if(compare(heap[Idx],heap[l]))
            Idx=l;
    }
    if(r<heap.size())
    {
        if(compare(heap[Idx],heap[r]))
            Idx=r;
    }

    if(Idx!=idx)
    {
       std::swap(heap[Idx],heap[idx]);
       heapifyDownward(Idx);
    }
}

#endif // Heap_H
