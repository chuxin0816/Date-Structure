#include <iostream>
#include <string>
using namespace std;
#define max 100000
int main() {
  string a, b;
  while (cin >> a >> b) {
    bool is_equal = false;
    auto len = a.size();
    if (len == b.size()) {
      for (auto i = 0; i < len; ++i) {
        if (a[i] == b[0]) {
          if (a.substr(i) == b.substr(0, len - i) &&
              a.substr(0, i) == b.substr(len - i)) {
            is_equal = true;
            break;
          }
        }
      }
    }
    if (is_equal)
      cout << "YES\n";
    else
      cout << "NO\n";
  }
}