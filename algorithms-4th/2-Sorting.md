# 2. Sorting

|             | in-place? | stable? | worst | average | best  | remarks                                          |
|----------- |--------- |------- |----- |------- |----- |------------------------------------------------ |
| selection   | x         |         | N^2/2 | N^2/2   | N^2/2 | N exchangesj                                     |
| insertion   | x         | x       | N^2/2 | N^2/4   | N     | use for small N or partially ordered             |
| shell       | x         |         | ?     | ?       | N     | tight code, subquadratic                         |
| quick       | x         |         | N^2/2 | 2NlgN   | NlgN  | NlgN probablistic guarantee fastest in practice |
| 3-way-quick | x         |         | N^2/2 | 2NlgN   | N     | improves quicksort in presence of duplicate keys |
| merge       |           | x       | NlgN  | NlgN    | NlgN  | NlgN guarantee, stable                          |
| heap        | x         |         | 2NlgN | 2NlgN   | NlgN  | NlgN guarantee, in-place                         |

## 2.1 Elementary Sort

### Selection sort

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

Selection sort is not stable. It swaps the min value with the first element, which changes the order of the first element.

> A sorting algorithm is said to be stable if two objects with equal keys appear in the same order in sorted output as they appear in the input array to be sorted.

### Insertion sort

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

### Shellsort

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

### Comparison

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

### Exercise

## 2.2 Mergesort

### Top-Down MergeSort

Notes:

1.  Use an auxiliary array for saving the original order temporarily. Don't create this aux array in the merge or sort method to avoid extra memory usage.
2.  We have to copy the original array between lo and hi into aux, every time before we merge, because the array in aux is alreay old.

```java
public class MergeSort {

    public static void merge(Comparable[] a, Comparable[] aux, int lo, int mid, int hi) {
        int l1 = lo;
        int l2 = mid + 1;

        // Don't forget to copy every time
        for (int k = lo; k <= hi; k++) {
            aux[k] = a[k];
        }

        for (int k = lo; k <= hi; k++) {
            if (l1 > mid) a[k] = aux[l2++];
            else if (l2 > hi) a[k] = aux[l1++];
            else if (less(aux[l1], aux[l2])) a[k] = aux[l1++];
            else a[k] = aux[l2++];
        }
    }

    public static void sort(Comparable[] a, Comparable[] aux, int lo, int hi) {
        if (hi <= lo) return;

        int mid = lo + (hi - lo) / 2;
        sort(a, aux, lo, mid);
        sort(a, aux, mid+1, hi);
        merge(a, aux, lo, mid, hi);
    }
}
```

> Top-down mergesort uses between 1⁄2NlgN and NlgN compares to sort any array of length N.
> 
> 1/2N: When the elements on one side is all greater or smaller than the other side, than on side gets copied back at first. N: When all elements have to be compared.

> Top-Down mergesort uses at most 6NlgN array access to sort an array of length N.
> 
> Each merge uses at most 6N array access (2N for the copy, 2N for the move back, and at most 2N for compares).

Possible improvement:

**Use insertion sort for small subarrays**.

**Test wether the array is already in order**. if (a[mid] <= a[mid+1]) return (skip call merge())

**Eliminate the copy to the auxiliary array**. Switch roles of aux and a.

### Bottom-Up MergeSort

Start by doing a pass of 1-by-1 merge, then 2-by-2, then 4-by-4 and so forth.

```java
public class MergeBU {
    public static void sort(Comparable[] a) {
        int N = a.lenght;
        aux = new Comparable[N];
        for (int sz = 1; sz < N; sz = sz + sz)
            for (int lo = 0; lo < N - sz;  lo += sz+sz) { // the mid is at maximum at N-2, otherwise you can merge when the right half is empty
                merge(a, aux, lo, lo+sz-1, Math.min(N-1, lo+sz+sz-1));
            }
    }
}
```

> Bottom-up mergesort uses between 1⁄2NlgN and NlgN compares and at most 6N lg N array accesses to sort an array of length N.

## 2.3 Quicksort

1.  stop left pointer when left side equal or greater than pivot
2.  stop right pointer when right side equal or less than pivot

```java
public class QuickSort {
    public static void sort(Comparablep[] a, int lo, int hi) {
        if (hi <= lo) return;
        int j = partition(a, lo, hi);
        sort(a, lo, j-1);
        sort(a, j+1, hi);
    }

    public static int partition(Comparable[] a, int lo, int hi) {
        int i = lo+1;
        int j = hi;
        int p = lo;

        while (true) {
            while (less(a[i], a[p])) {
                i++;
                if (i == hi) break;
            }
            while (less(a[p], a[j])) {
                j--;
                if (j == lo) break;
            }
            if (i >= j) break;
            swap(a, i, j);
        }

        swap(a, p, j);
        return j;
    }
}
```

> Quicksort uses ~ 2NlnN compares (and one-sixth that many exchanges) on the average to sort an array of length N with distinct keys.

**Partitioning in place**.

**Staying in bounds**. Do not run oof the left or right ends of the array. The test (j==lo) is redundant, since the partitioning item is at a[lo] and not less than it self.

**Terminating the loop**. i >= j. Consider why i > j won't work. For example when the array is decending [2, 1]. i will reach 1 and break, but j will stop at 1, because it is smaller than the pivot 2. They will never cross each other. If you don't have i >= j, there will be an endless loop.

**Handling items with keys equal to partitioning item's key**. It is best to stop the left scan for items with keys greater than or equal to the partitioning item’s key and the right scan for items with key less than or equal to the partitioning item’s key. Consider [1, 1, 1, 1, 1], if you don't stop for equal element, i will reach the end of the array, and split the array into 1 and N-1. The running time will be quadratic (1 + 2 + &#x2026; + N - 1).

**Terminating the recursion** if (hi <= lo) return. One item is always put into position.

Average Case:

> Quicksort uses ~2NlnN compares on average to sort an array of length N with distinct keys.

Worst Case:

> QuickSort uses ~ N^2/2 compares in the worst case, but random shuffling protects against this case.
> 
> For example: when you always partition the array into 1 and N-1 size, with a smallest (or greatest) partition item's key

### Possible Improvements

**Cutoff to insertion sort**. Insertion for tiny subarrays. if (hi <= lo + M) { Insertion.sort(a, lo, hi); return }

**Median-of-three partitioning**. Choosing a sample of size 3 and then partitioning on the middle item.

**Entropy-optimal sorting**. Improvement for arrays with large numbers of duplicate keys.

Partition into three parts, smaller than, equal to, and larget than. <https://en.wikipedia.org/wiki/Dutch_national_flag_problem>

```java
public class QuickSort3Way {
    public static void sort(Comparable[] a, int lo, int hi) {
        if (hi <= lo) return;
        int lt = lo, gt = hi, i = lo+1;
        Comparable v = a[lo];
        while (i <= gt) {
            if (less(a[i], v)) exch(a, i++, lt++);
            else if (less(v, a[i])) exch(a, i, gt--);
            else i++;
        }
        sort(a, lo, lt - 1);
        sort(a, gt + 1, hi);
    }
}
```

> Quicksort with 3-way partitioning uses ~(2ln2)NH compares to sort N items, where H is the Shannon entropy, defined from the frequencies of key values.

H = lgN when the keys are all distinct.

3-way quicksort’s running time to be proportional to N times the entropy of the distribution of input key values.

## 2.4 Priority Queue

It provides an easy way to guarrantee an logarithmetic running time for dynamic situations where large number of **insert** and **remove the maximum operations** are intermixed.

### Heap

> A binary tree is heap-ordered if the key in each node is larger than or equal to the keys in that node’s two children (if any).

> The largest key in a heap-ordered binary tree is found at the root.

> A binary heap is a collection of keys arranged in a complete heap-or- dered binary tree, represented in level order in an array (not using the first entry).

In a heap, the parent of the node in position k is in position [k/2] and, conversely, the two children of the node in position k are in positions 2k and 2k+1.

Move up the tree from a[k], we set k to k/2.

Move down the tree we set k to 2\*l or 2\*k + 1.

> Proposition P. The height of a complete binary tree of size N is ⎣ lg N ⎦ .

### Algorithms on heaps (Max Heap)

**Bottom-up reheapify(swim)**

```java
private void swim(int k) {
    while (k > 1 && less(k/2, k)) {
      exch(k/2, k);
      k = k/2;
    }
} 
```

**Top-down reheapify(sink)**

```java
private void sink(int k) {
    while (2*k < N) {
        int j = 2*k;
        if (j <= N && less(j, j+1)) j++;
        if (!less(k, j)) break;
        exch(k, j);
        k = j;
    }
}
```

**Insert**

Add the new key at the end of the array, and swim up.

**Remove the maximum**

Take the largest key off the top, put the last key on the top and sink it.

```java
public class MaxPQ<Key extends Comparable<Key>> {
    private Key[] pg;
    private int N = 0;
    public MaxPQ(int maxN) {
        pg = (Key[]) new Comparable[maxN+1];
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public void insert(Key v) {
        Key max = pq[1];
        exch(1, N);
        pq[N--] = null;
        sink(1);
        return max;
    }

    private boolean less(int i, int j);
    private void exch(int i, int j);
    private void swim(int k);
    private void sink(int k);
}
```

### Heapsort

1.  exchange the maximum value(top one) to the end
2.  reheapify
3.  repeat until the heap is empty

```java
public static void sort(Comparable[] a) {
    int N = a.length;
    for (int k = N/2; k >= 1; k--) { //start from the last parent, construct the heap
        sink(a, k, N);
    }

    while (N > 1) { // sort
        exch(a, 1, N--);
        sink(a, 1, N);
    }
}
```

**Complexity**

> It is the only method that we have seen that is optimal (within a constant factor) in its use of both time and space—it is guaranteed to use ~2N lg N compares and constant extra space in the worst case.

**Cache Performance**

> However, it is rarely used in typical applications on modern systems because it has poor cache performance: array entries are rarely compared with nearby array entries, so the number of cache misses is far higher than for quicksort, mergesort, and even shellsort, where most compares are with nearby entries.
