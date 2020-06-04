public class SCC {
    private Digraph G;
    private int[] id;
    private boolean[] marked;
    private int count;

    public SCC(Digraph G) {
        marked = new boolean[G.V()];
        id = new int[G.V()];
        DepthFirstOrder depthFirstOrder = new DepthFirstOrder(G);
        for (int v : depthFirstOrder.reversePost()) {
            if (!marked[v]) 
            {
                dfs(G, v);
                count++;
            }
        }
    }

    private void dfs(Digraph G, int v) {
        marked[v] = true;
        id[v] = count;
        for (int w : G.adj(v)) {
            if (!marked[w]) dfs(G, w);
        }
    }

    public boolean stronglyConnected(int v, int w) {
        return id[v] == id[w];
    }

    public int id(int v) {
        return id[v];
    }

    public int count() {
        return count;
    }

}
