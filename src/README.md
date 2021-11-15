# Segment Tree written in C as a Python Module
This is a [Segment Tree](https://en.wikipedia.org/wiki/Segment_tree) written in C, made available as a Python package. 

It supports basic min/max/sum queries which all happen in log(n) time.
It also supports update queries in log(n) time.

## Usage Examples
```
> from segtree import Segtree
> obj = Segtree([1, 2, 3, 4, 5], 'sum') # Accepted types: 'sum', 'min', 'max
> obj.sum(0, 3)                         # Gets range sum in log(n) time
> obj.update(0, 50)                     # Updates index 0 to value 50 in log(n) time
```

```
> from segtree import Segtree
> obj = Segtree([1, 2, 3, 4, 5], 'min')
> obj.min(0, 3)
> obj.update(0, 50)
```

```
> from segtree import Segtree
> obj = Segtree([1, 2, 3, 4, 5], 'max')
> obj.max(0, 3)
> obj.update(0, 50)
```
