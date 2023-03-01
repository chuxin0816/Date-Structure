#include <cstdio>//cin,cout太慢会超时
#include <cstring>
#include <iostream>
using namespace std;
#define maxn 4000000
#define max 4294967296
struct Node {
  long long priority;
  char name[10];
  bool operator<(const Node& x) {
    if (priority != x.priority) return priority < x.priority;
    return strcmp(name, x.name) < 0;
  }
};
Node heap[maxn];
int _size;
void heapify_up(int rank) {
  if (rank == 0) return;
  int parent = (rank - 1) / 2;
  if (heap[rank] < heap[parent]) {
    swap(heap[rank], heap[parent]);
    heapify_up(parent);
  }
}
void heapify_down(int rank) {
  int lc = rank * 2 + 1, rc = rank * 2 + 2, min_rank = rank;
  if (lc < _size && heap[lc] < heap[min_rank]) min_rank = lc;
  if (rc < _size && heap[rc] < heap[min_rank]) min_rank = rc;
  if (min_rank != rank) {
    swap(heap[rank], heap[min_rank]);
    heapify_down(min_rank);
  }
}
void insert(Node x) {
  heap[_size++] = x;
  heapify_up(_size - 1);
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  Node x;
  while (n--) {
    scanf("%lld%s", &x.priority, x.name);
    insert(x);
  }
  while (m-- && _size) {
    printf("%s\n", heap[0].name);
    heap[0].priority *= 2;
    x = heap[0];
    heap[0] = heap[--_size];
    heapify_down(0);
    if (x.priority < max) insert(x);
  }
  return 0;
}