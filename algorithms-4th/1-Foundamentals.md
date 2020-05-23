# 1. Foundamentals


## Standard output

| public class StdOut                    |                             |
|-------------------------------------- |--------------------------- |
| static void print(Stirng s)            | print s                     |
| static void println(String s)          | print s, followd by newline |
| static void println()                  | print a new line            |
| static void prinft(String f, &#x2026;) | formatted print             |

```java
public class RandomSeq
{
    public static void main(String[] args)
    {
        int N = Integer.parseInt(args[0]);
        double lo = Double.parseDouble(args[1]);
        double hi = Double.parseDouble(args[2]);
        for (int i = 0; i < N; i++) {
            double x = StdRandom.uniform(lo, hi);
            StdOut.printf("%.2f\n", x);
        }
    }
}
```

## Formatted output

| type   | code | typical literal    | sample  format strings | coverted string  values for output |
|------ |---- |------------------ |---------------------- |---------------------------------- |
| int    | d    | 512                | "%14d"                 | "           512"                   |
|        |      |                    | "%-14d"                | "512          "                    |
| double | f    | 1595.1680010754388 | "%14.2f"               | "        1595.17"                  |
|        | e    |                    | "%0.7f"                | "1595.1690011"                     |
|        |      |                    | "%14.4e"               | "     1.5952e+03"                  |
| String | s    | "Hello, World"     | "%14s"                 | "   Hello, World"                  |
|        |      |                    | "-14s"                 | "Hello, World   "                  |
|        |      |                    | "-14.5s"               | "Hello          "                  |

## Stack

### Linkedlist implementation

```java
public class LinkedStack<Item> implements Iterable<Item> {
    private  int n;
    private Node first;
    private class Node {
        private Item item;
        private Node next;
    }

    public LinkedStack() {
        first = null;
        n = 0;
        assert check();
    }

    public boolean isEmpty() {
        return first == null;
    }

    public int size() {
        return n;
    }

    public void push(Item item) {
        Node oldfirst = first;
        first = new Node();
        first.item = item;
        first.next = oldfirst;
        n++;
        assert check();
    }

    public Item pop() {
        if (isEmpty()) throw new NoSuchElementException("Stack underflow");
        Item item = first.item;
        first = first.next;
        n--;
        assert check();
        return item;
    }

    public Iterator<Item> iterator() {
        return new LinkedIterator();
    }

    private class LinkedIterator implements Iterator<Item> {
        private Node current = first;
        public boolean hasNext() { return current != null; }
        public void remove() { throw new UnsupportedOperationException(); }

        public Item next() {
            if (!hasNext()) throw new NoSuchElementException();
            Item item = current.item;
            current = current.next;
            return item;
        }
    }

}
```

### Resizing array implementation

```java
public class ResizingArrayStack<Item> implements Iterable<Item> {
    private Item[] a = (Item[]) new Object[1];
    private int N = 0;
    public boolean isEmpty() { return N == 0; }
    public int size() { return N; }

    private void resize(int max) {
        Item[] temp = (Item[]) new Object[max];
        for (int i = 0; i < N; i++)
            temp[i] = a[i];
        a = temp;
    }

    public void push(Item item) {
        if (N == a.length) resize(2*a.length);
        a[N++] = item;
    }

    public Item pop() {
        Item item = a[N-1];
        a[--N] = null;
        if (N > 0 && N == a.length/4) resize(a.length/2);
        return item;
    }

    public Iterator<Item> iterator() {
        return new ReverseArrayIterator();
    }

    private class ReverseArrayIterator implements Iterator<Item> {
        private int i = N;
        public boolean hasNext() { return i > 0; }
        public Item next() { return a[--i]; }
        public void remove() { }
    }

}

```

## Queue

### LinkedList implementation

```java
public class LinkedQueue<Item> implements Iterable<Item> {
    private int N = 0;
    private Node first;
    private Node last;

    private class Node {
        Item item;
        Node next;
    }

    public boolean isEmpty() { return first == null; }

    public void enqueue(Item item) {

        Node oldlast = last;
        last = new Node();
        last.item = item;
        last.next = null;
        if (isEmpty()) first = last;
        else oldlast.next = last;
        N++;
    }

    public Item dequeue() {
        if (N > 0) {
            Item item = first.item;
            first = first.next;
            if (isEmpty()) last = null;
            N--;
            return item;
        }
        else {
            throw new NoSuchElementException();
        }
    }

}
```
