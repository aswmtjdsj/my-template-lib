#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define see(x) cerr << __LINE__ << " Line :" << #x << ' ' << x << endl
#define sqr(x) ((x) * (x))
#define N 1000
using namespace std;
const double eps = 1e-6;
const double pi = acos(-1.0);
int n;
double r;
struct Point
{
	double x,y;
	Point(){}
	Point(double a,double b)
	{
		x = a;
		y = b;
	}
	double operator *(const Point p)
	{
		return x * p.x + y * p.y;
	}
	double operator ^(const Point p)
	{
		return x * p.y - y * p.x;
	}
	double norm() const
	{
		return sqrt(sqr(x) + sqr(y));
	}
	Point operator -(const Point p)
	{
		return Point(x - p.x,y - p.y);
	}
}p[N + 2];
int comp(const double &a)
{
	if(fabs(a) < eps)
		return 0;
	else if(a > eps)
		return 1;
	else
		return -1;
}
bool cmp1(const Point &a,const Point &b)
{
	return (comp(a.x - b.x) < 0) || (comp(a.x - b.x) == 0 && comp(a.y - b.y) < 0);
}
Point c;
bool cmp2(const Point &a,const Point &b)
{
	double theta1 = atan2((a.y - c.y),(a.x - c.x));
	double theta2 = atan2((b.y - c.y),(b.x - c.x));
	return (comp(theta1 - theta2) < 0) || (comp(theta1 - theta2) == 0 && comp(a.norm() - b.norm()) < 0);
}
double cha(Point a,Point b,Point c)
{
	return (b - c) ^ (a - c);
}
double ans = 0.0;
int now;
Point stack[N + 2];
void convex()
{
	if(n == 0)
		return ;
	stack[0] = p[0];
	now = 0;
	for(int i = 1;i < n;i++)
	{
		while(now >= 2 && comp(cha(p[i],stack[now],stack[now - 1])) <= 0)
		{
			now--;
		}
		now++;
		stack[now] = p[i];
	}
}
int main()
{
	while(scanf("%d %lf",&n,&r) == 2)
	{
		if(n == 0)
		{
			printf("%.3lf\n",0.0);
			continue;
		}
		int mark = 0;
		ans = 0;
		now = 0;
		for(int i = 0;i < n;i++)
		{
			double x,y;
			scanf("%lf %lf",&x,&y);
			p[i].x = x;
			p[i].y = y;
			if(i > 0)
			{
				if(cmp1(p[i],c))
				{
					c = p[i];
					mark = i;
				}
			}
			else
				c = p[0];
		}
		p[mark] = p[0];
		p[0] = c;
		sort(p + 1,p + n,cmp2);
		convex();
		for(int i = 0;i < now;i++)
			ans += (stack[i + 1] - stack[i]).norm();
		ans += (stack[now] - stack[0]).norm();
		cout << floor(0.5 + ans + 2.0 * pi * r) << endl;
	}
}
