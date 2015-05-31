#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define maxn 1005
#define maxm 40010

const int inf = ~0u >> 1;
struct edge {
	int p, next, val, cost;
	edge() {}
	edge(int a, int b, int c, int d): p(a), next(b), val(c), cost(d){}
} e[maxm];

int st[maxn], d[maxn], pre[maxn];
int tot, n, m, s, t;
bool in[maxn];

void init() {
	tot = 0;
	fill(st, st + n + 1, -1);
}

void add(int p,int q,int val,int cost) {
	e[tot] = edge(q, st[p], val, cost);
	st[p] = tot++;
	e[tot] = edge(p, st[q], 0, -cost);
	st[q] = tot++;
}

int spfa() {
	queue<int> Q;
	fill(d, d + n + 1, inf);
	fill(in, in + n + 1, 0);
	fill(pre, pre + n + 1, -1);
	d[s] = 0;
	Q.push(s);
	in[s] = true;
	while(!Q.empty()) {
		int now = Q.front();
		Q.pop();
		for(int k = st[now];~k;k = e[k].next) {
			if(e[k].val && d[e[k].p] > d[now] + e[k].cost) {
				d[e[k].p] = d[now] + e[k].cost;
				pre[e[k].p] = k;
				if(!in[e[k].p]) {
					Q.push(e[k].p);
                }
			}
		}
	}
	return d[t];
}

int mincost() {
	int flow,cost = 0,now,u;
	while(1) {
		if(spfa() == inf)
			break;
		u = t;
		now = inf;
		while(pre[u] != -1) {
			now = min(now,e[pre[u]].val);
			u = e[pre[u] ^ 1].p;
		}
		u = t;
		while(pre[u] != -1) {
			cost += now * e[pre[u]].cost;
			e[pre[u]].val -= now;
			e[pre[u] ^ 1].val += now;
			u = e[pre[u] ^ 1].p;
		}
	}
	return cost;
}

int main() {
	scanf("%d %d", &n, &m);
	init();
	s = 1;
	t = n;
	for(int i = 0; i < m; i++) {
		int a,b,c;
		scanf("%d %d %d", &a, &b, &c);
		add(a, b, 1, c);
		add(b, a, 1, c);
	}
	int ans = mincost();
	printf("%d\n", ans);
}
