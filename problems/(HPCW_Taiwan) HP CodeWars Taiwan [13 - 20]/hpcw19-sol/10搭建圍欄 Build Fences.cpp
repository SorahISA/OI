
#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;
#define MAXN 100010
#define eps 1e-10

inline double sig(double x) { return (x > eps) - (x < -eps); };

typedef struct Point
{
	double x, y;
	Point() {}
	Point(double _x, double _y) :
		x(_x), y(_y) {}
	bool operator <(const Point &argu) const { return sig(x - argu.x) == 0 ? y < argu.y : x < argu.x; }
	double dis(const Point &argu) const { return sqrt((x - argu.x) * (x - argu.x) + (y - argu.y) * (y - argu.y)); }
	double dis2(const Point &argu) const { return (x - argu.x) * (x - argu.x) + (y - argu.y) * (y - argu.y); }
	double operator ^(const Point &argu) const { return x * argu.y - y * argu.x; }
	double operator *(const Point &argu) const { return x * argu.x + y * argu.y; }
	Point operator -(const Point &argu) const { return Point(x - argu.x, y - argu.y); }
	double len() const { return sqrt(x * x + y * y); }
	void in() { scanf("%lf%lf", &x, &y); }
}Vector;

inline double Cross(const Point &o, const Point &a, const Point &b) { return (a - o) ^ (b - o); }

int ConvexHull(Point p[], Point ch[], int n)
{
	sort(p, p + n);
	int top = 0;
	for (int i = 0; i < n; i++)
	{
		while (top > 1 && Cross(ch[top - 2], ch[top - 1], p[i]) <= 0) top--;
		ch[top++] = p[i];
	}
	int t = top;
	for (int i = n - 2; i >= 0; i--)
	{
		while (top > t && Cross(ch[top - 2], ch[top - 1], p[i]) <= 0) top--;
		ch[top++] = p[i];
	}
	top--;
	return top;
}

void RotatingCalipers(Point p[], int n, double &minp)
{
	int t = 1, l = 1, r = 1;
	minp = 1e15;
	for (int i = 0; i < n; i++)
	{
		// side (p[i], p[i+1])
		while (sig((p[i + 1] - p[i]) ^ (p[t + 1] - p[t])) > 0) t = (t + 1) % n; // topest point
		while (sig((p[i + 1] - p[i]) * (p[r + 1] - p[r])) > 0) r = (r + 1) % n; // most right point
		if (i == 0) l = (r + 1) % n;											// initial most left point
		while (sig((p[i + 1] - p[i]) * (p[l + 1] - p[l])) < 0) l = (l + 1) % n; // most left point
		double d = p[i + 1].dis(p[i]);
		double h = ((p[i + 1] - p[i]) ^ (p[t] - p[i])) / d;						// height of the triangle
		double w = ((p[i + 1] - p[i]) * (p[r] - p[l])) / d;						// project

		minp = min(minp, 2 * (h + w));
	}
}

Point pp[MAXN], ch[MAXN];
int n, c;
double  minp;

void solve()
{
	c = ConvexHull(pp, ch, n); ch[c] = ch[0];
	RotatingCalipers(ch, c,  minp);
	printf("%d\n", int(round(minp)));
}

int main()
{
	if (scanf("%d", &n) && n)
	{
		for (int i = 0; i < n; i++) pp[i].in();
		solve();
	}
	return 0;
}