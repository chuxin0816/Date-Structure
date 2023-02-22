#include <cstdio>
#define MAX 4000010
int pre[MAX], post[MAX];
struct treenode {
  treenode *lc, *rc;
  int date;
};

treenode *ProperRebuild(int pre_lo, int pre_hi, int post_lo, int post_hi) {
  treenode *root = new treenode;
  root->date = pre[pre_lo];
  root->lc = root->rc = nullptr;
  if (pre_hi == pre_lo) return root;
  int pos, num_left;
  for (int i = post_lo; i <= post_hi; ++i)
    if (post[i] == pre[pre_lo + 1]) {
      pos = i;
      break;
    }
  num_left = pos - post_lo + 1;
  root->lc = ProperRebuild(pre_lo + 1, pre_lo + num_left, post_lo, pos);
  root->rc = ProperRebuild(pre_lo + num_left + 1, pre_hi, pos + 1, post_hi - 1);
}

void Inordertraverse(treenode *root) {
  if (!root) return;
  Inordertraverse(root->lc);
  ::printf("%d ", root->date);
  Inordertraverse(root->rc);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) ::scanf("%d", &pre[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &post[i]);
  treenode *root = ProperRebuild(0, n - 1, 0, n - 1);
  Inordertraverse(root);
  return 0;
}
