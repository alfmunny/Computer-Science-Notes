#include <iostream>
#include <unordered_map>
#include <vector>

#define MAX_w 100
#define MAX_v 100

#define MAX_N 100
#define MAX_W 100

using namespace std;

int n, W;
int w[MAX_w], v[MAX_v];

// recursive without dp
// pick part smaller then j(weight) from the i-th(index) item.    
int rec(int i, int j) {
    int res;

    if (i == n) {
        // the last item
        res = 0;
    } else if (w[i] > j) {
        // can't pick up the item
        res = rec(i+1, j);
    } else {
        // two option, pick or do not pick
        res = max(rec(i+1, j), rec(i+1, j - w[i]) + v[i]);
    }
    return res;
}

void solve() {
    printf("%d\n", rec(0, W));
}

// recursive with dp
int dp[MAX_N + 1][MAX_W + 1];

int rec_dp(int i, int j) {
    int res;
    if (dp[i][j] >= 0) return dp[i][j];

    if (i == n) {
        // the last item
        res = 0;
    } else if (w[i] > j) {
        // can't pick up the item
        res = rec(i+1, j);
    } else {
        // two option, pick or do not pick
        res = max(rec(i+1, j), rec(i+1, j - w[i]) + v[i]);
    }

    return res;
}

void solve_dp() {
    memset(dp, -1, sizeof(dp));
    printf("%d\n", rec(0, W));
}

void solve_pure_dp() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= W; j++) {
            if (j < w[i]) {
                dp[i+1][j] = dp[i][j];
            } else {
                dp[i+1][j] = max(dp[i][j], dp[i][j - w[i]] + v[i]);
            }
        }
    }
    printf("%d\n", dp[n][W]);

    
}

int main() {

    n = 4;
    W = 5;

    w[0] = 2; 
    w[1] = 1; 
    w[2] = 3; 
    w[3] = 2; 
    
    v[0] = 3; 
    v[1] = 2; 
    v[2] = 4; 
    v[3] = 2; 
    solve_pure_dp();
    return 0;
}
