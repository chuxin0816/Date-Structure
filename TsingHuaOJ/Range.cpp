//归并排序+二分查找  
#include <cstdio>
int binary_search(int* arr, int lo, int hi, int e);
void merge(int* a, int lo, int mi, int hi);
void mergesort(int* a, int lo, int hi);
int main() {
  int n, m, a, b, a1, b1;
  scanf("%d%d",&n,&m);
  int arr[n];
  for (int i = 0; i < n; ++i) scanf("%d",&arr[i]);
  mergesort(arr, 0, n);
  while (m--) {
    scanf("%d%d",&a,&b);
    a1 = binary_search(arr, 0, n, a);
    b1 = binary_search(arr, a1 > 0 ? a1 : 0, n, b);
    if (a1 >= 0 && arr[a1] == a) a1--;
    printf("%d\n",b1-a1);
  }
  return 0;
}

int binary_search(int* arr, int lo, int hi, int e) {
  while (hi > lo) {
    int mi = (lo + hi) >> 1;
    (e < arr[mi]) ? hi = mi : lo = mi + 1;
  }
  return --lo;
}

void merge(int* a, int lo, int mi, int hi) {
  int *A = a + lo, *C = a + mi, lb = mi - lo, lc = hi - mi;
  int* B = new int[lb];
  for (int i = 0; i < lb; B[i++] = A[i])
    ;
  for (int i = 0, j = 0, k = 0; j < lb;) {
    if (k >= lc || B[j] <= C[k]) A[i++] = B[j++];
    if (k < lc && C[k] < B[j]) A[i++] = C[k++];
  }
  delete[] B;
}
void mergesort(int* a, int lo, int hi) {
  if (hi - lo < 2) return;
  int mi = (lo + hi) >> 1;
  mergesort(a, lo, mi);
  mergesort(a, mi, hi);
  merge(a, lo, mi, hi);
}