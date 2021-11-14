#include <stdio.h>

static int min(int a, int b) { return (a < b) ? a : b; }
static int max(int a, int b) { return (a > b) ? a : b; }

void build(int *tree, int *arr, int i, int lo, int hi) {
  if (lo == hi) {
    tree[i] = arr[lo];
    return;
  }

  int m = (lo + hi) / 2;
  build(tree, arr, i*2, lo, m);
  build(tree, arr, i*2+1, m+1, hi);
  tree[i] = tree[i*2] + tree[i*2+1];
}

int sum(int *tree, int i, int lo, int hi, int query_lo, int query_hi) {
  if (query_lo > query_hi)
    return 0;
  else if (lo == query_lo && hi == query_hi)
    return tree[i];

  int m = (lo + hi) / 2;
  return sum(tree, i*2, lo, m, query_lo, min(query_hi, m)) + sum(tree, i*2+1, m+1, hi, max(query_lo, m+1), query_hi);
}

void update(int *tree, int i, int lo, int hi, int pos, int new_val) {
  if (lo == hi) {
    tree[i] = new_val;
    return;
  }

  int m = (lo + hi) / 2;

  if (pos <= m)
    update(tree, i*2, lo, m, pos, new_val);
  else
    update(tree, i*2+1, m+1, hi, pos, new_val);

  tree[i] = tree[i*2] + tree[i*2+1];
}
