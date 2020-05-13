import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class MergeBU {

    private static Comparable[] aux;

    public static void merge(Comparable[] a, int lo, int mid, int hi) {
        int l1 = lo;
        int l2 = mid + 1;

        for (int k = lo; k <= hi ; k++)
            aux[k] = a[k];

        for (int i = lo; i <= hi; i++) {
            if (l1 > mid) a[i] = aux[l2++];
            else if (l2 > hi) a[i] = aux[l1++];
            else if (less(aux[l1], aux[l2])) a[i] = aux[l1++];
            else a[i] = aux[l2++];
        }
    }

    public static void sort(Comparable[] a) {
        int N = a.length;
        aux = new Comparable[N];
        for (int sz = 1; sz < N; sz = sz + sz)
            for (int lo = 0; lo < N - sz;  lo += sz+sz) { // the mid is at maximum at N-2, otherwise you can merge when the right half is empty
                merge(a, lo, lo+sz-1, Math.min(N-1, lo+sz+sz-1));
            }
    }

    private static boolean less(Comparable v, Comparable w) {
        return v.compareTo(w) < 0;
    }

    private static void show(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            StdOut.println(a[i]);
        }
    }

    public static void main(String[] args) {
        String[] a = StdIn.readAllStrings();
        sort(a);
        show(a);
    }
}
