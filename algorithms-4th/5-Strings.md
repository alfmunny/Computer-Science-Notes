# 5. Strings


## String sorts

### Key-indexed Counting

-   Compute frequency counts
-   Transform counts to indices
-   Distribute the data
-   Copy back

```java
public class KeyIndexedCounting {
    public void sort(String[] a) {
        int N = a.length;
        String[] aux = new String[N];
        int[] count = new int[R+1];

        for (int i < 0; i < N; i++) {
            count[a[i].key() + 1]++;
        }

        for (int r = 0; r < R; r++) {
            count[r+1] = count[r];
        }

        for (int i = 0; i < N; i++) {
            aux[count[a[i].key()]++] = a[i];
        }

        for (int i = 0; i < N; i++) {
            a[i] = aux[i];
        }
    }
}
```

### LSD string sort

Least-significant-digit first string sort.

Consider the string from right to left.

LSD only works for fixed-length strings.

```java
public class LSD {
    pubic staitc void sort(String[] a, int W) {
        int N = a.length;
        int R = 256;
        String[] aux = new String[N];
        for (int d = W-1; d >= 0; d--) {
            int count = new int[R+1];

            for (int i = 0; i < N; i++) {
                count[a[i].charAt(d)+1]++;
            }

            for (int r = 0; r < R; i++) {
                count[r+1] += count[r];
            }

            for (int i = 0; i < N; i++) {
                aux[count[a[i].charAt(d)]++] = a[i];
            }

            for (int i = 0; i < N; i++) {
                a[i] = aux[i];
            }
        }
    }
}
```

### MSD string sort

To implement a general-purpose string sort, where strings are not necessarily all the same length, we consider the characters in left-to-right order.

```java
public class MSD {
    private static int R = 256;
    private static final int M = 15;
    private static String[] aux;

    public static void int charAt(String[] a, int d) {
        if (d < s.length()) return s.charAt(d);
        else return -1;
    }

    public static void sort(String[] a) {
        int N = a.length;
        aux = new String[N];
        sort(a, 0, N-1, 0);
    }

    private static void sort(String[] a, int lo, int hi, int d) {
        if (hi <= lo + M) {
            Insertion.sort(a, lo, hi, d);
            return;
        }

        int[] count = new int[R+2];

        for (int i = lo; i <= hi; i++)
            count[charAt(a[i], d)+2]++;
        for (int r = 0; r < R+1; r++)
            count[r+1] += count[r];
        for (int i = 0; i <= hi; i++)
            aux[count[charAt(a[i], d)+1]++] = a[i];
        for (int i = lo; i <= hi; i++)
            a[i] = aux[i - lo];
        for (int r = 0; r < R; r++)
            sort(a, lo+count[r], lo+count[r+1], d+1);
    }
}

```

> To sort N strings taken from an R-character alphabet, the amount of space needed by MSD string sort is proportional to R times the length of the longest string (plus N), in the worst case.

| algorithm              | stable? | inplace? | running time        |
|---------------------- |------- |-------- |------------------- |
| insertion sort         | yes     | yes      | between N and N^2   |
| quicksort              | no      | yes      | NlogN               |
| mergesort              | yes     | no       | NlogN               |
| 3-way quicksort        | no      | yes      | between N and NlogN |
| LSD string sort        | yes     | no       | NW                  |
| MSD string sort        | yes     | no       | between N and NW    |
| 3-way string quicksort | no      | yes      | between N and NW    |

## Tries

**Search in a trie**

> -   The value at the node corresponding to the last character in the key is not null (as in the searches for shells and she depicted at left above). This result is a search hit—the value associated with the key is the value in the node corre- sponding to its last character.
> 
> -   The value in the node corresponding to the last character in the key is null (as in the search for shell depicted at top right above). This result is a search miss: the key is not in the table.
> 
> -   The search terminated with a null link (as in the search for shore depicted at bottom right above). This result is also a search miss.

```java
public class TrieST<Value> {
    private static int R = 256;
    private Node root;

    private static class Node {
        private Object val;
        private Node[] next = new Node[R];
    }

    public Value get(String key) {
        Node x = get(root, key, 0);
        if (x == null) return null;
        return (Value) x.val;
    }

    private Node get(Node x, String key, int d) {
        if (x == null) return null;
        if (d == key.length()) return x;
        char c = key.charAt(d);
        return get(x.next[c], key, d+1);
    }

    public void put(String key, Value val) {
        root = put(root, key, val, 0);
    }

    private Node put(Node x, String key, Value val, int d) {
        if (x == null) x = new Node();
        if (d == key.lenght()) { x.val = val; return x; }
        char c = key.charAt(d);
        x.next[c] = put(x.next[c], key, val, d+1);
        return x;
    }
}

```

### Ternary search tries (TSTs)

TST avoids the excessive space cost associated with R-way tries

> In a TST, each node has a character, three links, and a value. The three links correspond to keys whose current characters are less than, equal to, or greater than the node’s character.

```java

```

## Substring Search

Brute-force backing up text.

If i and j point to mismatching characters, then we back up both pointers: j to point to the beginning of the pattern and i to correspond to moving the pattern to the right one position

```java
public static int search(String pat, String txt) {
    for (i = 0, j = 0; i < N && j < M; i++) {
        if (txt.charAt(i) == pat.charAt(j)) j++;
        else { i -= j; j = 0; }
    }

    if (j == M) return i - M;
    else return N;
}
```

### KMP

Knuth-Morris-Pratt substring search.

The basic idea:

> Whenever we detect a mismatch, we already know some of the characters in the text. We can take advantage of this information to void backing up the text pointer over all those known characters.

**Backing up the pattern pointer**. We use an array dfs[][] to record how far to back up the pattern pointer j when a mismatch is detected.

**KMP search method**. Once we have computed the dfa[][] array: when i and j point to mismatching characters, set j to dfs[txt.charAt(i)][j] and increment i.

```java
public int search(String txt) {
    int i, j, N = txt.length();
    for (i = 0, j = 0; i < N && j < M)
        j = dfs[txt.charAt(i)][j];
    if (j == M) return i - M;
    else return N;
}
```

**DFA simulation**. A useful way to describe this process is in terms of a deterministic finite-state automaton (DFA).

**Constructing the DFA** Remarkably, to construct the dfa[][] array is to use DFA itself. When we have a mismatch at pat.charAt(j), our interest is in knowing in what state the DFA would be if we were to back up the text index and rescan the text characters that we just saw after shifting to the right one position. (It's like, we have treat the pattern as the text, when we have a mismatch, we want to move to the next position of the text, and use the DFA to find the pattern from there. As we have already construct the DFA before position j, we can use it to match the pattern until j-1)

The crucial detail to the computation is to observe that maintaining the restart position X.

For each j:

-   Copies dfs[][X] to dfa[][j] (for mismatch cases)
-   Sets dfa[pat.charAt(j)][j] to j+1 (for match case)
-   Updates X

```java
public void construct() {
    dfa[pat.charAt(0)][0] = 1;
    for (int X = 0, j = 1; j < M; j++) {
        for (int c = 0; c < R; c++)
            dfa[c][j] = dfa[c][X];
        dfa[pat.charAt(j)][j] = j+1;
        X = dfa[pat.charAt(j)][X];
}
```

```java
public class KMP {
    private String pat;
    private int[][] dfa;

    public KMP(String pat) {
        this.pat = pat;
        int M = pat.length();
        int R = 256;

        dfa = new int[R][M];
        dfa[pat.charAt(0)][0] = 1;
        for (int X = 0, j = 1; j < M; j++) {
            for (int c = 0; c < R; c++)
                dfa[c][j] = dfa[c][X];
            dfa[pat.charAt(j)][j] = j+1;
            X = dfa[pat.charAt(j)][X];
        }
    }

    public int search(String txt) {
        int i, j, N = txt.length(), M = pat.length();
        for (i = 0, j = 0; i < N && j < M; i++)
            j = dfa[txt.charAt(i)][j];

        if (j == M) return i - M;
        else return N;
    }

    public static void main(Stirng[] arg) {
        String pat = args[0];
        String txt = args[1];
        KMP kmp = new KMP(pat);
        StdOut.println("text:     " + txt);
        int offset = kmp.search(txt);
        StdOut.print("pattern: ");
        for (int i = 0; i < offset; i++)
            StdOut.print(" ");
        StdOut.println(pat);
    }
}
```

## Data Compression
