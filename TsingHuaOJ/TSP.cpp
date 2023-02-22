#include <cstdio>

#define MAX 1000001
#define GetMax(a, b) a > b ? a : b
struct NNode {
  int sub;
  NNode *succ;
};
struct PNode {
  int in, len;
  NNode *next;
};
int n, m, total, top, stack[MAX];
PNode village[MAX];
NNode *t;

void TPsort() {
  for (int i = 1; i <= n; ++i) {
    if (!village[i].in) stack[++top] = i;
  }
  while (top) {
    int v = stack[top--];
    for (NNode *p = village[v].next; p; p = p->succ) {
      if (!--village[p->sub].in) stack[++top] = p->sub;
      village[p->sub].len = GetMax(village[p->sub].len, village[v].len + 1);
      total = GetMax(total, village[p->sub].len);
    }
  }
}

int main() {
  int a, b;
  scanf("%d%d", &n, &m);
  while (m--) {
    scanf("%d%d", &a, &b);
    village[b].in++;
    t = new NNode;
    t->sub = b;
    t->succ = village[a].next;
    village[a].next = t;
  }
  TPsort();
  printf("%d", total + 1);
  return 0;
}