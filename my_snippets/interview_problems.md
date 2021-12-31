### Morris Traversal - InOrder Traversal without stack

Morris Traversal method traverses the binary tree (non-recursive, no stack, O(1) space)

* To use O(1) space for traversal, the biggest difficulty lies in how to return to the parent node when traversing to the child node (assuming there is no p pointer to the parent node in the node), because the stack cannot be used as an auxiliary space.

* To solve this problem, Morris method uses a threaded binary concept (threaded binary tree) of.
* In the Morris method, there is no need to allocate additional pointers to each node to point to its predecessor and successor, just use the left and right null pointers in the leaf node to point to the predecessor or successor node under a certain order of traversal.

![](images/morris_traversal.png)


Execution order left to right

![image](https://user-images.githubusercontent.com/19663316/147833861-9c3af599-c162-44cb-b752-5918b6142f4b.png)
