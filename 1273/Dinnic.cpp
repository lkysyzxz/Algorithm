#include <iostream>
#include <queue>
#include <string.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int capacity[222][222];
int dep[222];
bool used[222];

bool BFS(int s,int t,int pointCount){
    queue<int> que;
    que.push(s);
    memset(dep,-1,sizeof dep);
    dep[s]=0;
    while(!que.empty()){
        int now = que.front();
        que.pop();
        for(int i = 1;i<=pointCount;i++){
            if(capacity[now][i]>0&&dep[i]==-1){
                dep[i]=dep[now]+1;
                que.push(i);
            }
        }
    }
    return dep[t]!=-1;
}
int DFS(int now, int t, int cnt, int f) {
    if (now == t) {
        return f;
    }
    for (int i = 1; i <= cnt; i++) {
        if (capacity[now][i] > 0 && dep[i]==dep[now]+1) {
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
    int res=0;
    while(BFS(s,t,cnt)){
        int tmp = -1;
        while(tmp!=0){
            tmp = DFS(s,t,cnt,0x3f3f3f3f);
            if(tmp>0){
                res+=tmp;
            }
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