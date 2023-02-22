#include "temperature.h"

#include <iostream>
using namespace std;
struct Station {
  int x, y, temp;
};
Station stations[50010];
struct Node {
  Node *lc, *rc, *parent;
  Station date;
  int height = 0;
  Node(const Station& e, const Node& p, const Node& lc = nullptr,
       const Node& rc = nullptr)
      : date(e), parent(p), lc(lc), rc(rc){};
};
struct Tree {
  Node *root, *hot;
  void InsertAsRoot(const Node& e);
  Node*& searchin(Node*& root, const int& e, Node*& hot);
  Node*& search(const int& e);
  Node* insert(const int& e);
  Node*& fromparentto();
  Node* connect34();
  Node* RotateAt();
  void search_leaf();
  int size = 0;
};
void Tree::InsertAsRoot(const Node& e) {
  root = new Node(e, nullptr);
  size++;
}
NOde*& Tree::searchin(Node*& root, const int& e, Node*& hot) {
  if (!root) return root;
  hot = root;
  return searchin((root->date.x >= e) ? root->lc : root->rc, e, hot);
}
Node*& Tree::search(const int& e) { return searchin(root, e, hot = nullptr); }
bool islchind(Node* e) return (e->parent) && (e == e->parent->lc);
bool isrchind(Node* e) return (e->parent) && (e == e->parent->rc);
int stature(Node* e) return e ? e->height : -1;
void UpdateHeight(Node* e) {
  e->height =
      (stature(e->lc) < stature(e->rc)) ? stature(e->rc) : stature(e->lc) + 1;
}
bool Banlance(Node* e) {
  return (stature(e->lc) - stature(e->rc) < 2) &&
         (stature(e->lc) - stature(e->rc) > -2);
}
bool operate == (const Node& d1, const Node& d2) {
  return d1.x == d2.x && d1.y == d2.y;
}
Node* insert(const station& e) 
int main() {
  int n;
  n = GetNumOfStation();
  if (n == 0) {
    Response(0);
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    int x, y, temp;
    GetStationInfo(i, &stations[i].x, &stations[i].y, &stations[i].temp);
  }
  int x1, x2, y1, y2;
  while (GetQuery(&x1, &y1, &x2, &y2)) {
    Response();
  }
}