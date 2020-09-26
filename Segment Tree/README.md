# Segment Tree
C++ library for Segment Tree.

# How to use
1)include "SegTree.h" in your .cpp(source) file.
2)Construct tree by specifying as below:<br>
   I).   The datatype for which the tree is being constructed.<br>
   II).  Vector of data<br>
   III). Identity value for extra nodes<br>
   IV).  Combine function that specifies how the result of left and right child of a node<br> 
         should be used to generate the value of current node.
3)int sum(int x,int y)<br>
  {<br>
      return x+y;<br>
  }<br>  
  SegmentTree<int> rangeSumQueries(data,0,sum);<br>
   
   
# Options
1)Build Tree<br>
2)Query Tree<br>
3)Update Tree(point)

