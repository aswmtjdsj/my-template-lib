#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define maxn 405
#define maxm 50005
const int inf = 100000;
struct edge
{
	int p,next,val;
	edge(){}
	edge(int a,int b,int c):p(a),next(b),val(c){}
}e[maxm];
int tot,n,N,S,T,flow[maxn],pre[maxn],v[maxn],arc[maxn],d[maxn],cnt[maxn],path[maxn];
void init()
{
	tot = 0;
	n = N + N + 1;
	fill(v,v + n + 1,-1);
	fill(cnt,cnt + n + 1,0);
	fill(d,d + n + 1,0);
	cnt[0] = n + 1;
}
void add(int p,int q,int val)
{
	e[tot] = edge(q,v[p],val);
	v[p] = tot++;
	e[tot] = edge(p,v[q],0);
	v[q] = tot++;
}
int mflow()
{
	int sum,now,i,k,least,loc;
	int s = 0,t = n;
	bool flag;
	for(int i = 0;i <= n;i++)
		arc[i] = v[i];
	for(sum = 0,now = inf,i = s;d[s] < n + 1;)
	{
		flow[i] = now;
		for(flag = false,k = arc[i];~k;k = e[k].next)
		{
			if(e[k].val && d[i] == d[e[k].p] + 1)
			{
				now = min(now,e[k].val);
				pre[e[k].p] = i;
				path[e[k].p] = k;
				arc[i] = k;
				i = e[k].p;
				if(i == t)
				{
					for(sum += now;i != s;i = pre[i])
					{
						e[path[i]].val -= now;
						e[path[i] ^ 1].val += now;
						//cout << "point" << i << endl;
					}
					now = inf;
				}
				flag = true;
				break;
			}
		}
		if(!flag)
		{
			for(least = n + 1,k = v[i];~k;k = e[k].next)
			{
				if(e[k].val && d[e[k].p] < least)
				{
					least = d[e[k].p];
					loc = k;
				}
			}
			cnt[d[i]]--;
			if(!cnt[d[i]])
				break;
			d[i] = least + 1;
			cnt[d[i]]++;
			arc[i] = loc;
			if(i != s)
			{
				i = pre[i];
				now = flow[i];
			}
		}
	}
	return sum;
}
int main()
{
}
