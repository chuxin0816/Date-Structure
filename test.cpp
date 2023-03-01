#include "cmath"
#include "cstring"
#include "iostream"

using namespace std;
const int maxn = 1e7;
typedef long long ll;
struct node {
  ll val;
  char str[10];

  friend bool operator<(node a, node b) {
    if (a.val != b.val) return a.val < b.val;
    return strcmp(a.str, b.str) < 0;
  }
} heap[maxn];

int n = 0;

void up(int p) {
  while (p > 1) {
    if (heap[p] < heap[p / 2]) {
      swap(heap[p], heap[p / 2]);
      p /= 2;
    } else
      break;
  }
}

void down(int p) {
  int s = p * 2;
  while (s <= n) {
    if (s < n && heap[s + 1] < heap[s]) s++;
    if (heap[s] < heap[p]) {
      swap(heap[p], heap[s]);
      p = s;
      s *= 2;
    } else
      break;
  }
}

void extract() {
  heap[1] = heap[n--];
  down(1);
}

void insert(node val) {
  heap[++n] = val;
  up(n);
}

int main() {
  //    freopen("in.txt", "r", stdin);
  int a, b;
  node x;
  scanf("%d %d", &a, &b);
  ll p = 1;
  for (int i = 0; i < 32; i++) {
    p *= 2;
  }
  for (int i = 0; i < a; i++) {
    scanf("%lld %s", &x.val, x.str);
    insert(x);
  }
  while (b-- && n >= 1) {
    printf("%s\n", heap[1].str);
    x = heap[1];
    x.val *= 2;
    extract();
    if (x.val < p) {
      insert(x);
    }
  }
  return 0;
}
