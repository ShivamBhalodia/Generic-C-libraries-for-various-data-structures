# Segment Tree
C++ library for Segment Tree.

# How to use
1)include "SegTree.h" in your .cpp(source) file.
2)Construct tree by specifying as below:<br>
   ->The datatype for which the tree is being constructed.<br>
   ->Vector of data<br>
   ->Identity value for extra nodes<br>
   ->Combine function that specifies how the result of left and right child of a node<br> 
     should be used to generate the value of current node.<br>
     
3)int sum(int x,int y)<br>
  { return x+y ; }<br> 
  SegTree < int > rangeSumQueries(data,0,sum);<br>
   
   
# Options
1)Build Tree<br>
2)Query Tree<br>
3)Update Tree(point)

