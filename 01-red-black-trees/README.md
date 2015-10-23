# Red-black trees

The root node must be a black node.

A red node can't have a red node as a child.

Black height constraint: from any node in the tree to a leaf node, 
you need to have the same amount of black nodes. 
This in every path, starting from that node.

Rotation constraint: the inorder order must be kept, 
because otherwise we get a violation to the searchtree constraint