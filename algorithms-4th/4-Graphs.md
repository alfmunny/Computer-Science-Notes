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
            else if (onStack[v]) {
                cycle = new Stack<Integer>();
                for (int x = v; x != w; x = edgeTo[x]) {
                    cycle.push(x);
                }
                cycle.push(w);
                cycle.push(v);
            }
            onStack[v] = false;
        }
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

### Prim Algorithm

### Kruskal Algorithm
