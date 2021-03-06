# Singular connected graph

We can find strong connected components by using the algorithm of Kosaraju and Sharir.

## Algorithm

1. Create the reversed graph, by reversing each edge in the graph.
2. Use depth first search on the reversed graph, with post order numeration.
3. Use depth first search on the original graph, taking the vertex with the highest post order numeration first.

This algorithm results in a depth-first forest, where the trees are the strongly connected components.

## Example

In the code, a graph of 7 vertices is used as an example. You can view the graph in the picture below.

![Graph of 7 vertices][img1]

The strongly connected components in this graph are (0,1,2,3) and (4,5,6). This is because from vertex 2 you can go to vertex 4, but not the way around. They are however two weakly connected components.

[img1]: https://raw.githubusercontent.com/EMerckx/algorithms-ii/master/07-usages-depth-first-search/01-singular-connected-graph/graph.png
