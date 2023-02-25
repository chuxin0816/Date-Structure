#include "temperature.h"

#include <iostream>
using namespace std;
int n;
struct Node;
struct Station {
  int x, y, temp;
  Station& operator=(const Station& a) {
    x = a.x;
    y = a.y;
    temp = a.temp;
    return *this;
  }
  Node *c, *road = nullptr;
};
Station stations[50010];
struct Node {
  Station date;
  Node *parent, *lc, *rc;
  int height = 0;
  Node(const Station& e, Node* p, Node* lc = nullptr, Node* rc = nullptr)
      : date(e), parent(p), lc(lc), rc(rc){};
  Fctree* fc;
  int fc_size = 0;
};
struct Fctree {
  Station date;
  bool operator<(const Fctree& a) {
    if (date.y < a.date.y)
      return true;
    else if (date.y == a.date.y) {
      if (date.x < a.date.x)
        return true;
      else
        return false;
    } else
      return false;
  }
  bool operator>(const Fctree& a) {
    if (date.y > a.date.y)
      return true;
    else if (date.y == a.date.y) {
      if (date.x > a.date.x)
        return true;
      else
        return false;
    } else
      return false;
  }
};

struct Tree {
  Node *root = nullptr, *hot = nullptr;
  void InsertAsRoot(const Station& e);
  Node*& searchin(Node*& root, const int& e, Node*& hot);
  Node*& search(const int& e);
  Node*& itself(Node* e);
  Node* insert(const Station& e);
  Node* connect34(Node* a, Node* b, Node* c, Node* l1, Node* l2, Node* l3,
                  Node* l4);
  Node* RotateAt(Node* e);
  void search_leaf(Node*& v, int& i, Node* hot);
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
void Merge_y(Fctree*& a, Fctree lc[], Fctree rc[], int n_lc, int n_rc) {
  a = new Fctree[n_lc + n_rc];
  int i = 0, j = 0, k = 0;
  while (i < n_lc && j < n_rc) {
    if (lc < rc)
      a[k++].date = lc[i++].date;
    else
      a[k++].date = rc[j++].date;
  }
  while (i < n_lc) a[k++].date = lc[i++].date;
  while (j < n_rc) a[k++].date = rc[j++].date;
}
void Tree::search_leaf(Node*& v, int& i, Node* hot) {
  if (!v) {
    if (i < n) {
      stations[i].c = v = new Node(stations[i], hot);
      v->fc = new Fctree[1];
      v->fc->date = stations[i++];
      v->fc_size++;
    }
  } else {
    hot = v;
    search_leaf(v->lc, i, hot);
    search_leaf(v->rc, i, hot);
    if (v->lc && v->rc) {
      Merge_y(v, v->lc, v->rc, v->lc->fc_size, v->rc->fc_size);
      v->fc_size = v->lc->fc_size + v->rc->fc_size;
    } else {
      v->fc = new Fctree[v->lc->fc_size];
      for (int i = 0; i < v->lc->fc_size; ++i) v->fc[i].date = v->lc->date;
      v->fc_size = v->lc->fc_size;
    }
  }
}
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
int cnt,road_x1,road_x2;
long long sum;
Station stack_x1[100],stack_x2[100];
void search_x1(Node* root,int x1,int x2,Station stack[],int& road,int lo,int hi){
  int length=hi;
  while(lo<hi){
    int mi=(lo+hi)>>1;
    stations[mi]<x1?lo=mi+1:hi=mi;
  }
  if(lo<length&&stations[lo].x<=x2){
    auto root=stations[lo].c;
    while(root){
      stack[road]=root->date;
      stack[road].c=root;
      if(!isleaf(stack[road].c)) stack[road].road=stack[road-1].c;
      road++;
      root=root->parent;
    }
  }
}
void search_x2(Node* root,int x1,int x2,Station stack[],int& road,int lo,int hi){
  while(lo<hi){
    int mi=(lo+hi)>>1;
    stations[mi]>x2?hi=mi:lo=mi+1;
  }
  lo--;
  if(lo>-1&&stations[lo].x>=x1){
    auto root=stations[lo].c;
    while(root){
      stack[road]=root->date;
      stack[road].c=root;
      if(!isleaf(stack[road].c)) stack[road].road=stack[road].c;
      road++;
      root=root->parent;
    }
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
  Mergesort_x(stations, 0, n);
  int i = 0;
  a.search_leaf(a.root, i, a.hot);
  while (GetQuery(&x1, &y1, &x2, &y2)) {
    Response();
  }
}