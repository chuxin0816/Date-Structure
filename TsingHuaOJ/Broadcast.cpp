#include <iostream>
using namespace std;
int cnt[10010], quene[10010], adjList[10010][5005], color[10010];
int main() {
  int n, m, a, b;
  cin >> n >> m;
  while (m--) {
    cin >> a >> b;
    adjList[a][++cnt[a]] = b;
    adjList[b][++cnt[b]] = a;
  }
  for (int i = 1; i <= n; ++i) {
    if (color[i]) continue;
    color[i] = 1;
    int head = -1, tail = -1;
    quene[++tail] = i;
    while (head != tail) {
      int cur = quene[++head];
      for (int j = 1; j <= cnt[cur]; ++j) {
        int next = adjList[cur][j];
        if (!color[next]) {
          color[next] = 0 - color[cur];
          quene[++tail] = next;
        } else if (color[cur] + color[next] != 0) {
          cout << "-1\n";
          return 0;
        }
      }
    }
  }
  cout << "1\n";
  return 0;
}