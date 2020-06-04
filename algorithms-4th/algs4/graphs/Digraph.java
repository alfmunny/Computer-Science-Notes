import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Out;

public class Digraph {
    private int V;
    private int E;
    private Bag<Integer>[] adj;
        
    public Digraph(In in) {
        this(in.readInt());
        int edges = in.readInt();
        for (int e = 0; e < edges; e++) {
            int v = in.readInt();
            int w = in.readInt();
            addEdge(v, w);
        }
    }

    public Digraph(int v) {
        V = v;
        E = 0;
        adj = (Bag<Integer>[]) new Bag[v];
        for (int i = 0; i < V; i++) {
            adj[i] = new Bag<Integer>();
        }
    }

    public void addEdge(int v, int w) {
        adj[v].add(w);
        E++;
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        Digraph digraph = new Digraph(in);
    }

    public int V() { return V; }
    public int E() { return E; }
    public Iterable<Integer> adj(int v) { return adj[v]; }
}
