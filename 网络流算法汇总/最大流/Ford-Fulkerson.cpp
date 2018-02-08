#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int capacity[222][222];
bool used[222];

int DFS(int now, int t, int cnt, int f) {
    if (now == t) {
        return f;
    }
    for (int i = 1; i <= cnt; i++) {
        if (capacity[now][i] > 0 && !used[i]) {
            used[i] = true;
            int delta = DFS(i, t, cnt, min(capacity[now][i], f));
            if (delta > 0) {
                capacity[now][i] -= delta;
                capacity[i][now] += delta;
                return delta;
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t, int cnt) {
    int d = -1;
    int res = 0;
    while (d != 0) {
        memset(used, false, sizeof used);
        d = DFS(s, t, cnt, 0x3f3f3f3f);
        if (d > 0) {
            res += d;
        }
    }
    return res;
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(capacity, 0, sizeof capacity);
        int u, v, c;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &u, &v, &c);
            if (u == v)continue;
            capacity[u][v] += c;
        }
        printf("%d\n", maxFlow(1, m, m));
    }
    return 0;
}