void build(int *tree, int (*op)(int,int), int *arr, int i, int lo, int hi);
int query(int *tree, int (*op)(int,int), int i, int lo, int hi, int query_lo, int query_hi);
void update(int *tree, int (*op)(int,int), int i, int lo, int hi, int pos, int new_val);

int min(int, int);
int max(int, int);
int sum(int, int);
