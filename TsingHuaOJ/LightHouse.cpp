#include <stdlib.h>
#include <cstdio>
using namespace std;
long cnt = 0;
class point {
 public:
  long x, y;
};
point points[4000010];
int cmp(const void* a, const void* b) {
  return (*(point*)a).x > (*(point*)b).x ? 1 : -1;
}
void merge(point* a, int lo, int mi, int hi) {
  point *A = a + lo, *C = a + mi;
  int lb = mi - lo, lc = hi - mi;
  point* B = new point[lb];
  for (int i = 0; i < lb; B[i++].y = A[i].y)
    ;
  for (int i = 0, j = 0, k = 0; j < lb;) {
    if (k >= lc || B[j].y <= C[k].y) A[i++].y = B[j++].y;
    if (k < lc && C[k].y < B[j].y) A[i++].y = C[k++].y, cnt += lb - j;
  }
  delete[] B;
}
void mergesort(point* a, int lo, int hi) {
  if (hi - lo < 2) return;
  int mi = (lo + hi) >> 1;
  mergesort(a, lo, mi);
  mergesort(a, mi, hi);
  merge(a, lo, mi, hi);
}
int main() {
  long n, total;
  scanf("%ld", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%ld%ld", &points[i].x, &points[i].y);
  }
  qsort(points, n, sizeof(points[0]), cmp);
  mergesort(points, 0, n);
  total = (n * (n - 1)) >> 1;
  printf("%ld\n", total - cnt);
  return 0;
}