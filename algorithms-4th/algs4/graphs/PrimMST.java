import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.MinPQ;

public class PrimMST {
    private Queue<Edge> MST;
    private boolean[] marked;
    private MinPQ<Edge> pq;

    public PrimMST(EdgeWeightedGraph G) {
        pq = new MinPQ<Edge>();
        MST = new Queue<Edge>();
        marked = new boolean[G.V()];
        visit(G, 0);
        while (!pq.isEmpty()) {
            Edge e = pq.delMin();
            int v = e.either(), w = e.other(v);
            if (marked[v] && marked[w]) continue;
            else {
                MST.enqueue(e);
                if (!marked[v]) visit(G, v);
                else if (!marked[w]) visit(G, w);

            }
        }
    }

    public void visit(EdgeWeightedGraph G, int v) {
        marked[v] = true;
        for (Edge e : G.adj(v)) {
            if (!marked[e.other(v)]) pq.insert(e);
        }
    }

    public Iterable<Edge> edges() {
        return MST;
    }

    public double weight() {
        double w = 0.0;
        for (Edge e : MST) {
            w += e.weight();
        }
        return w;
    }

    public static void main(String args[]) {
        In in = new In(args[0]);
        EdgeWeightedGraph g = new EdgeWeightedGraph(in);
        PrimMST mst = new PrimMST(g);
        for (Edge e : mst.MST) {
            StdOut.println(e.toString());
        }

        StdOut.println(mst.weight());
    }

}
