#include <iostream>
using namespace std;
#define maxn 41000
int fc[10];
int cnt[maxn];
void init() {
  fc[1] = 0;
  fc[2] = 1;
  for (int i = 3; i <= 8; ++i) fc[i] = (i - 1) * fc[i - 1];
}
struct Node {
  int a[10]={0}, val;
  int hash() {
    val = 0;
    for (int i = 1; i <= 8; ++i) {
      int x = 0;
      for (int j = i + 1; j <= 8; ++j) {
        if (a[i] > a[j]) x++;
      }
      val += x * fc[9 - i];
    }
    return val;
  }
  void op_A() {
    for (int i = 1; i < 5; ++i) swap(a[i], a[9 - i]);
  }
  void op_B() {
    for (int i = 0; i < 4; ++i) a[i] = a[i + 1];
    a[4] = a[0];
    for (int i = 9; i > 5; --i) a[i] = a[i - 1];
    a[5] = a[9];
  }
  void op_C() {
    a[0] = a[2];
    a[2] = a[3];
    a[3] = a[6];
    a[6] = a[7];
    a[7] = a[0];
  }
};
Node stack[maxn];
void BFS() {
  Node now;
  for (int i = 1; i < 9; ++i) now.a[i] = i;
  int from = 0, to = 0;
  stack[to++] = now;
  cnt[now.hash()] = 1;
  Node op;
  while (from != to) {
    now = stack[from++];
    from %= maxn;
    op = now;
    op.op_A();
    if (!cnt[op.hash()]) {
      cnt[op.val] = cnt[now.val] + 1;
      stack[to++] = op;
      to %= maxn;
    }
    op = now;
    op.op_B();
    if (!cnt[op.hash()]) {
      cnt[op.val] = cnt[now.val] + 1;
      stack[to++] = op;
      to %= maxn;
    }
    op = now;
    op.op_C();
    if (!cnt[op.hash()]) {
      cnt[op.val] = cnt[now.val] + 1;
      stack[to++] = op;
      to %= maxn;
    }
  }
}
int main() {
  init();
  BFS();
  Node x;
  int n;
  cin >> n;
  while (n--) {
    for (int i = 1; i < 9; ++i) cin >> x.a[i];
    cout << cnt[x.hash()] - 1 << endl;
  }
  return 0;
}