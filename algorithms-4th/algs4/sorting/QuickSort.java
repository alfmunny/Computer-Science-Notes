import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public class QuickSort {
    private static int partition(Comparable[] a, int lo, int hi) {
        int p = lo;
        int i = lo+1;
        int j = hi;
        while (true) {
            while (i < hi && less(a[i], a[p])) i++;
            while (j > lo && less(a[p], a[j])) j--;
            if (i >= j) break;
            swap(a, i, j);
        }
        swap(a, p, j);
        return j;
    }

    private static void swap(Comparable[] a, int i, int j) {
        Comparable tmp = a[i];
        a[i] = a[j];
        a[j] = tmp; 
    }

    private static void sort(Comparable[] a, int lo, int hi) {
        if (a.length == 0) return;
        if (hi <= lo) return;
        int mid = partition(a, lo, hi);
        sort(a, lo, mid-1);
        sort(a, mid+1, hi);
    }

    private static boolean less(Comparable v, Comparable w) {
        return v.compareTo(w) < 0;
    }

    private static void exch(Object[] a, int i, int j) {
        Object swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    private static void show(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            StdOut.println(a[i]);
        }
    }

    private static boolean isSorted(Comparable[] a) {
        return isSorted(a, 0, a.length);
    }

    private static boolean isSorted(Comparable[] a, int lo, int hi) {
        for (int i = lo+1; i < hi; i++)
            if (less(a[i], a[i-1])) return false;
        return true;
    }

    public static void sort(Comparable[] a) {
        StdRandom.shuffle(a);
        sort(a, 0, a.length - 1);
        assert isSorted(a) : "Not Sorted";
    }

    public static void main(String[] args) {
        String[] a = StdIn.readAllStrings();
        sort(a);
        show(a);
    }
}
