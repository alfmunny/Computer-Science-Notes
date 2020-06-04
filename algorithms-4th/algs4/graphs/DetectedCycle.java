import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import java.io.InputStream;

public class DetectedCycle {
    private Digraph G;
    private boolean[] marked;
    private boolean[] onStack;
    private int[] edgeTo;
    private Stack<Integer> cycle;

    public DetectedCycle(Digraph g) {
        G = g;
        marked = new boolean[G.V()];
        onStack = new boolean[G.V()];
        edgeTo = new int[G.V()];
        for (int v = 0; v < G.V(); v++) {
            if (!marked[v]) dfs(v);
        }
    }

    private void dfs(int v) {
        marked[v] = true;
        onStack[v] = true;
        for (int w : G.adj(v)) {
            if (hasCycle()) return;
            else if (!marked[w]) { 
                edgeTo[w] = v;
                dfs(w);
            }
            else if (onStack[v]) {
                cycle = new Stack<Integer>();
                for (int x = v; x != w; x = edgeTo[x]) {
                    cycle.push(x);
                }
                cycle.push(w);
                cycle.push(v);
            }
        }
    }

    public boolean hasCycle() {
        return cycle != null;
    }

    public Iterable<Integer> cycle() {
        return cycle;
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        Digraph digraph = new Digraph(in);
        DetectedCycle dc = new DetectedCycle(digraph);
        if (dc.hasCycle()) {
            for (int v : dc.cycle()) {
                StdOut.print(Integer.toString(v) + " ");
            }
        }
    }
}
