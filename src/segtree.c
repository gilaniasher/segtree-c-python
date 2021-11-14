#include <stdio.h>
#include <limits.h>

int min(int a, int b) { return (a < b) ? a : b; }
int max(int a, int b) { return (a > b) ? a : b; }
int sum(int a, int b) { return a + b; }

void build(int *tree, int (*op)(int,int), int *arr, int i, int lo, int hi) {
  if (lo == hi) {
    tree[i] = arr[lo];
    return;
  }

  int m = (lo + hi) / 2;
  build(tree, op, arr, i*2, lo, m);
  build(tree, op, arr, i*2+1, m+1, hi);
  tree[i] = op(tree[i*2], tree[i*2+1]);
}

int query(int *tree, int (*op)(int,int), int i, int lo, int hi, int query_lo, int query_hi) {
  if (query_lo > query_hi) {
    if (op == min) return INT_MAX;
    else if (op == max) return INT_MIN;
    else if (op == sum) return 0;
  } else if (lo == query_lo && hi == query_hi)
    return tree[i];

  int m = (lo + hi) / 2;
  int left = query(tree, op, i*2, lo, m, query_lo, min(query_hi, m));
  int right = query(tree, op, i*2+1, m+1, hi, max(query_lo, m+1), query_hi);
  return op(left, right);
}

void update(int *tree, int (*op)(int,int), int i, int lo, int hi, int pos, int new_val) {
  if (lo == hi) {
    tree[i] = new_val;
    return;
  }

  int m = (lo + hi) / 2;

  if (pos <= m)
    update(tree, op, i*2, lo, m, pos, new_val);
  else
    update(tree, op, i*2+1, m+1, hi, pos, new_val);

  tree[i] = op(tree[i*2], tree[i*2+1]);
}
