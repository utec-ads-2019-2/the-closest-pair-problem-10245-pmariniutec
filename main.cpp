#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

#define N 10010
#define THRESHOLD 10000

struct Point2D {
  double x, y;

  Point2D(double x = 0, double y = 0) : x(x), y(y) { }

  inline const void set() {
	scanf("%lf%lf", &x, &y);
  }

  const bool operator<(const Point2D &other) const {
	return x == other.x ? y < other.y : x < other.x;
  }

  const double squaredDistance(const Point2D &other) const {
	return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
  }
};

int n;
Point2D p[N];

double closest(int l, int r) {
  if(l >= r) return THRESHOLD * THRESHOLD;

  if(l + 1 == r) return p[l].squaredDistance(p[r]);

  int mid = (l + r) >> 1;
  auto minDistance = std::min(closest(l, mid), closest(mid + 1, r));

  std::vector<Point2D> group1, group2;

  for(int i = mid; i >= l && (p[mid].x - p[i].x) < minDistance; --i)
	group1.push_back(p[i]);

  for(int i = mid + 1; i <= r && (p[i].x - p[mid].x) < minDistance; ++i)
	group2.push_back(p[i]);

  for(int i = 0; i <= group1.size() - 1; ++i) {
	for(int j = 0; j <= group2.size() - 1; ++j) {
	  minDistance = std::min(minDistance, group1[i].squaredDistance(group2[j]));
	}
  }

  return minDistance;
}

int main() {
  double ans;

  while(scanf("%d", &n) == 1 && n) {
	for (int i = 1; i <= n; ++i)
	  p[i].set();

	std::sort(p + 1, p + 1 + n);

	ans = sqrt(closest(1, n));

	if(ans >= THRESHOLD)
	  std::cout << "INFINITY";
	else 
	  printf("%.4lf\n", ans);
  }

  return 0;
}
