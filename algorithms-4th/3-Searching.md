# 3. Searching


## 3.1 Symbol Tables

TODO

## 3.2 Binary Search Trees

> A binary search tree (BST) is a binary tree where each node has a Comparable key (and an associated value) and satisfied the restriction that the key in any node is larger than the keys in all nodes in that node's left subtree and smaller than the keys in all nodes in that node's right subtree

> size(x) = size(x.left) + size(x.right) + 1

```java
public class BST<Key extends Comparable<Key>, Value> {
    private Node root;
    private class Node {
        private Key key;
        private Value val;
        private Node left, right;
        private int N;

        public Node(Key key, Value value, int N) {
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
          return get(root, key)
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
    }
}
```

### Deletion

**Delete Minimum**

```java
public void deleteMin() {
    root = deleteMin(root);

}
private Node deleteMin(Node x) {
    if (x.left == null) return x.right;
    x.left = deleteMin(x.left);
    x.N = size(x.left) + size(x.right) + 1;
    return x;
}
```

**Hibbard deletion**

```java
public void delete(Key key)
{ root = delete(root, key); }

private Node delete(Node x, Key key)
{
    if (x==null) return null;
    int cmp = key.compareTo(x.key);
    if (cmp < 0) x.left = delete(x.left, key);
    else if (cmp > 0) x.right = delete(x.right, key);
    else {
        if (x.right == null) return x.left;
        else if (x.left == null) return x.right;
        Node t = x;
        x = min(t.right);
        x.right = deleteMin(t.right);
        x.left = t.left;
    }
    x.N = size(x.left) + size(x.right) + 1;
    return x;
}
```

**Hibbard deletion** always align to the right side of the tree.

With a large amount of deletion operation, the tree would become likely unbalanced.

To optimize the BST we will consider another tree data structure in the next: Red-Black Tree.
