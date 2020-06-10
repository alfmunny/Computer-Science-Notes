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

Least-significant-digit first string srot.

```java
public class LSD {
    pubic staitc void srot(String[] a, int W) {
        int N = a.length;
        int R = 256;
        String[] aux = new String[N];
        for (int d = W-1; d >= 0; d--) {
            int count = new int[R+1];

            for (int i = 0; i < N; i++) {
                count[a[i].charAt(d)+1]++;
            }

            for (int r = 0; r < R; i++) {
                count[r+1] = count[r];
            }

            for (int i = 0; i < N; i++) {
                aux[count[a[i]]++] = a[i];
            }

            for (int i = 0; i < N; i++) {
                a[i] = aux[i];
            }
        }
    }
}
```

## Tries

## Substring Search

## Data Compression
