/*
   circle class and random_shuffle for Minimum Circle Problem
   */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define maxn 1005
#define sqr(x) ((x) * (x))
int n;
const double eps = 1e-8;
int sgn(double x)
{
	return fabs(x) < eps ? 0 : x < -eps ? -1: 1;
}
struct point
{
	double x,y;
	point(){}
	point(double a,double b):x(a),y(b){}
	point operator - (point p){return point(x - p.x,y - p.y);}
	point operator + (point p){return point(x + p.x,y + p.y);}
	double norm(){return sqrt(sqr(x) + sqr(y));}
	double operator * (point p){return x * p.x + y * p.y;}
	point operator * (double a){return point(x * a,y * a);}
	double operator ^ (point p){return x * p.y - y * p.x;}
}p[maxn];
bool line(point a,point b,point c){return sgn((a - b) ^ (a - c)) == 0;}
struct circle
{
	point o;
	double r;
	circle(){}
	circle(point _o,double _r):o(_o),r(_r){}
	circle(point a,point b)
	{
		o = (a + b) * 0.5;
		r = (a - b).norm() * 0.5;
	}
	circle(point a,point b,point c)
	{
		if(sgn((a - b) * (c - b)) == 0)
		{
			o = point((a + c) * 0.5);
			r = (a - c).norm() * 0.5;
		}
		else if(sgn((c - a) * (b - a)) == 0)
		{
			o = point((c + b) * 0.5);
			r = (c - b).norm() * 0.5;
		}
		else if(sgn((a - c) * (b - c)) == 0)
		{
			o = point((a + b) * 0.5);
			r = (a - b).norm() * 0.5;
		}
		else if(sgn((b.x - a.x) * (b.x - c.x)))
		{
			o.y = (((sqr(b.y) - sqr(c.y)) * (b.x - a.x) - (sqr(b.y) - sqr(a.y)) * (b.x - c.x)) + (b.x - c.x) * (b.x - a.x) * (c.x - a.x)) / (2.0 * ((b - a) ^ (b - c)));
			o.x = ((a.y + b.y) * 0.5 - o.y) * (b.y - a.y) / (b.x - a.x) + (a.x + b.x) * 0.5;
			r = (b - o).norm();
		}
		else
		{
			o.x = (((sqr(b.x) - sqr(a.x)) * (b.y - c.y) - (sqr(b.x) - sqr(c.x)) * (b.y - a.y)) + (a.y - c.y) * (b.y - a.y) * (b.y - c.y)) / (2.0 * ((b - a) ^ (b - c)));
			o.y = ((a.x + b.x) * 0.5 - o.x) * (b.x - a.x) / (b.y - a.y) + (a    .y + b.y) * 0.5;
			r = (b - o).norm();
		}
	}
	bool in(point x)
	{
		return sgn((x - o).norm() - r) <= 0;
	}
};
circle g(point q[],int num,point x,point y)
{
	circle now(x,y);
	for(int i = 0;i < num;i++)
		if(!now.in(q[i]) && !line(x,y,q[i]))
			now = circle(x,y,q[i]);
	return now;
}
circle f(point q[],int num,point x)
{
	random_shuffle(q,q + num);
	circle now = circle(q[0],x);
	for(int i = 1;i < num;i++)
		if(!now.in(q[i]))
			now = g(q,i,q[i],x);
	return now;
}
circle mincircle()
{
	circle now;
	random_shuffle(p,p + n);
	now = circle(p[0],p[1]);
	for(int i = 2;i < n;i++)
		if(!now.in(p[i]))
			now = f(p,i,p[i]);
	return now;
}
int main()
{
	while(scanf("%d",&n) == 1 && n)
	{
		double x,y;
		for(int i = 0;i < n;i++)
		{
			scanf("%lf %lf",&x,&y);
			p[i] = point(x,y);
		}
		circle ans = mincircle();
		printf("%lf %lf %lf\n",ans.o.x,ans.o.y,ans.r);
	}
}
