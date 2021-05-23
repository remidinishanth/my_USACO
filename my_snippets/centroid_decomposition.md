# Centroid Decomposition

## Problem & Motivation

Given a tree, we are asked to find all the number of pairs `(u, v)` such that `dist(u, v) ≤ D`.

**Solution**

Let us fix one node of Tree by picking a vertex of the tree and call it `c`. Now let us split all the possible paths into classes: 
1) Some of the paths may not include this vertex `c`, then it will be completely inside one of the subtrees formed after removing `c`.
2) If the path includes node `c`, then we can break into two segments `u to c` and `c to v`.

![image](https://user-images.githubusercontent.com/19663316/119270576-ff1a0900-bc1a-11eb-9261-84c847174bf0.png)
![image](https://user-images.githubusercontent.com/19663316/119270572-f88b9180-bc1a-11eb-9c00-522ebc7ffb8e.png)
![image](https://user-images.githubusercontent.com/19663316/119270570-f0cbed00-bc1a-11eb-9657-fa2d98855f5f.png)




We can use Centroid decomposition technique to solve this problem. Centroid Decomposition is just a divide and conquer technique which is used on trees and turns out useful in many problems.

TODO - https://robert1003.github.io/2020/01/16/centroid-decomposition.html & https://github.com/miguelAlessandro/robert1003.github.io/blob/master/_posts/2020-01-16-centroid-decomposition.md

TODO - https://robert1003.github.io/tag/algorithm.html

TODO - https://iq.opengenus.org/centroid-decomposition-of-tree/

TODO - https://codeforces.com/blog/entry/52492?locale=en

Implementation: https://codeforces.com/contest/321/submission/3973635, https://codeforces.com/contest/321/submission/45791725, https://usaco.guide/plat/centroid?lang=cpp

![image](https://user-images.githubusercontent.com/19663316/119269663-6aada780-bc16-11eb-8d91-051c2db7fbe3.png)

![image](https://user-images.githubusercontent.com/19663316/119269676-81ec9500-bc16-11eb-9448-ab4e7968c6b9.png)
