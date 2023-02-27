#include <iostream>
#include <string>
#define maxn 300000
using namespace std;
int hashing(const string& a) {
  int hashval = 0;
  for (auto e : a) hashval = (e + hashval * 31) % maxn;
  return hashval;
}
int list[maxn];
string ans[maxn];
int main() {
  int n;
  string str;
  cin >> n;
  while (n--) {
    cin >> str;
    int pos = hashing(str);
    while (list[pos] && str != ans[pos]) pos = (pos + 1) % maxn;
    ans[pos] = str;
    if (list[pos] == 1) cout << str << endl;
    list[pos]++;
  }
  return 0;
}