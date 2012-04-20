#include<iostream>
#include<iomanip>
#include<cstdio>
#include<complex>
#include<algorithm>
#include<cmath>
using namespace std;
const double inf=1e-10;
const int Max=60010;
typedef complex<double> Point;
inline int dbcmp(double tp){return tp<-inf?-1:tp>inf;}
double operator^(Point a,Point b)
{return imag(conj(a)*b);}
struct Line{
	Point a,b;
	double angle;
	Line(){}
	Line(Point a,Point b):a(a),b(b){angle=arg(a-b);}
};
bool operator<(Line p,Line l){
	return dbcmp(p.angle-l.angle)<0||
		(dbcmp(p.angle-l.angle)==0&&dbcmp(p.b-p.a^l.b-p.a)<0);
}

Point operator*(const Line& u,const Line&v)
{
	Point tp=u.a;
	double fz=u.a-v.a^v.b-v.a;
	double fm=u.a-u.b^v.b-v.a;
	return tp+(u.b-u.a)*fz/fm;
}
bool onleft(Point p,Line u)
{
	return dbcmp(p-u.a^u.b-u.a)<=0;
}
bool uniquecmp(Line u,Line v)
{
	return dbcmp(u.angle-v.angle)==0;
}
bool iter(Point p,Point q)
{
	return dbcmp(real(p) - real(q)) < 0 || (dbcmp(real(p) - real(q)) == 0 && dbcmp(imag(p) - imag(q)) < 0);
}
Point p[Max];
Line l[Max];
int e[Max];//line的下标
int get_kernel(Line *l,int lsz,Point *p )
{
	int eb=0,ee=2,pb=0,pe=1;
	sort(l,l+lsz);
	p[lsz]=p[0];
	lsz=distance(l,unique(l,l+lsz,uniquecmp));
	e[0]=0;e[1]=1;
	p[0]=l[0]*l[1];
	for(int i=2;i<lsz;i++){
		while(pb!=pe&&!onleft(p[pe-1],l[i]))pe--,ee--;
		while(pb!=pe&&!onleft(p[pb],l[i]))pb++,eb++;
		p[pe++]=l[i]*l[e[ee-1]];
		e[ee++]=i;
	}
	while(pb!=pe&&!onleft(p[pe-1],l[e[eb]]))pe--,ee--;
	//这个循环好像是没有用的。。
	while(pb!=pe&&!onleft(p[pb],l[e[ee-1]]))pb++,eb++;
	p[pe++]=l[e[pb]]*l[e[ee-1]];
	int psz=pe-pb;
	for(int i=0;pb!=pe;i++)p[i]=p[pb++];
	return psz;//点的个数
}
bool uniqueccc(Point p,Point q)
{
	return  dbcmp(real(p)-real(q)) == 0 && dbcmp(imag(p)-imag(q))==0;
}
void gao()
{
	// freopen("1.txt","r",stdin);
	int n;int lsz=0;
	scanf("%d",&n);
	double x,y;
	for(int i=0;i<n;i++)
	{
		scanf("%lf%lf",&x,&y);
		l[lsz++]=Line(Point(0,x),Point(1,x+y));
	}
	l[lsz++]=Line(Point(0,0),Point(1,0));
	l[lsz++]=Line(Point(1e22,0),Point(1e22,1));
	l[lsz++]=Line(Point(1,1e22),Point(0,1e22));
	l[lsz++]=Line(Point(0,1e22),Point(0,0));
	int psz=get_kernel(l,lsz,p);
	sort(p,p + psz,iter);//delete the duplicate points
	psz = distance(p,unique(p,p + psz,uniqueccc));
	printf("%d\n",psz-2);
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int i = 0;i < t;i++)
		gao();
}
