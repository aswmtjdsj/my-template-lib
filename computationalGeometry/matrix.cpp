/*
   by using homogeneous matrix to transform coordinates in 2D and 3D
   including Scaling,Shifting and Rotating
   in 2D,rotation is around arbitrary point
   in 3D,rotation is around arbitrary axis
   */
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int maxn = 10;
int sgn(const double x){return fabs(x) < eps?0:x < -eps?-1:1;}
#define REP(i,x) for(int i = 0;i < x;i ++)
struct matrix
{
	int r,c;
	double v[maxn][maxn];
	matrix(){}
	matrix(int a,int b):r(a),c(b)
	{
		REP(i,r) 
			fill(v[i],v[i]+c,0.0);
		if(r==c)
		{
			REP(i,r)//unit matrix as default matrix
				v[i][i]=1;
		}
	}
	matrix operator * (const matrix p)
	{
		matrix ans(r,p.c);
		REP(i,r)
			REP(j,ans.c)
			{
				double tmp = 0.0;
				REP(k,c)
					tmp += v[i][k] * p.v[k][j];
				ans.v[i][j] = tmp;
			}
		return ans;
	}
};
matrix power(matrix a,int n)
{
	matrix e(a.r,a.c);
	if(n == 0)return e;
	matrix ans = power(a,n/2);
	ans = ans * ans;
	return (n%2)?ans*a:ans;
}
struct dPoint
{
	double x,y;
	dPoint(){}
	dPoint(double a,double b):x(a),y(b){}
	dPoint shift(double dx,double dy)
	{
		matrix tran(3,3),o(3,1);
		o.v[0][0] = x;
		o.v[1][0] = y;
		o.v[2][0] = 1;
		tran.v[0][2]=dx;tran.v[1][2]=dy;
		matrix ans = tran * o;
		return dPoint(ans.v[0][0],ans.v[1][0]);
	}
	dPoint scale(double sx,double sy)
	{
		matrix tran(3,3),o(3,1);
		o.v[0][0] = x;
		o.v[1][0] = y;
		o.v[2][0] = 1;
		tran.v[0][0] = sx;
		tran.v[1][1] = sy;
		matrix ans = tran * o;
		return dPoint(ans.v[0][0],ans.v[1][0]);
	}
	dPoint rotate(dPoint p,double theta)//counter_clockwise rotate
	{//shift , rotate about (0,0) , shift back
		theta = theta / 180.0 * pi;
		matrix tran(3,3),o(3,1),ans(3,1);
		o.v[0][0] = x;
		o.v[1][0] = y;
		o.v[2][0] = 1;
		tran.v[0][0] = tran.v[1][1] = cos(theta);
		tran.v[0][1] = -sin(theta); tran.v[1][0] = sin(theta);
		tran.v[0][2] = -cos(theta) * p.x + sin(theta) * p.y + p.x;
		tran.v[1][2] = -sin(theta) * p.x - cos(theta) * p.y + p.y;
		ans=tran*o;
		return dPoint(ans.v[0][0],ans.v[1][0]);
	}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%lf %lf\n",x,y);}
};
struct tPoint
{
	double x,y,z;
	tPoint(){}
	tPoint(double a,double b,double c):x(a),y(b),z(c){}
	tPoint operator - (const tPoint p){return tPoint(x-p.x,y-p.y,z-p.z);}
	tPoint shift(double dx,double dy,double dz)
	{
		matrix tran(4,4),o(4,1);
		o.v[0][0] = x;
		o.v[1][0] = y;
		o.v[2][0] = z;
		o.v[3][0] = 1;
		tran.v[0][3]=dx;tran.v[1][3]=dy;tran.v[2][3]=dz;
		matrix ans = tran * o;
		return tPoint(ans.v[0][0],ans.v[1][0],ans.v[2][0]);
	}
	tPoint scale(double sx,double sy,double sz)
	{
		matrix tran(4,4),o(4,1);
		o.v[0][0] = x;
		o.v[1][0] = y;
		o.v[2][0] = z;
		o.v[3][0] = 1;
		tran.v[0][0] = sx;
		tran.v[1][1] = sy;
		tran.v[2][2] = sz;
		matrix ans = tran * o;
		return tPoint(ans.v[0][0],ans.v[1][0],ans.v[2][0]);
	}
	tPoint rotate(tPoint,tPoint,double);
	void scan(){scanf("%lf%lf%lf",&x,&y,&z);}
	void print(){printf("%lf %lf %lf\n",x,y,z);}
	double norm2(){return x*x+y*y+z*z;} 
	double norm(){return sqrt(norm2());}
	tPoint unit(){return tPoint(x/norm(),y/norm(),z/norm());}
};
tPoint tZero(0,0,0);
tPoint tPoint::rotate(tPoint a,tPoint b,double theta)
{
	double t = theta / 180.0 * pi;
	matrix tran(4,4),o(4,1),ans(4,1);
	o.v[0][0] = x;
	o.v[1][0] = y;
	o.v[2][0] = z;
	o.v[3][0] = 1;
	tPoint p = b - a;
	double ct = cos(t),st = sin(t);
	p = p.unit();//normalized---------this is the standard handling
	tran.v[0][0] = (1.0 - ct) * p.x * p.x + ct;
	tran.v[0][1] = (1.0 - ct) * p.x * p.y - st * p.z;
	tran.v[0][2] = (1.0 - ct) * p.x * p.z + st * p.y;
	tran.v[1][0] = (1.0 - ct) * p.y * p.x + st * p.z;
	tran.v[1][1] = (1.0 - ct) * p.y * p.y + ct;
	tran.v[1][2] = (1.0 - ct) * p.y * p.z - st * p.x;
	tran.v[2][0] = (1.0 - ct) * p.z * p.x - st * p.y;
	tran.v[2][1] = (1.0 - ct) * p.z * p.y + st * p.x;
	tran.v[2][2] = (1.0 - ct) * p.z * p.z + ct;
	tran.v[0][3] = -tran.v[0][0] * a.x - tran.v[0][1] * a.y - tran.v[0][2] * a.z + a.x;
	tran.v[1][3] = -tran.v[1][0] * a.x - tran.v[1][1] * a.y - tran.v[1][2] * a.z + a.y;
	tran.v[2][3] = -tran.v[2][0] * a.x - tran.v[2][1] * a.y - tran.v[2][2] * a.z + a.z;
	ans = tran * o;
	return tPoint(ans.v[0][0],ans.v[1][0],ans.v[2][0]);
}
int main()
{
	dPoint dp,dp_;
	tPoint tp,tp_;
	double x,y,z;
	puts("2D---------->");
	dp.scan();
	scanf("%lf %lf",&x,&y);
	dp.shift(x,y).print();
	dp.scale(x,y).print();
	dp.rotate(dPoint(x,y),90.0).print();
	puts("3D---------->");
	tp.scan();
	scanf("%lf %lf %lf",&x,&y,&z);
	tp.shift(x,y,z).print();
	tp.scale(x,y,z).print();
	tp.rotate(tPoint(0,0,0),tPoint(0,0,1),90.0).print();
}
