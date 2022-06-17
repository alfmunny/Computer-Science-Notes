# 4. Graphs


## Undirected Graph

### Adjacency-lists data structure

1.  Space usage proportional to V+E
2.  Constant time to add an edge
3.  Time proportional to the degree of v to iterate through vertices adjacent to v

```java
public class Graph {
    private final int V;
    private int E;
    private Bag<Integer>[] adj;

    public Graph(int V) {
        this.V = V; this.E = 0;
        adj = (Bag<Integer>[]) new Bag[V];
        for (int v = 0; v < V; v++)
            adj[v] = new Bag<Integer>();
    }

    public Graph(In in) {
        this(in.readInt());
        int E = in.readInt();
        for (int i = 0; i < E; i++) {  // Add an edge.
            int v = in.readInt();
            int w = in.readInt();
            addEdge(v, w);
        }
    }

    public int V()  {  return V;  }

    public int E()  {  return E;  }

    public void addEdge(int v, int w)
    {
        adj[v].add(w);
        adj[w].add(v);
        E++;
    }

    public Iterable<Integer> adj(int v)
    {  return adj[v];  }
}
```

### DFS

```java
public void dfs(Graph G, int v) {
  dfs(G, v);
}

private void dfs(Graph G, int v) {
    marked[v] = true;
    for (int w : adj[v]) {
        if(!marked[w]) {
            edgeTo[w] = v;
            dfs(G, w);
        }
    }
}
```

### BFS

```java
private void bfs(Graph G, int s) {
    Queue<Integer> queue = new Queue<Integer>();
    marked[s] = true;          // Mark the source
    queue.enqueue(s);          //   and put it on the queue.
    while (!q.isEmpty()) {
        int v = queue.dequeue(); // Remove next vertex from the queue.
        for (int w : G.adj(v))
            if (!marked[w]) {  // For every unmarked adjacent vertex
                edgeTo[w] = v;     //
                marked[w] = true;  //
                queue.enqueue(w);
            }
    }
}
```

> For any vertex v reachable from s, BFS computes a shortest path from s to v (no path from s to v has fewer edges).

### Connected components

```java
public void connected() {
    id = new int[V];
    for (int v = 0; v < V, v++) {
        if (!marked[v]) {
            dfs[G, v];
            count++;
        }
    }
}

private void dfs(Graph G, int v) {
    marked[v] = true;
    id[v] = count;
    for (int w : G.adj(v))
        if (!marked[w])
            dfs(G, w)
```

## Directed Graph

### Reachability

The identical code with Graph changed to Digraph solves the analogous problem for digraphs: Single-source reachability

Multi-source reachability:

Given a digraph and a set of source vertices, is there a directed path from any vertex in the set to a given target vertex v.

An import application of multiple-source reachability is found in typical memory management systems. A mark-and-weep garbage collection strategy reserves one bit per object for the purpose of gargage collection, then periodically marks the set of potentially accesible objects by running a digraph reachability.

### Cycles and DAGs

> A directed acylic graph is a digraph with no directed cycles

Cycle Detect

Use an onStack array to remember the trace of the cycle.

```java
public class DirectedCycle {
    private boolean[] onStack;
    private boolean[] marked;
    private int[] edgeTo;
    private Stack<Integer> cycle;

    public DirectedCycle(Digraph G) {
        onStack = new boolean[G.V()];
        marked = new boolean[G.V()];
        for (int v = 0; v < G.V(); v++) {
            if (!marked[v]) dfs(G, v);
        }
    }

    private void dfs(Digraph G, int v) {
        onStack[v] = true;
        marked[v] = true;

        for (int w : G.adj(v)) {
            if (this.hasCycle()) return;
            else if (!marked[w]) {
                edgeTo[w] = v;
                dfs(G, w);
            }
            else if (onStack[w]) {
                cycle = new Stack<Integer>();
                for (int x = v; x != w; x = edgeTo[x]) {
                    cycle.push(x);
                }
                cycle.push(w);
                cycle.push(v);
            }
        }
        onStack[v] = false;
    }

    public boolean hasCycle() {
        return cycle != null;
    }

    public Iterable<Integer> cycle() {
        return cycle;
    }

}
```

### Topogogical Sort

> A digraph has topological order if and only if it is a DAG

Three vertex orderings are of interest in typical applications

1.  Preorder: Put the vertex on a queue before the recursive calls. (order of dfs calls)
2.  Postorder: Put the vertex on a queue after the recursive calls. (order in which vertices are done)
3.  Reverse postorder: Put the vertex on a stack after the recursive calls.

```java
private void dfs(Digraph G, int v) {
  preorder.enqueue(v);
  marked[v] = true;
  for (int w : G.adj(v))
      if (!marked[w])
          dfs(G, w);
  post.enqueue(v);
  reversePost.push(v);
}
```

> Reverse postorder in a DAG is a topological sort

If the graph is a DAG, there is a reversed post order, which solves the job scheduling problem, otherwise, the order is null.

```java
public class Topological {
    private Iterable<Integer> order;

    public Topological(Digraph G) {
        DirectedCycle cyclefinder = new DirectedCycle(G);
        if (!cyclefinder.hasCycle()) {
            DepthFirstOrder dfs = new DepthFirstOrder(G);
            order = dfs.reversePost();
        }
    }
}
```

> With DFS, we can topological sort a DAG in time proportional to V+E

### Strong components

> Definition. Two vertices v and w are strongly connected if they are mutually reachable: that is, if there is a directed path from v to w and directed path from w to v. A digraph is strongly connected if all its vertices are strongly connected to one another.

**Kosaraju's algorithm**

1.  GIven a digraph G, compute the reverse postorder of its reverse G\_R
2.  Run a strandard DFS on G, but consider the unmarked vertices in reverse postorder
3.  All vertices reach on a call to the outer dfs() are in a strong component

```java
public class KosarajuSCC {
    private boolean[] marked;
    private int[] id;
    private int count;

    public KosarajuSCC(Digraph G) {
        marked = new boolean[G.V()];
        id = new int[G.V()];
        DepthFirstOrder order = new DepthFirstOrder(G.reverse());
        for (int s : order.reversePost()) {
            if (!marked[s]) {
                dfs(G, s);
                count++;
            }
        }
    }

    private void dfs(Digraph G, int v) {
        marked[v] = true;
        id[v] = count;
        for (int w : G.adj(v))
            if (!marked[w])
                dfs(G, w)
    }
}
```

## Minimum Spanning Trees

Given an undirected edgeweighted graph, find an MST.

> Definition. Recall that a spanning tree of a graph is a connectec subgraph with no cycles that includes all the vertices. A minumum spanning tree (MST) of an edge-weighted graph is a spanninng tree whose weight is no larger than the weight of any other spanning tree.

Assumptions:

-   The graph is connected.
-   The edge weights are not neccessarily distances.
-   The edge weights may be zero or negative.
-   The edge weights are all different. (The MST may not be unique. But the algorithms work without modification in the presence of equal weights)

### Edge-weighted graph

```java
public class Edge implements Comparable<Edge> {
    public double weight() {}
    public int either() {}
    public int other(int v) {}
    int compareTo(Edge that) {}
    String toString()
}
```

```java
public class EdgeWeightedGraph {
    public EdgeWeightedGraph(int V) {}
    public EdgeWeightedGraph(In in) {}
    public int V() {}
    public int E() {}
    public void addEdge(Edge e) {}
    public Iterable<Edge> adj(int v) {}
    public ITerable<Edge> edges() {}
    public String toString() {}
}
```

### Prim's Algorithm

Start with any vertex as single-vertex tree; then add V-1 edges to it, always taking the next minimum-weight edge that connects a vertex on the tree to a vertex not yet on the tree.

Data structures:

-   Vertices on the tree: we use a vertex-indexed boolean array `marked[]`
-   Edges on the tree; We use on of two data structures: a queue `mst` to collect MST edges or a vertex-indexed array `edgeTo[]` of Edge objects.
-   Crossing edges: We use a `MinPQ<Edge>` priority queue that compares edges by weight.

**Lazy Version**: putting all of the incidet edges that are not ineligible onto the priority queue

```java
public class LazyPrimMST {
    private boolean[] marked;
    private Queue<Edge> mst;
    private MinPQ<Edge> pq;
    public LazyPrimMST(EdgeWeightedGraph G)
    {
        pq = new MinPQ<Edge>();
        marked = new boolean[G.V()];
        mst = new Queue<Edge>();
        visit(G, 0);   // assumes G is connected (see Exercise 4.3.22)
        while (!pq.isEmpty()) {
            Edge e = pq.delMin();                  // Get lowest-weight
            int v = e.either(), w = e.other(v);    //    edge from pq.
            if (marked[v] && marked[w]) continue;  // Skip if ineligible.
            mst.enqueue(e); // Add edge to tree.
            if (!marked[v]) visit(G, v); // Add vertex to tree
            if (!marked[w]) visit(G, w); //   (either v or w).
        }
    }

    private void visit(EdgeWeightedGraph G, int v) {
        // Mark v and add to pq all edges from v to unmarked vertices.
        marked[v] = true;
        for (Edge e : G.adj(v))
            if (!marked[e.other(v)]) pq.insert(e);
    }

    public Iterable<Edge> edges() {
        return mst;
    }

    public double weight() {
        double w = 0.0;
        for (Edge e : mst) {
            w += e.weight();
        }
        return w;
    }
}
```

> The lazy version of Prim's algorithm uses extra space proportional to E and time proportional to ElogE to compute the MST fo a connected edge-weighted graph with E edges and V vertices

**Eager Versionl**: only keep the smallest weight edge of a non-tree vertex

```java
public class EagerPrimMST {
    private boolean[] marked;
    private IndexMinPQ<Double> pq;
    private double[] distTo;
    private Edge[] edgeTo;

    public EagerPrimMST(EdgeWeightedGraph G) {
        edgeTo = new Edge[G.V()];
        distTo = new double[G.V()];
        marked = new boolean[G.V()];
        for (int v = 0l v < G.V(); v++) {
            distTo[v] = Double.POSTIVE_INFINITY;
        }
        pq = new IndexMinPQ<Double>(G.V());

        distTo[0] = 0.0;
        pq.insert(0, 0.0);
        while (!pq.empty()) {
            visit(G, pq.delMin());
        }
    }

    private void visit(EdgeWeightedGraph G, int v) {
        marked[v] = true;
        for (Edge e : G.adj(v)) {
            int w = e.other(v);
            if (marked[w]) continue;
            if (e.weight() < distTo[w]) {
                distTo[w] = e.weight();
                edgeTo[w] = e;
                if (pq.contains(w)) pq.changeKey(w, e.weight());
                else pq.insert(w, e.wieght());
            }
        }
    }
}
```

> The eager version of Prim;s algorithm uses extra space proportional to V and time proportional to ElogV to compute the MST fo a connected edge-weighted graph with E edges and V vertices

### Kruskal's Algorithm

Process the all the edges in order of their weight values, taking for the MST each edge taht does not fom a cycle with edges previously added, stopping after adding V - 1 edges have been taken.

```java
public class KruskalMST {
    private Queue<Edge> mst;

    public KruskalMST(EdgeWeightedGraph G) {
        mst = new Queue<Edge>();
        MinPQ<Edge> pq = new MinPQ<Edge>();
        for (Edge e : G.edges()) {
            pq.insert(e);
        }

        UF uf = new UF(G.V());

        while (!pq.isEmpty() && mst.size() < G.V() - 1) { // stop early
            Edge e = pq.delMin();
            int v = e.either(), w = e.other(v);
            if (uf.find(v) == uf.find(w)) continue;
            uf.union(v, w);
            mst.enqueue(e);
        }
    }

    public Iterable<Edge> edges() {
        return mst;
    }
}
```

> Kruskal’s algorithm uses space proportional to E and time proportional to E log E (in the worst case) to compute the MST of an edge-weighted connected graph with E edges and V vertices.

Kruskal’s algorithm is generally slower than Prim’s algorithm because it has to do a connected() operation for each edge, in addition to the priority-queue operations that both algorithms do for each edge processed

### Summary

| algorithm  | space | ttime |
|---------- |----- |----- |
| lazy Prim  | E     | ElogE |
| eager Prim | E     | ElogV |
| Kruskal    | E     | ElogE |

> Do Prim's and Kruskal's algorithms work for directed graphs?
> 
> No. not at all. That is a more difficult graph-processing problem known as the minimum cost arborescence problem

## Shortest Path

> Definition. A shortest path from vertex s to vertex t in an edge-weighted digraph is a directed path from s to t with the property that no other such path has a lower weight.

### Edge-weighted digraph data types

```java
public class DirectedEdge
{
    private final int v;
    private final int w;
    private final double weight;
    public DirectedEdge(int v, int w, double weight) {
        this.v = v;
        this.w = w;
        this.weight = weight;
    }

    public double weight() {  return weight;  }
    public int from() {  return v;  }
    public int to() {  return w;  }

    public String toString() {
        return String.format("%d->%d %.2f", v, w, weight);
    }
}
```

Edge relaxation

```java
private void relax(DirectedEdge e) {
    int v = e.from(), w = e.to();
    if (distTo[w] > distTo[v] + e.weight()) {
        distTo[w] = distTo[v] + e.weight();
        edgeTo[w] = e;
    }
}
```

### Dijkstra's Algorithm

> Dijkstra’s algorithm solves the single-source shortest-paths prob- lem in edge-weighted digraphs with nonnegative weights.

> Dijkstra’s algorithm uses extra space proportional to V and time proportional to E log V (in the worst case) to compute the SPT rooted at a given source in an edge-weighted digraph with E edges and V vertices.

> The marked[] array is not needed, because the condition !marked[w] is equivalent to the condition that distTo[w] is infinite. In other words, switching to undirected graphs and edges and omitting the references to distTo[v] in the relax() code in Algorithm 4.9 gives an implementation of Algorithm 4.7, the eager version of Prim’s algorithm (!). Also, a lazy version of Dijkstra’s algorithm along the lines of LazyPrimMST (page 619) is not difficult to develop.

```java
public class DijkstraSP {
    private DirectedEdge[] edgeTo;
    private double[] distTo;
    private IndexMinPQ<Double> pq;

    public DijkstraSP(EdgeWeightedDigraph G, int s) {
        edgeTo = new DirectedEdge[G.V()];
        distTo = new double[G.V()];
        pq = new IndexMinPQ<Double>(G.V());
        for (int v = 0; v < G.V(); v++)
            distTo[v] = Double.POSITIVE_INFINITY;
        distTo[s] = 0.0;
        pq.insert(s, 0.0);
        while (!pq.isEmpty())
            relax(G, pq.delMin());
    }

    private void relax(EdgeWeightedDigraph G, int v) {
        for(DirectedEdge e : G.adj(v)) {
            int w = e.to();
            if (distTo[w] > distTo[v] + e.weight()) {
                distTo[w] = distTo[v] + e.weight();
                edgeTo[w] = e;
                if (pq.contains(w)) pq.change(w, distTo[w]);
                else                pq.insert(w, distTo[w]);
            }
        }
    }

    public double distTo(int v) {}
    public boolean hasPathTo(int v) {}
    public Iterable<Edge> pathTo(int v) {}
}
```

### Acylic edge-weighted digraphs

An algorithm for finding shortest paths that is simpler and faster than Dijkstra's algorithm for edge-weighted DAGs.

-   Solves the single-source problem in linear time
-   Handles negative edge weights
-   Solves related problems, such as finding longest paths

```java
public class AcyclicSP {
    private DirectedEdge[] edgeTo;
    private double[] distTo;

    public AcyclicSP(EdgeWeightedDigraph G, int s) {
        edgeTo = new DirectedEdge[G.V()];
        distTo = new double[G.V()];
        for (int v = 0; v < G.V(); v++)
            distTo[v] = Double.POSITIVE_INFINITY;
        distTo[s] = 0.0;
        Topological top = new Topological(G);
        for (int v : top.order())
            relax(G, v);
    }

    private void relax(EdgeWeightedDigraph G, int v) {}
    public double distTo(int v) {}          // standard client query methods
    public boolean hasPathTo(int v) {}      //   for SPT implementatations
    public Iterable<Edge> pathTo(int v) {}
}

```

### Bellman-Fold's Algorithm

```java
public class BellmanFordSP {
    private double[] distTo;
    private DirectedEdge[] edgeTo;
    private boolean[] onQ;
    private Queue<Integer> queue;
    private int cost;
    private Iterable<DirectedEdge> cycle;

    public BellmanFordSP(EdgeWeightedDigraph G, int s) {
        distTo = new double[G.V()];
        edgeTo = new DirectedEdge[G.V()];
        onQ = new boolean[G.V()];
        queue = new Queue<Integer>();
        for (int v = 0; v < G.V(); v++)
            distTo[v] = Double.POSITIVE_INFINITY;
        distTo[s] = 0.0;

        queue.enqueue(s);
        onQ[s] = true;
        while (!queue.isEmpty() && !this.hasNegativeCycle()) {
            int v = queue.dequeue();
            onQ[v] = false;
            relax(v);
        }
    }

    private void relax(int v) {
        for (DirectedEdge e : G.adj(v)) {
            int w = e.to();
            if (distTo[w] > distTo[v] + e.weight()) {
                distTo[w] = distTo[v] + e.weight();
                edgeTo[w] = e;
                if (!onQ[w]) {
                    queue.enqueue(w);
                    onQ[w] = true;
                }
            }
        }
    }

    private void findNegativeCycle() {}
    public boolean hasNegativeCycle() {}
    public Iterable<Edge> negativeCycle() {}
}
```
