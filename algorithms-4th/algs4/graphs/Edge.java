public class Edge implements Comparable<Edge> {
    private final int v;
    private final int w;
    private final double weight;

    public Edge(int v, int w, double weight) {
        this.v = v;
        this.w = w;
        this.weight = weight;
    }

    public int either() {
        return this.v;
    }

    public int other(int vertex) {
        if (vertex == v) return w;
        else if (vertex == w) return v;
        else throw new RuntimeException("Inconsistent edge");
    }

    public double weight() {
        return weight;
    }

    public int compareTo(Edge e) {
        if (e.weight == this.weight) return 0;
        else if (e.weight > this.weight) return -1;
        else return 1;
    }

    public String toString() {
        return String.format("%d-%d %.2f", v, w, weight);
    }
}
