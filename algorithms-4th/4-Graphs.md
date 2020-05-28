# Graphs


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
