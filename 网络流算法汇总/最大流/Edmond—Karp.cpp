#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int capacity[222][222];
int mp[222][222];
int pre[222];
int flow[222];
int src, des;
queue<int> que;

int BFS(int s, int t, int m) {
    while (!que.empty())
        que.pop();
    for (int i = 1; i <= m; i++) {
        pre[i] = -1;
    }
    flow[s] = 0x3f3f3f3f;
    pre[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int now = que.front();
        que.pop();
        if (now == t)
            break;
        for (int i = 1; i <= m; i++) {
            if (i != src && capacity[now][i] > 0 && pre[i] == -1) {
                flow[i] = min(capacity[now][i], flow[now]);
                pre[i] = now;
                que.push(i);
            }
        }
    }
    if (pre[t] == -1)
        return -1;
    else
        return flow[t];
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(capacity, 0, sizeof capacity);
        memset(flow, 0, sizeof flow);
        src = 1;
        des = m;
        int u, v, c;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &u, &v, &c);
            if(u==v)continue;
            capacity[u][v] += c;
        }
        int ans = 0;
        int increasement = 0;
        while ((increasement = BFS(src, des, m)) != -1) {
            int k = des;
            while (k != src) {
                int last = pre[k];
                capacity[last][k] -= increasement;
                capacity[k][last] += increasement;
                k = last;
            }
            ans += increasement;
        }
        printf("%d\n", ans);
    }
    return 0;
}