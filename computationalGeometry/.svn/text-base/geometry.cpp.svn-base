#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <cctype>
#include <map>
#include <queue>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>
#include <stack>
using namespace std;
#define sqr(x) ((x) * (x))
#define NMAX 1000
#define FOR(i,n) for(int (i) = 1;(i) <= (n);(i)++)
#define FF(i,a,b) for(int (i) = a;(i) <= (b);(i)++)
const double eps = 1e-8;
const double pi = acos(-1.0);
//D-Plane Point declaration
int ok(const double &a)
{
	if(fabs(a) < eps)
		return 0;
	else if(a > eps)
		return 1;
	else
		return -1;
}
struct DPoint
{
	double x,y;
	DPoint(){}
	DPoint(double _x,double _y):x(_x),y(_y){}
	double norm()
	{
		return sqrt(x * x + y * y);
	}
};
DPoint operator -(const DPoint &p,const DPoint &q)
{
	return DPoint(p.x - q.x,p.y - q.y);
}
DPoint operator +(const DPoint &p,const DPoint &q)
{
	return DPoint(p.x + q.x,p.y + q.y);
}
double operator *(const DPoint &p,const DPoint &q)
{
	return p.x * q.x + p.y * q.y;
}
double operator ^(const DPoint &p,const DPoint &q)
{
	return p.x * q.y - p.y * q.x;
}
double multi(DPoint a,DPoint b,DPoint o)
{
	return (a - o) ^ (b - o);
}
double scalar(DPoint a,DPoint b,DPoint o)
{
	return (a - o) * (b - o);
}
bool operator ==(const DPoint p,const DPoint q)
{
	return ok(p.x - q.x) == 0 && ok(p.y - q.y) == 0;
}
DPoint c;//graham scan 's base point
//sort by y then x
bool cmpxy(DPoint a,DPoint b)
{
	return ok(a.y - b.y) < 0 || (ok(a.y - b.y) == 0 && ok(a.x - b.x) < 0);
}
//sort by polar angle
bool cmptheta(const DPoint &a,const DPoint &b)
{
	DPoint temp1 = a - c,temp2 = b - c;
	return ok(temp1 ^ temp2) < 0 || (ok(temp1 ^ temp2) == 0 && ok(temp1.norm() - temp2.norm()) < 0);
}
struct Circle
{
	DPoint o;
	double r;
	Circle(){}
	Circle(DPoint _o,double _r):o(_o),r(_r){}
};
struct Poly
{
	DPoint vertex[NMAX];
	DPoint point[NMAX];
	int tot,N;
	//initialization
	void init(int _N)
	{
		N = _N;
		int mark = 0;
		for(int i = 0;i < N;i++)
		{
			double a,b;
			scanf("%lf %lf",&a,&b);
			point[i] = DPoint(a,b);
			if(!i)
				c = point[i];
			else
			{
				if(cmpxy(point[i],c))
				{
					c = point[i];
					mark = i;
				}
			}
		}
		point[mark] = point[0];
		point[0] = c;
		sort(point + 1,point + N,cmptheta);
		scan();
	}
	//graham scan
	void scan()
	{
	}
	//rotating callipers
	double rc()
	{
	}
}poly;
struct DLine
{
	DPoint a,b;
	DLine(){}
	DLine(DPoint _a,DPoint _b):a(_a),b(_b){}
};
typedef DLine DSeg;
//the distance between point and line
double DPointToLine(DPoint p,DLine l)
{
	return multi(l.a,l.b,p) / (l.a - l.b).norm();
}
//the distance between point and segment
int main()
{
}
