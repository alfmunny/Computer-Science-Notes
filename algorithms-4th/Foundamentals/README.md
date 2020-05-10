# Foundamentals


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
