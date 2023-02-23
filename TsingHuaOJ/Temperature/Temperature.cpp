#include "temperature.h"

#include <iostream>
using namespace std;
struct Station {
  int x, y, temp;
};
Station stations[50010];
struct Node {
  Station date;
  Node *parent, *lc, *rc;
  int height = 0;
  Node(const Station& e, Node* p, Node* lc = nullptr, Node* rc = nullptr)
      : date(e), parent(p), lc(lc), rc(rc){};
};
struct Tree {
  Node *root, *hot;
  void InsertAsRoot(const Station& e);
  Node*& searchin(Node*& root, const int& e, Node*& hot);
  Node*& search(const int& e);
  Node*& itself(Node* e);
  Node* insert(const Station& e);
  Node* connect34(Node* a, Node* b, Node* c, Node* l1, Node* l2, Node* l3,
                  Node* l4);
  Node* RotateAt(Node* e);
  void search_leaf();
  int size = 0;
};
void Tree::InsertAsRoot(const Station& e) {
  root = new Node(e, nullptr);
  size++;
}
Node*& Tree::searchin(Node*& root, const int& e, Node*& hot) {
  if (!root) return root;
  hot = root;
  return searchin((root->date.x >= e) ? root->lc : root->rc, e, hot);
}
Node*& Tree::search(const int& e) { return searchin(root, e, hot = nullptr); }
bool islchind(Node* e) { return e->parent && (e == e->parent->lc); }
bool isrchind(Node* e) { return e->parent && (e == e->parent->rc); }
int stature(Node* e) { return e ? e->height : -1; }
Node* Tallerchild(Node* e) {
  return (stature(e->lc) > stature(e->rc))   ? e->lc
         : (stature(e->lc) < stature(e->rc)) ? e->rc
         : islchind(e)                       ? e->lc
                                             : e->rc;
}
void UpdateHeight(Node* e) {
  e->height = (stature(e->lc) < stature(e->rc)) ? stature(e->rc) + 1
                                                : stature(e->lc) + 1;
}
bool Banlance(Node* e) {
  return (stature(e->lc) - stature(e->rc) < 2) &&
         (stature(e->lc) - stature(e->rc) > -2);
}
bool operator==(const Station& d1, const Station& d2) {
  return d1.x == d2.x && d1.y == d2.y;
}
Node*& Tree::itself(Node* e) {
  if (e->parent)
    return islchind(e) ? e->parent->lc : e->parent->rc;
  else
    return root;
}

Node* Tree::insert(const Station& e) {
  Node** x = search(e.x);
  Node* xx = x = new Node(e, hot);
  for (Node* g = hot; g; g = g->parent) {
    if (!Banlance(g)) {
      Node*& temp = itself(g);
      temp = RotateAt(Tallerchild(Tallerchild(g)));
      break;
    } else
      UpdateHeight(g);
  }
  return xx;
}
Node* Tree::connect34(Node* a, Node* b, Node* c, Node* l1, Node* l2, Node* l3,
                      Node* l4) {
  a->lc = l1;
  if (l1) l1->parent = a;
  a->rc = l2;
  if (l2) l2->parent = a;
  UpdateHeight(a);
  c->lc = l3;
  if (l3) l3->parent = c;
  c->rc = l4;
  if (l4) l4->parent = c;
  UpdateHeight(c);
  b->lc = a;
  b->rc = c;
  a->parent = b;
  c->parent = b;
  UpdateHeight(b);
  return b;
}
Node* Tree::RotateAt(Node* e) {
  Node* p = e->parent;
  Node* g = p->parent;
  if (islchind(p)) {
    if (islchind(e)) {
      p->parent = g->parent;
      return connect34(e, p, g, e->lc, e->rc, p->rc, g->rc);
    } else {
      e->parent = g->parent;
      return connect34(p, e, g, p->lc, e->lc, e->rc, g->rc);
    }
  } else {
    if (islchind(e)) {
      e->parent = g->parent;
      connect34(g, e, p, g->lc, e->lc, e->rc, p->rc);
    } else {
      p->parent = g->parent;
      connect34(g, p, e, g->lc, p->lc, e->lc, e->rc);
    }
  }
}
bool isleaf(const Node* e) { return e && !e->lc && !e->rc; }
void Merge_x(Station stations[], int lo, int mi, int hi) {
  Station* a = new Station[mi - lo];
  for (int i = 0; i < mi - lo; ++i) a[i] = stations[lo + i];
  int i = 0, t = mi - lo;
  while (i < t && mi < hi) {
    if (a[i].x < stations[mi].x)
      stations[lo++] = a[i++];
    else if ((a[i].x = stations[mi].x) && (a[i].y < stations[mi].y))
      stations[lo++] = a[i++];
    else
      station[lo++] = stations[mi++];
  }
  while (i < t) stations[lo++] = a[i++];
  delete[] a;
}
void Mergesort_x(Station stations[], int lo, int hi) {
  if (hi - lo < 2)
    return;
  else {
    int m = (lo + hi) >> 1;
    Mergesort_x(stations, lo, mi);
    Mergesort_x(stations, mi, hi);
    Merge_x(stations, lo, mi, hi);
  }
}
int main() {
  int n;
  n = GetNumOfStation();
  if (n == 0) {
    Response(0);
    return 0;
  }
  Tree a;
  for (int i = 0; i < n; ++i) {
    int x, y, temp;
    GetStationInfo(i, &stations[i].x, &stations[i].y, &stations[i].temp);
  }
  a.InsertAsRoot(stations[0]);
  for (int i = 1; i < n; ++i) a.insert(stations[i]);
  Mergesort_x(stations,0,n);
  while (GetQuery(&x1, &y1, &x2, &y2)) {
    Response();
  }
}