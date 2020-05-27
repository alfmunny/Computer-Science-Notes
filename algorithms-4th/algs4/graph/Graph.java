import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Queue;

public class Graph {
    private int V;
    private int E;
    private Bag<Integer>[] adj;
    boolean[] marked;
    int[] path;
    Queue<Integer> queue;

    public Graph(int v) {
        V = v;
        E = 0;
        adj = (Bag<Integer>[]) new Bag[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new Bag<Integer>();
        }
    }

    public Graph(In in) {
        this(in.readInt());
        int edges = in.readInt();
        for (int i = 0; i < edges; i++) {
            int v = in.readInt();
            int w = in.readInt();
            addEdge(v, w);
        }

    }

    public void addEdge(int v, int w) {
        adj[v].add(w);
        adj[w].add(v);
        E++;
    }

    public int degree(int v) {
        return adj[v].size();
    }
    
    public int V() {
        return this.V;
    }

    public int E() {
        return this.E;
    }

    public Iterable<Integer> adj(int v) {
        return  adj[v];
    }

    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(V + " vertices, " + E + " edges \n");
        for (int v = 0; v < V; v++) {
            s.append(v + ": ");
            for (int w : adj[v]) {
                s.append(w + " ");
            }
            s.append("\n");
        }
        return s.toString();
    }
    
    public void dfs(int v) {
        marked = new boolean[V];
        path = new int[V];
        dfsPath(v);
    }

    private void dfsPath(int v) {
        marked[v] = true;
        for (int w : adj[v]) {
            if(!marked[w]) {
                dfsPath(w);
                path[w] = v;
                StdOut.println(v + " -> " + w);
            }
        }
    }

    public void bfs(int v) {
        marked = new boolean[V];
        path = new int[V];
        queue = new Queue<Integer>();

        marked[v] = true;
        queue.enqueue(v);

        while (!queue.isEmpty()) {
            int q = queue.dequeue();
            for (int w : adj[q]) {
                if (!marked[w]) {
                    queue.enqueue(w);
                    path[w] = q;
                    marked[w] = true;
                    StdOut.println(q + " -> " + w);
                }
            }
        }
    }


    public static void main(String[] args) {
        In in = new In(args[0]);
        Graph graph = new Graph(in);
        StdOut.println(graph);
        graph.bfs(0);
    }

}
