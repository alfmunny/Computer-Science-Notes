# 2. Sorting


## 2.1 Selection sort

> Slection sort uses ~N^2/2 compares and N exchanges to sort an array of length N.

**Running time is insensitive to input**. It taks about as long to run selection sort for an array that is already in order or for an array with all keys equal as it does for a randomly-ordered array.

**Data movement is minimal**. N changes. None of the orther sorting algorithms that we consider have this property.

```java
public class Selection {
    public static void sort(Comparable[] a) {
        int N = a.length;
        for (int i = 0; i < N; i++) {
            int min = i;
            for (int j = i+1; j < N; j++)
                if (less(a[j], a[min])) min = j;
            exch(a, i, min);
        }
    }
}
```

## 2.2 Insertion sort

> Insertion sort uses ~N^2/4 compares and ~N^2/4 exchanges to sort a randomly ordered array of length N with distinct keys, on the average. The worst cas is ~N^2/2 compares and ~N^2/2 exchanges (reversed) and the best case is N - 1 compares and 0 exchanges (already sorted)

```java
public class Insertion {
    public  static void sort(Comparable[] a) {
        int N = a.length;
        for (int i = 1; i < N; i++) {
            for (int j = i; j > 0 && a[j] < a[j-1]; j--)
                exch(a, j, j-1);
        }
    }
}
```

\*Partially sorted array:

For instance,

E X A M P L E has 11 inversions: E-A, X-A, X-M, X-P, X-L, X-E, M-L, M-E, P-L, P-E, and L-E.

If the number of inversions in an array is less than a constant multiple of the array size, we say that the array is partially sorted.

Typical examples of partially sorted arrays:

-   An array where each entry is not for from its final position
-   A small array appended to a large sorted array
-   An array with ouly a few entries that are not in place

**Insertion sort is an efficient method for such arrays; selection sort is not**.

Excellent method for partially sorted arrays and is also a fine method for tiny arrays.

Improvement see exercise 2.1.25

## 2.3 Shellsort

Insertion sort moves an item only one place each time. When the smallest item happends to be at the end of array, we need to moves N-1 steps.

Shellsort basically gains speed to exchanges items that for far apart, to produce **partially sorted** array, which can be sorted eventually by insertion sort.

Increment sequences here is 1, 4, 13, 40, 121, 364, 1093&#x2026;

> Increment sequences that are substantially better still may be waiting to be discovered.

```java
public class Shell {
    public static void sort(Comparable[] a) {
        int N = a.length;
        int h = 1;
        while (h < N/3) h = 3 * h + 1;
        while (h >= 1) {
            for (int i = h; i < N; i++) {
                for (int j = i; j >= h && less(a[j], a[j-h]); j -= h ) {
                    exch(a, j, j-h);
                }
            }
            h = h/3;
        }
    }
}
```

## Comparison

Use the random library to do some interesting comparison

```java
public class SortCompare {
    public static double time(String alg, Double[] a) {
        Stopwatch timer = new Stopwatch();
        if (alg.equals("Insertion")) Insertion.sort(a);
        if (alg.equals("Selection")) Insertion.sort(a);
        if (alg.equals("Shell")) Insertion.sort(a);
    }

    // Use alg to srot T random arrays of length N
    public static double timeRandomInput(String alg, int N, int T) {
        double total = 0.0;
        Double[] a = new Double[N];
        for (int t = 0; t < T; t++) {
            for (int i = 0; i < N; i++) {
                a[i] = StdRandom.uniform();
            }
            total += time(alg, a);
        }
        return total;
    }

    public static void main(String[] args) {
        String alg1 = args[0];
        String alg2 = args[1];
        int N = Integer.parseInt(args[2]);
        int T = Integer.parseInt(args[3]);
        double t1 = timeRandomInput(alg1, N, T);
        double t2 = timeRandomInput(alg2, N, T);
        StdOut.printf("For %d random Doubles\n    %s is", N, alg1);
        StdOut.printf(" %.1f times faster than %s\n", t2/t1, alg2);
    }
}
```

Comparison between Insertion and Selction

100 arrays of length 1000

    % java SortCompare Insertion Selection 1000 100
    For 1000 random Doubles
      Insertion is 1.7 times faster than Selection

Comparison between Shell and Insertion

100 arrays of length 1000

    % java SortCompare Shell Insertion 1000 100
    For 1000 random Doubles
        Shell is 4.0 times faster than Insertion

100 arrays of length 10000

    % java SortCompare Shell Insertion 10000 100
    For 10000 random Doubles
        Shell is 48.4 times faster than Insertion

100 arrays of length 100000

    % java SortCompare Shell Insertion 100000 100
    For 100000 random Doubles
        Shell is 418.1 times faster than Insertion
