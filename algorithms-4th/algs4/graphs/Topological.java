public class Topological {
    private Digraph G;
    private Iterable<Integer> order;

    public Topological(Digraph g) {
        G = g;
        DetectedCycle dc = new DetectedCycle(g);
        if (!dc.hasCycle()) {
            DepthFirstOrder depthFirstOrder = new DepthFirstOrder(G);
            order = depthFirstOrder.reversePost();
        }
    }

    public Iterable<Integer> order() {
        return order;
    }

    public boolean isDAG() {
        return order == null;
    }

}
