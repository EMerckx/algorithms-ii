# B-trees

A B-tree is a tree of degree m
* m > 2
* every internal node has max m children
* every internal node has min ceil(m/2) children (exception: the root node)
* every leaf has the same level

A node in the B-tree has
* a variable that keeps the amount of keys in the node
* array with pointers to the children of the node (max size m)
* array for max m-1 keys (sorted in increasing order)
* array for max m-1 data values (maps the keys)
* logical value to indicate if the node is a leaf node