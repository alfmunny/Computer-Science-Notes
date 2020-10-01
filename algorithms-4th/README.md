# Notes on Algorithms 4th

[The book](https://www.amazon.de/-/en/Robert-Sedgewick/dp/032157351X/ref=sr_1_6?dchild=1&keywords=algorithms+4th&qid=1601583080&sr=8-6)

Online Content:
- [Algorithm, 4th Edition](https://algs4.cs.princeton.edu/home/)
- Algorithms Part 1: [Video on Coursera](https://www.coursera.org/learn/algorithms-part1)
- Algorithms Part 2: [Video on Coursera](https://www.coursera.org/learn/algorithms-part2)

Preparations:

- How to set up a java environment?

    [Mac OS](https://lift.cs.princeton.edu/java/mac/), [Windows](https://lift.cs.princeton.edu/java/windows/)

- How to approach?

1. Watch the videos before you dive into each chapter.
2. Browse the chapter in book and read the code.
3. Learning by doing, understand it, implement the code once yourself, and run for tests.
4. If you encounter problems, please refer to the codes presented [online](https://algs4.cs.princeton.edu/code/).
5. Pick some problems from exercises and solve them. The solutions can be found [online](https://algs4.cs.princeton.edu/code/) as well.
6. Practice until you get it.

We will skip the first chapter (Fundamentals) for now. You can also go through it quickly yourself. 
Those are basic knowledge of java programming.
We assume you have already known most of it. A quick recap should help.

## Table of Contents

1. [Foundamentals](1-Foundamentals.md), [code](algs4/foundamentals)
2. [Sorting](2-Sorting.md), [code](algs4/sorting)
3. [Searching](3-Searching.md), [code](algs4/searching)
4. [Graphs](4-Graphs.md), [code](algs4/graphs)
5. [Strings](5-Strings.md), [code](algs4/strings)
6. [Context](6-Context.md)

## Learning Progress (20/21)

Start date: 12.May.2020

End date: 5.July.2020

7 Weeks

[Week 0: Foundamentals](#Week-0)

- [X] Stacks and Queues
- [ ] Union-Find

[Week 1: Sorting](#Week-1)

- [X] Elementary Sorts
- [X] Merge Sort
- [X] Quick Sort
- [X] Priority Queues

[Week 2: Searching](#Week-2)

- [ ] ~Symbol Tables~
- [X] Binary Search
- [X] Balanced Search Trees
- [X] Hash Tables (Implementation missed)

[Week 3: Graphs](#Week-3)

- [X] Undirected Graphs (DFS, BFS)
- [X] Directed Graphs

[Week 4: Graphs](#Week-4)

- [X] Minimum Spanning Trees (Kruskal's, Prim's)
- [X] Shortest Paths (Djikstra's, Bellman-Ford's)

[Week 5: Strings](#Week-5)

- [X] String sorts
- [X] Tries
 
[Week 6: Strings](#Week-6)

- [X] Substring Search
- [X] Regular Expressions

[Week 7: Context](#Week-7)

Strings
- [X] Data Compression (Huffman Compression and LZW Compression)

Context 
- [X] Reductions
- [X] Linear Programming
- [X] Intractability (P vs. NP, NP-Completeness)

## Week 0

Stack and Queue

1. [Videos](https://www.coursera.org/lecture/algorithms-part1/stacks-jSxyD)
2. Implement Stack and Queue

Union Find

1. [Videos](https://www.coursera.org/lecture/algorithms-part1/dynamic-connectivity-fjxHC)
2. Implement Union-Find

## Week 1

### Monday 

Elementary Sorts
1. [Video content](https://www.coursera.org/learn/algorithms-part1/lecture/JHpgy/sorting-introduction)
2. Read the code

### Tuesday

Elementary Sort: 
1. Implement
2. Exercise

### Wednesday

Merge Sort

1. [Video content](https://www.coursera.org/lecture/algorithms-part1/mergesort-ARWDq)
2. Read the code
3. Implement

### Thursday

Quick Sort

1. [Video content](https://www.coursera.org/lecture/algorithms-part1/quicksort-vjvnC)
2. Read the code
3. Implement

### Friday

Priority Queues

1. [Video content](https://www.coursera.org/lecture/algorithms-part1/binary-heaps-Uzwy6)
2. Read the code

### Saturday

Priority Queues

1. Implement
2. Exercise

## Week 2

### Monday

Binary Tree 

1. [Video content](https://www.coursera.org/lecture/algorithms-part1/symbol-table-api-7WFvG)
2. Read the code and Implement

### Tuesday

Binary Tree 

1. Implement it

Additional content: [MIT: Binary Search Trees, BST sort](https://www.youtube.com/watch?v=9Jry5-82I68&list=PLUl4u3cNGP61Oq3tWYp6V_F-5jb5L2iHb&index=5)

### Wednesday

2-3 Search Trees

1. [Video content](https://www.coursera.org/lecture/algorithms-part1/2-3-search-trees-wIUNW)
2. Read the code

### Thursday

Red-Black BST
1. [Video Content](https://www.coursera.org/lecture/algorithms-part1/red-black-bsts-GZe13)
2. (optional) Implement Red-Black BST
3. (optional) B-Trees [Video content](https://www.coursera.org/lecture/algorithms-part1/b-trees-optional-HIlHd)

Additional content [MIT AVL Trees](https://www.youtube.com/watch?v=FNeL18KsWPc&list=PLUl4u3cNGP61Oq3tWYp6V_F-5jb5L2iHb&index=7&t=155s)

### Friday

Hash Table

1. [Video content](https://www.coursera.org/lecture/algorithms-part1/hash-tables-CMLqa)
2. Read

Additional content [MIT: Hashing with Chaining](https://www.youtube.com/watch?v=0M_kIqhwbFo&list=PLUl4u3cNGP61Oq3tWYp6V_F-5jb5L2iHb&index=8)

### Saturday

1. Implement the Separate Chaining Hash Table

Additional content [MIT: Open Addressing, Cryptographic Hashing](https://www.youtube.com/watch?v=rvdJDijO2Ro&list=PLUl4u3cNGP61Oq3tWYp6V_F-5jb5L2iHb&index=10)

Optional: [Symbol Table Applications](https://www.coursera.org/lecture/algorithms-part1/symbol-table-applications-sets-optional-ewcSx)

Summary

## Week 3

### Monday

Undirected Graph

1. [Introduction to Graphs](https://www.coursera.org/lecture/algorithms-part2/introduction-to-graphs-dKTI4)
2. [Graph API](https://www.coursera.org/lecture/algorithms-part2/graph-api-4ZE6G)
3. [Depth-First Search](https://www.coursera.org/lecture/algorithms-part2/depth-first-search-mW9aG)

### Tuesday

Undirected Graph

1. Implement Undirected Graph and DFS

### Wednesday

Undirected Graph
1. [Breadth-First Search](https://www.coursera.org/lecture/algorithms-part2/breadth-first-search-DjaET)
2. [Connected Components](https://www.coursera.org/lecture/algorithms-part2/connected-components-Dzl65)
3. (optional)[Graph Challenges](https://www.coursera.org/lecture/algorithms-part2/graph-challenges-6kk3F)
4. Implement BFS

### Thursday

Directed Graph

1. [Digraph Search](https://www.coursera.org/lecture/algorithms-part2/introduction-to-digraphs-QKBnh)
2. Implement digraph search

### Friday

Directed Graph

1. [Topological Sort](https://www.coursera.org/lecture/algorithms-part2/topological-sort-RAMNS)
2. Implement sort

### Saturday

Directed Graph

1. [Strong Components](https://www.coursera.org/lecture/algorithms-part2/strong-components-fC5Yw)
2. Implement strong components

## Week 4

### Monday - Wednesday

Minimum Spanning Trees

1. Introduction to MSTs [Video](https://www.coursera.org/lecture/algorithms-part2/introduction-to-msts-lEPxc)
2. Prim's Algorithm [Video](https://www.coursera.org/lecture/algorithms-part2/prims-algorithm-HoHKu)
3. Kruskal's Algorithm [Video](https://www.coursera.org/lecture/algorithms-part2/kruskals-algorithm-KMCRd)
4. Implementation for Prim's and Kruskal's Algorithms

### Thursday - Saturday

1. Shortest Path [Video](https://www.coursera.org/lecture/algorithms-part2/shortest-paths-apis-e3UfD)
1. Single Source Shortest Path: Djikstra Algorithm [Video](https://www.coursera.org/lecture/algorithms-part2/dijkstras-algorithm-2e9Ic)
2. Negative Weighted Digraph: Bellman-Ford Algorithm [Video](https://www.coursera.org/lecture/algorithms-part2/negative-weights-PKCKQ)
3. Maxflow [Video](https://www.coursera.org/lecture/algorithms-part2/introduction-to-maxflow-jZVUm)
3. Implementation for for Djikstra and Bellman-Ford Algorithms

## Week 5

### Monday - Wednesday

Strings Sorts

1. Strings in Java [Video](https://www.coursera.org/lecture/algorithms-part2/strings-in-java-vGHvb)
2. Radix Sort [Video](https://www.coursera.org/lecture/algorithms-part2/key-indexed-counting-2pi1Z)
3. Suffix Array [Video](https://www.coursera.org/lecture/algorithms-part2/suffix-arrays-TH18W)
4. Implement Radix Sort 

### Thursday - Saturday

Tries

1. R-Way Tries [Video](https://www.coursera.org/lecture/algorithms-part2/r-way-tries-CPVdr)
2. Ternary Search Tries [Video](https://www.coursera.org/lecture/algorithms-part2/ternary-search-tries-yQM8K)
3. Implement Tries

## Week 6

### Monday - Wednesday

Substring Search

1. Introduction [Video](https://www.coursera.org/lecture/algorithms-part2/introduction-to-substring-search-n3ZpG)
2. Knuth-Morris-Pratt [Video](https://www.coursera.org/learn/algorithms-part2/lecture/TAtDr/knuth-morris-pratt)
3. Boyer-Moore [Video](https://www.coursera.org/lecture/algorithms-part2/boyer-moore-CYxOT)
4. Rabin-Karp [Video](https://www.coursera.org/lecture/algorithms-part2/rabin-karp-3KiqT)
5. Implement KMP

### Thursday

Regular Expressions

1. Regular Expressions [Video](https://www.coursera.org/learn/algorithms-part2/lecture/go3D7/regular-expressions)
2. NFAs [Video](https://www.coursera.org/learn/algorithms-part2/lecture/go3D7/regular-expressions)
3. NFA Simulation [Video](https://www.coursera.org/lecture/algorithms-part2/nfa-simulation-oBemg)
4. NFA Construction [Video](https://www.coursera.org/lecture/algorithms-part2/nfa-construction-CPhIB)
5. Regular Expressions Applications [Video](https://www.coursera.org/lecture/algorithms-part2/regular-expression-applications-7RfPB)
6. Implement NFA

## Week 7

### Monday

Data Compression

1. Introduction to Data Compression [Video](https://www.coursera.org/learn/algorithms-part2/lecture/OtmHU/introduction-to-data-compression)
2. Run-Length-Coding [Video](https://www.coursera.org/lecture/algorithms-part2/introduction-to-data-compression-OtmHU)

### Tuesday

Data Compression

1. Huffman Compression [Video](https://www.coursera.org/lecture/algorithms-part2/huffman-compression-6Hzrx)
2. Implement Huffman Compression

### Wednesday
1. LZW Compression [Video](https://www.coursera.org/lecture/algorithms-part2/lzw-compression-lQ4b0)
2. Implement LZW Compression

### Thursday

Context

1. Reductions [Videp](https://www.coursera.org/lecture/algorithms-part2/introduction-to-reductions-oLAm2)
2. Linear Programming [Video](https://www.coursera.org/lecture/algorithms-part2/brewers-problem-qcFRy)

### Friday

Context

1. P vs. NP [Video](https://www.coursera.org/lecture/algorithms-part2/p-vs-np-rN2J6)
2. NP Completeness [Video](https://www.coursera.org/learn/algorithms-part2/lecture/c28Sw/np-completeness)
