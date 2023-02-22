#include <iostream>
using namespace std;
#define MAX 1600001
int a[MAX], b[MAX], s[MAX], result[2 * MAX];
int main() {
  int n, m, key = 1, tops = 0, topr = 0;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> b[i];
  for (int i = 1, j = 0; i <= n; ++i) {
    if (tops < m) {
      s[tops++] = i;
      result[topr++] = 1;  // push
    } else {
      key = 0;
      break;
    }
    while (tops > 0 && s[tops - 1] == b[j]) {
      tops--;
      j++;
      result[topr++] = 0;  // pop
    }
  }
  if (tops > 0 || key == 0)
    cout << "No\n";
  else {
    for (int i = 0; i < topr; ++i) {
      if (result[i] == 1)
        cout << "push\n";
      else
        cout << "pop\n";
    }
  }
  return 0;
}
