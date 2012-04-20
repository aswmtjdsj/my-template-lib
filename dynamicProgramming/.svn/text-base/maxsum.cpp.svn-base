/*
   O(N) dp to calculate Maximum Interval Sum
   dp[j] means the Restricted Maximum Interval Sum in all the SubInterval which contains the 'jth' element, namely a[j]
   ans = max(1...n){dp[i]}
   dp[i] = max(dp[i-1] + a[i],a[i])
   if dp[j-1] > 0 then dp[j] = dp[j-1] + a[j], just use the biggest one to add a[j], cause a[j] must be included in dp[j]
   or dp[j-1] < 0 then dp[j] = a[j], apparently
   
   for details, go to http://www.stackpop.org/blog/html/y2011/381_max_interval.html
   */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define maxn 100005
#define MIN (-1005)
int a[maxn],dp[maxn],s[maxn],t[maxn];
int n;
int main()
{
	int cas;
	scanf("%d",&cas);
	for(int k = 1;k <= cas;k++)
	{
		printf("Case %d:\n",k);
		scanf("%d",&n);
		dp[0] = 0;
		s[0] = t[0] = 1;
		int ans = 0,MAX = MIN;
		for(int i = 1;i <= n;i++)
			scanf("%d",&a[i]);
		for(int i = 1;i <= n;i++)
		{
			if(dp[i-1] + a[i] >= a[i])
			{
				dp[i] = dp[i-1] + a[i];
				t[i] = i;
				s[i] = s[i-1];
			}
			else
			{
				dp[i] = a[i];
				s[i] = t[i] = i;
			}
			if(MAX < dp[i])
			{
				ans = i;
				MAX = dp[i];
			}
		}
		printf("%d %d %d\n",dp[ans],s[ans],t[ans]);
	}
}
