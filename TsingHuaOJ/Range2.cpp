// 前缀和
#include <cstdio>
int arr[10000005];
int main() {
  int n, m, a, x, y;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a);
    arr[a] = 1;
  }
  for (int i = 1; i < 10000005; ++i) arr[i] = arr[i] + arr[i - 1];
  while (m--) {
    scanf("%d%d", &x, &y);
    printf("%d\n", arr[y] - arr[x - 1]);
  }
  return 0;
}