import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.IndexMinPQ;
import edu.princeton.cs.algs4.Bag;

public class EagerPrimMST {
    private Queue<Edge> MST;
    private boolean[] marked;
    private IndexMinPQ<Double> pq;
    private Edge[] edgeTo;
    private double[] distTo;

    public EagerPrimMST(EdgeWeightedGraph G) {
        pq = new IndexMinPQ<Double>(G.V());
        marked = new boolean[G.V()];
        edgeTo = new Edge[G.V()];
        distTo = new double[G.V()];
        for (int v = 0; v < G.V(); v++) {
            distTo[v] = Double.POSITIVE_INFINITY;

        }
        distTo[0] = 0.0;
        pq.insert(0, 0.0);
        while (!pq.isEmpty()) {
            visit(G, pq.delMin());
        }
    }

    public void visit(EdgeWeightedGraph G, int v) {
        marked[v] = true;
        for (Edge e : G.adj(v)) {
            int w = e.other(v);
            if (marked[w]) continue;
            if (e.weight() < distTo[w]) {
                edgeTo[w] = e;
                distTo[w] = e.weight();
                if (pq.contains(w)) pq.changeKey(w, e.weight());
                else pq.insert(w, e.weight());
            }
        }

    }

    public Iterable<Edge> edges() {
        Bag<Edge> mst = new Bag<Edge>();
        for (int v = 1; v < edgeTo.length; v++) {
            mst.add(edgeTo[v]);
        }

        return mst;
    }

    public double weight() {
        double w = 0.0;
        for (int v = 1; v < edgeTo.length; v++) {
            w += edgeTo[v].weight();
        }
        return w;
    }

    public static void main(String args[]) {
        In in = new In(args[0]);
        EdgeWeightedGraph g = new EdgeWeightedGraph(in);
        EagerPrimMST mst = new EagerPrimMST(g);
        for (Edge e : mst.edges()) {
            StdOut.println(e.toString());
        }

        StdOut.println(mst.weight());
    }

}
