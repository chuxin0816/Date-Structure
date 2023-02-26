#include "temperature.h"
#define maxn 50000
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
Station stations[maxn];
struct Node {
  Station date;
  Node *parent, *lc, *rc;
  int height = 0;
  Fctree* fc;
  int fc_size = 0;
  Node(const Station& e, Node* p, Node* lc = nullptr, Node* rc = nullptr,
       Fctree* fc = nullptr)
      : date(e), parent(p), lc(lc), rc(rc), fc(fc){};
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
  return ((stature(e->lc) - stature(e->rc) < 2) &&
          (stature(e->lc) - stature(e->rc) > -2));
}
bool operator==(const Station& d1, const Station& d2) {
  return (d1.x == d2.x && d1.y == d2.y);
}
Node*& Tree::itself(Node* e) {
  if (e->parent)
    return islchind(e) ? e->parent->lc : e->parent->rc;
  else
    return root;
}

Node* Tree::insert(const Station& e) {
  Node*& x = search(e.x);
  Node* xx = x = new Node(e, hot);
  for (Node* g = hot; g; g = g->parent) {
    if (!Banlance(g)) {
      auto& temp = itself(g);
      temp = RotateAt(Tallerchild(Tallerchild(g)));
      break;
    } else
      UpdateHeight(g);
  }
  size++;
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
      return connect34(g, e, p, g->lc, e->lc, e->rc, p->rc);
    } else {
      p->parent = g->parent;
      return connect34(g, p, e, g->lc, p->lc, e->lc, e->rc);
    }
  }
}
bool isleaf(const Node* e) { return e && !e->lc && !e->rc; }
void Merge_y(Fctree*& a, Fctree lc[], Fctree rc[], int n_lc, int n_rc) {
  a = new Fctree[n_lc + n_rc];
  int i = 0, j = 0, k = 0;
  while (i < n_lc && j < n_rc) {
    if (lc[i] < rc[j])
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
      Merge_y(v->fc, v->lc->fc, v->rc->fc, v->lc->fc_size, v->rc->fc_size);
      v->fc_size = v->lc->fc_size + v->rc->fc_size;
    } else {
      v->fc = new Fctree[v->lc->fc_size];
      for (int i = 0; i < v->lc->fc_size; ++i)
        v->fc[i].date = v->lc->fc[i].date;
      v->fc_size = v->lc->fc_size;
    }
  }
}
void Merge_x(Station stations[], int lo, int mi, int hi) {
  Station* a = new Station[mi - lo];
  int i = 0, t = mi - lo;
  for (int i = 0; i < mi - lo; ++i) a[i] = stations[lo + i];
  while (i < t && mi < hi) {
    if (a[i].x < stations[mi].x)
      stations[lo++] = a[i++];
    else if ((a[i].x = stations[mi].x) && (a[i].y < stations[mi].y))
      stations[lo++] = a[i++];
    else
      stations[lo++] = stations[mi++];
  }
  while (i < t) stations[lo++] = a[i++];
  delete[] a;
}
void Mergesort_x(Station stations[], int lo, int hi) {
  if (hi - lo > 1) {
    int mi = (lo + hi) >> 1;
    Mergesort_x(stations, lo, mi);
    Mergesort_x(stations, mi, hi);
    Merge_x(stations, lo, mi, hi);
  } else
    return;
}
int cnt, road_x1, road_x2;
long long int sum = 0;
Station stack_x1[100], stack_x2[100];
void search_x1(Node* root, int x1, int x2, Station stack[], int& road, int lo,
               int hi) {
  int length = hi;
  while (lo < hi) {
    int mi = (lo + hi) >> 1;
    stations[mi].x < x1 ? lo = mi + 1 : hi = mi;
  }
  if (lo < length && stations[lo].x <= x2) {
    auto root = stations[lo].c;
    while (root) {
      stack[road] = root->date;
      stack[road].c = root;
      if (!isleaf(stack[road].c)) stack[road].road = stack[road - 1].c;
      road++;
      root = root->parent;
    }
  }
}
void search_x2(Node* root, int x1, int x2, Station stack[], int& road, int lo,
               int hi) {
  while (lo < hi) {
    int mi = (lo + hi) >> 1;
    stations[mi].x > x2 ? hi = mi : lo = mi + 1;
  }
  lo--;
  if (lo > -1 && stations[lo].x >= x1) {
    auto root = stations[lo].c;
    while (root) {
      stack[road] = root->date;
      stack[road].c = root;
      if (!isleaf(stack[road].c)) stack[road].road = stack[road - 1].c;
      road++;
      root = root->parent;
    }
  }
}
void common_node() {
  while (road_x1 > 0 && road_x2 > 0 &&
         stack_x1[--road_x1] == stack_x2[--road_x2])
    ;
}
void search_y(Node* root, int lo, int hi, int y1, int y2) {
  while (lo < hi) {
    int mi = (lo + hi) >> 1;
    y1 <= root->fc[mi].date.y ? hi = mi : lo = mi + 1;
  }
  while (lo < root->fc_size && root->fc[lo].date.y <= y2) {
    sum += root->fc[lo].date.temp;
    cnt++;
    lo++;
  }
}
void Travel(int x1, int x2, int y1, int y2) {
  while (road_x1 >= 0) {
    auto rc = stack_x1[road_x1].c->rc;
    auto lc = stack_x1[road_x1].c->lc;
    auto road = stack_x1[road_x1].road;
    if (rc && rc != road) search_y(rc, 0, rc->fc_size, y1, y2);
    road_x1--;
  }
  auto now = stack_x1[0].c;
  if (now->date.x >= x1 && now->date.x <= x2 && now->date.y >= y1 &&
      now->date.y <= y2) {
    sum += now->date.temp;
    cnt++;
  }
  while (road_x2 >= 0) {
    auto rc = stack_x2[road_x2].c->rc;
    auto lc = stack_x2[road_x2].c->lc;
    auto road = stack_x2[road_x2].road;
    if (lc && lc != road) search_y(lc, 0, lc->fc_size, y1, y2);
    road_x2--;
  }
  now = stack_x2[0].c;
  if (now->date.x >= x1 && now->date.x <= x2 && now->date.y >= y1 &&
      now->date.y <= y2) {
    sum += now->date.temp;
    cnt++;
  }
}
int main() {
  n = GetNumOfStation();
  if (n == 0) {
    Response(0);
    return 0;
  }
  Tree a;
  for (int i = 0; i < n; ++i)
    GetStationInfo(i, &stations[i].x, &stations[i].y, &stations[i].temp);
  a.InsertAsRoot(stations[0]);
  for (int i = 1; i < n; ++i) a.insert(stations[i]);
  Mergesort_x(stations, 0, n);
  int i = 0;
  a.search_leaf(a.root, i, a.hot);
  int x1, x2, y1, y2;
  while (GetQuery(&x1, &y1, &x2, &y2)) {
    search_x1(a.root, x1, x2, stack_x1, road_x1, 0, n);
    search_x2(a.root, x1, x2, stack_x2, road_x2, 0, n);
    int road1 = road_x1, road2 = road_x2;
    if (road_x1 && road_x2) {
      common_node();
      Travel(x1, x2, y1, y2);
      if (cnt)
        Response(sum / cnt);
      else
        Response(0);
    } else
      Response(0);
    for (int i = 0; i < road1; ++i) {
      stack_x1[i].c = stack_x1[i].road = nullptr;
      stack_x1[i].x = stack_x1[i].y = stack_x1[i].temp = 0;
    }
    for (int i = 0; i < road2; ++i) {
      stack_x2[i].c = stack_x1[i].road = nullptr;
      stack_x2[i].x = stack_x2[i].y = stack_x2[i].temp = 0;
    }
    road_x1 = road_x2 = sum = cnt = 0;
  }
  return 0;
}