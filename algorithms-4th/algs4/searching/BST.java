import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class BST<Key extends Comparable<Key>, Value> {
    private Node root;
    private class Node {
        private Key key;
        private Value val;
        private Node left, right;
        private int N;

        public Node(Key key, Value val, int N) {
            this.key = key;
            this.val = val;
            this.N = N;
        }
    }

    public int size() {
        return size(root);
    }

    private int size(Node x) {
        if (x == null) return 0;
        else return x.N;
    }

    private Value get(Node x, Key key) {
        if (x == null) return null;
        int cmp = key.compareTo(x.key);
        if (cmp < 0) return get(x.left, key);
        else if (cmp > 0) return get(x.right, key);
        else return x.val;
    }

    private Node put(Node x, Key key, Value val) {
        if (x == null) return new Node(key, val, 1);
        int cmp = key.compareTo(x.key);
        if (cmp < 0) x.left = put(x.left, key, val);
        else if (cmp > 0) x.right = put(x.right, key, val);
        else x.val = val;
        x.N = size(x.left) + size(x.right) + 1;
        return x;
    }

    private Node deleteMin(Node x) {
        if (x.left == null) return x.right;
         x.left = deleteMin(x.left);
         x.N = size(x.right) + size(x.left) + 1;
         return x;
    }

    public Value get(Key key) {
      return get(root, key);
    }

    public void put(Key key, Value val) {
        root = put(root, key, val);
    }

    public Node min(Node x) {
        if (x.left == null) return x;
        return min(x.left);
    }

    public void deleteMin() {
        root = deleteMin(root);
    }

    public void delete(Key key) {
        root = delete(root, key);
    }

    private Node delete(Node x, Key key) {
        if (x == null) return null;
        int cmp = key.compareTo(x.key);

        if (cmp < 0) delete(x.left, key);
        else if (cmp > 0) delete(x.right, key);
        else {
            if (x.left == null) return x.right;
            else if (x.right == null) return x.left;
            else {
                Node t = x;
                x = min(x.right);
                x.right = delete(x.right, x.key);
                x.left = t.left;
            }
        }
        x.N = size(x.left) + size(x.right) + 1;
        return x;
    }

    public void inorder() {
        inorder(root);
    }

    public int rank(Key key) {
        return rank(root, key);
    }

    private int rank(Node x, Key key) {
        if (x == null) return 0;
        int cmp = key.compareTo(x.key);
        if (cmp < 0) return rank(x.left, key);
        else if (cmp > 0) return size(x.left) + rank(x.right, key) + 1;
        else return size(x.left);
    }

    public Key select(int k) {
        if (k < 0 && k >= size(root)) return null;
        return select(root, k);
    }

    private Key select(Node x, int k) {
        if (x == null) return null;
        if (size(x.left) < k) return select(x.right, k - size(x.left) - 1);
        else if (size(x.left) > k) return select(x.left, k);
        else return x.key;
    }

    private void inorder(Node x) {
        if (x == null) return;
        inorder(x.left);
        StdOut.println(x.key);
        inorder(x.right);
    }

    public static void main(String[] args) {
        BST<String, String> bst = new BST<String, String>();
        String a[] = StdIn.readAllStrings();
        for (int i = 0; i < a.length; i++) { 
            bst.put(a[i], a[i]);
        }
        bst.deleteMin();
        bst.inorder();
        StdOut.println(bst.select(2));
        StdOut.println(bst.select(1));
        StdOut.println(bst.select(0));
    }
}
