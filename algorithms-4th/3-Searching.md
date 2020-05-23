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

## 3.3 Red-Black BST

> 1.  Red links lean left
> 2.  No node has two read links connected to it
> 3.  The tree has perfect balck balance: every path from the root to a null link has the same number of black links.

```java
Node rotateLeft(Node h) {
    Node x = h.right;
    h.right = x.left;
    x.left = h;
    x.color = h.color;
    h.color = RED;
    x.N = h.N;
    h.N = 1 + size(h.right) + size(h.left);
    return x;
}
```

```java
Node rotateRight(Node h) {
    Node x = h.left;
    h.left = x.right;
    x.right = h;
    x.color = h.color;
    h.color = RED;
    x.N = h.N;
    h.N = 1 + size(h.left) + size(h.right);
    return x;
}
```

```java
void flipColors(Node h) {
    h.color = RED;
    h.left.color = BLACK;
    h.right.color = BLACK;
}
```

-   if the right child is red and the left child is black, rotate left;
-   if both the left child and its left child are red, rotate left;
-   if both children are red, flip colors;

```java
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
```
