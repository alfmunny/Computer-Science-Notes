public class RedBlackBST<Key extends Comparable<Key>, Value> {
    private static final boolean RED = true;
    private static final boolean BLACK = false;
    private Node root;
    private class Node {
        Key key;
        Node left;
        Node right;
        Value value;
        int N;
    }

    private Node rotateLeft(Node h) {}
    private Node rotateRight(Node h) {}
    private Node flipColors(Node h) {}
    private isRed(Node h) {
        if (h == null) return BLACK;
        return h.color == RED;
    }

    public void put(Key key, Value val) {
        root = put(root, key, val);
        root.color = BLACK;
    }

    public Node put(Node h, Key key, Value val) {
        if (h == null)
            return new Node(Key, val, 1, RED);

        it cmp = key.compareTo(h.key);
        if (cmp < 0) return put(root.left, key. val);
        else if (cmp > 0) return put(root.right, key, val);
        else h.val = val;

        if (!isRed(h.left) && isRed(h.right)) rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left)) rotateRight(h);
        if (isRed(h.left) && isRed(h.right)) flipColors(h);

        h.N = 1 + size(h.right) + size(h.left);

        return h
}
