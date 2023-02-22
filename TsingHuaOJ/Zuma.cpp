#include <iostream>
#include <string>
using namespace std;
int main() {
  int n, position, cnt, i;
  string qiu;
  string a;
  getline(cin,a);
  cin >> n;
  while (n--) {
    bool iserased = true;
    cin >> position >> qiu;
    a.insert(position, qiu);
    while (iserased) {
      cnt = 1;
      iserased = false;
      for (i = 1; i < a.size(); ++i) {
        if (a[i] == a[i - 1])
          cnt++;
        else {
          if (cnt > 2) {
            a.erase(i - cnt, cnt);
            iserased = true;
          }
          cnt = 1;
        }
      }
      if (cnt > 2) {
        a.erase(i - cnt, cnt);
        iserased = true;
      }
    }
    if (a.empty())
      cout << "-\n";
    else
      cout << a << endl;
  }
  return 0;
}