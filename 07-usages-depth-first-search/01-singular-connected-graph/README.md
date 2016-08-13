# Singular connected graph

We can find strong connected components by using the algorithm of Kosaraju and Sharir.

# Algorithm

1. Create the reversed graph, by reversing each edge in the graph.
2. Use depth first search on the reversed graph, with post order numeration.
3. Use depth first search on the original graph, taking the vertex with the highest post order numeration first.

This algorithm results in a depth-first forest, where the trees are the strongly connected components.