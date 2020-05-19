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

        public int size() {
            return size(root);
        }

        private int size(Node x) {
            if (x == null) return 0;
            else return x.N;
        }

        public Value get(Key key) {
          return get(root, key);
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

        private Node deleteMin(Node x) {
            if (x.left == null) return x.right;
             x.left = deleteMin(x.left);
             x.N = size(x.right) + size(x.left) + 1;
             return x;
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
                    x.right = deleteMin(x.right);
                    x.left = t.left;
                }
            }
            x.N = size(x.left) + size(x.right) + 1;
            return x;
        }
    }
}
