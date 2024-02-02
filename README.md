# Bottom Up Red/Black Tree's
Simplifying Bottom Up Red/Black Trees

# What's here
On my blog I frequently discuss various topics related to red/black trees. Because There are
many variants of r/b trees I wanted to unify a simple recursive bottom up framework for implementing them.

```
    RedBlack.hpp - This has the RedBlackTree class, from which all variants are derived, it contains the methods for rotations
                   and color flips, insertion, and a virtual fixUp method meant to implement the balancing rules of the particular
                   variant.
    RedBlackNode.hpp - The node definition for red/black trees
    RedBlack234.hpp - "Traditional" bottom up 2-3-4 Tree based Red/Black Tree
    RedBlack23.hpp  - Parity Seeking 2-3 Tree based Red/Black Tree
    LLRedBlack23.hpp - "Left Leaning" 2-3 Tree based Red/Black Tree
    ValidateRedBlack.hpp - algorithms to verify a given tree is a valid 2-3 or 2-3-4 red/black BST.
```

These tree's are used along with my TreeDraw library to create images such as the following for my blog:
![3kinds](https://github.com/maxgoren/RedBlackTrees/assets/65133477/d4e36933-178c-4e93-8af5-028e5c35d70e)
which appear in articles describing the algorithms in this repo, such as http://www.maxgcoding.com/bottom-up-2-3-red-black-trees-let-your-red-nodes-lean-how-they-want/
