#include <stdio.h>
#include <stdlib.h>
#define MAXN 20

int tree[4*MAXN];
int arr[] = {1, 2, 3, -1};
int length = 4;

int min(int a, int b) { return (a < b) ? a : b; }
int max(int a, int b) { return (a > b) ? a : b; }

void build(int *arr, int i, int lo, int hi) {
  if (lo == hi) {
    tree[i] = arr[lo];
    return;
  }

  int m = (lo + hi) / 2;
  build(arr, i*2, lo, m);
  build(arr, i*2+1, m+1, hi);
  tree[i] = tree[i*2] + tree[i*2+1];
}

int sum(int i, int lo, int hi, int query_lo, int query_hi) {
  if (query_lo > query_hi)
    return 0;
  else if (lo == query_lo && hi == query_hi)
    return tree[i];

  int m = (lo + hi) / 2;
  return sum(i*2, lo, m, query_lo, min(query_hi, m)) + sum(i*2+1, m+1, hi, max(query_lo, m+1), query_hi);
}

void update(int i, int lo, int hi, int pos, int new_val) {
  if (lo == hi) {
    tree[i] = new_val;
    return;
  }

  int m = (lo + hi) / 2;

  if (pos <= m)
    update(i*2, lo, m, pos, new_val);
  else
    update(i*2+1, m+1, hi, pos, new_val);

  tree[i] = tree[i*2] + tree[i*2+1];
}

int main() {
  build(arr, 1, 0, length-1);
  update(1, 0, length-1, 2, 50);
  update(1, 0, length-1, 0, 40);
  printf("Sum: %d\n", sum(1, 0, length-1, 0, 3));

  return 0;
}
