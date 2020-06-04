import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DepthFirstOrder {
    private Queue<Integer> pre;
    private Queue<Integer> post;
    private Stack<Integer> reversePost;
    private boolean[] marked; 
    private Digraph G;

    public DepthFirstOrder(Digraph g) {
        G = g;
        marked = new boolean[G.V()];
        pre = new Queue<Integer>();
        post = new Queue<Integer>();
        reversePost = new Stack<Integer>();
        for (int v = 0; v < G.V(); v++) {
            if (!marked[v]) dfs(v);
        }
    }

    private void dfs(int v) {
        pre.enqueue(v);
        marked[v] = true;
        for (int w : G.adj(v)) {
            if (!marked[w]) dfs(w);
        }
        post.enqueue(v);
        reversePost.push(v);
    }

    public Iterable<Integer> pre() { return pre; }
    public Iterable<Integer> post() { return post; }
    public Iterable<Integer> reversePost() { return reversePost; }

    public static void main(String[] args)  {
        In in = new In(args[0]);
        Digraph digraph = new Digraph(in);
        DepthFirstOrder order = new DepthFirstOrder(digraph);
        for (int v : order.reversePost()) {
            StdOut.print(Integer.toString(v) + " ");
        }
        for (int v : order.post()) {
            StdOut.print(Integer.toString(v) + " ");
        }
        for (int v : order.pre()) {
            StdOut.print(Integer.toString(v) + " ");
        }
    }
}
