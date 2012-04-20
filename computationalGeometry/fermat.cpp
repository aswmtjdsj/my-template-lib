/*
   多边形的费马点（比较坑爹？精度还是？）
   模拟退火
   */
#include <cstdio>
#include <cmath>
#include <iostream>
struct point {
	double x, y;
	point(){}
	point(double a,double b):x(a),y(b){}
	point operator - (const point p)
	{
		return point(x - p.x,y - p.y);
	}
	double norm()
	{
		return sqrt(x * x + y * y);
	}
};
//求n 边形的费马点(参数p_fermat), 返回最小距离和
double fermat_point(point p[], int n, point& p_fermat) {
	point u, v;
	double step = 0.0, curlen, explen, minlen;
	int i, j, k, idx;
	bool flag;
	//u.x = u.y = v.x = v.y = 0.0;  //point "构造函数"
	for(i = 0; i < n; i++) {//初始化步长和起始点
		step += fabs(p[i].x) + fabs(p[i].y);
		u.x += p[i].x;
		u.y += p[i].y;
	}
	u.x /= n;
	u.y /= n;
	flag = 0;//判断是否曾经更新过
	while(step > 1e-10) {
		for(k = 0; k < 10; step /= 2, k++)
			for(i = -1; i <= 1; i++)//向 3 * 3 九个方向做出试探
				for(j = -1; j <= 1; j++) {
					v.x = u.x + step * i;
					v.y = u.y + step * j;
					curlen = explen = 0.0;
					for(idx = 0; idx < n; idx++) {
						curlen += (u - p[idx]).norm();
						explen += (v - p[idx]).norm();
					}
					if(curlen > explen) {//如果试探成功，即距离减小
						u = v;//则更新点的位置
						minlen = explen;
						flag = 1;
					}
				}
	}
	p_fermat = u;
	return flag ? minlen : curlen;
}

int main() {
	point poly[101], p_fermat;
	double len;
	int n;
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < n; i++)
			scanf("%lf %lf", &poly[i].x, &poly[i].y);
		len = fermat_point(poly, n, p_fermat);
		printf("%d\n", int(len + 0.5));//其实没必要
		//printf("%.0lf\n",len);
	}
	return 0;
}

