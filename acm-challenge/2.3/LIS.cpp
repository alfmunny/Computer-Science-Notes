#include <iostream>
#include <unordered_map>
#include <vector>

#define MAX_N 100

using namespace std;

// input

int a[] = {4, 2, 3, 1, 5, 2, 3, 4, 5, 6};

int dp[MAX_N];

int solve() {
    int res = 0;
    int n = sizeof(a)/sizeof(*a);

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for ( int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        res = max(res, dp[i]);
        }
    }

    return res;
}

int main() {
    int res = solve();
    printf("%d\n", res);
    return 0;
}
