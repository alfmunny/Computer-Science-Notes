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

## Substring Search

## Data Compression
