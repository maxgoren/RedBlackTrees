# Red/Black Tree's
Exploring the many types of Red/Black Trees

# What's here
On my blog I frequently discuss various topics related to red/black trees. Because there are
many variants of r/b trees I wanted to unify a simple recursive bottom up framework for implementing them.
I have also begun exploring varioud top down variants as well.

```
    RedBlackNode.hpp - The node definition for red/black trees
    ValidateRedBlack.hpp - algorithms to verify a given tree is a valid red/black BST, with algorithms for 2-3, 2-3-4, and 2-3-4-5 red/black trees.
Bottom up algorithms:
    RedBlack.hpp - This has the RedBlackTree class, from which all variants are derived, it contains the methods for rotations
                   and color flips, insertion, and a virtual fixUp method meant to implement the balancing rules of the particular
                   variant.
    RedBlack234.hpp - "Traditional" bottom up 2-3-4 Tree based Red/Black Tree
    RedBlack23.hpp  - Parity Seeking 2-3 Tree based Red/Black Tree
    LLRedBlack23.hpp - "Left Leaning" 2-3 Tree based Red/Black Tree
Top down algorithms:
   TDRedBlack234.hpp - Top down 2-3-4 red/black tree's as described in sedgewick & guibas's orginal 1978 paper
   TDRedBlack2345.hpp - Another top down variant from the above mentioned paper, uses only single rotations and implements 2-3-4-5 trees.
```

These tree's are used along with my TreeDraw library to create images such as the following for my blog:
![3kinds](https://github.com/maxgoren/RedBlackTrees/assets/65133477/d4e36933-178c-4e93-8af5-028e5c35d70e)
<img width="861" alt="td-234-vs-td-2345" src="https://github.com/maxgoren/RedBlackTrees/assets/65133477/ceb3a645-08ca-4f61-b345-30e55dea5a68">

which appear in articles describing the algorithms in this repo, such as:

http://www.maxgcoding.com/bottom-up-2-3-red-black-trees-let-your-red-nodes-lean-how-they-want/

http://www.maxgcoding.com/bottom-up-red-black-trees/

http://www.maxgcoding.com/validating-red-black-trees/

http://www.maxgcoding.com/top-down-2-3-4-5-trees-the-red-black-tree-time-forgot/
