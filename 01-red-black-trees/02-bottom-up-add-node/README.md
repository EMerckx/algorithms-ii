# Bottom up - add node

## In short

2 steps:
* Add the node as a leaf, without any color 
* Repair the red-black tree, starting from the bottom

Note that we go to the bottom of the tree and afterwards, we go back up. 

We require pointers to parents or a stack for this method.