'''
This script actually compiles our C code
Comes from here: https://docs.python.org/3/extending/building.html#building

Build:
  python3 setup.py build

Installing the library:
  sudo python3 setup.py install

Using:
  import segtree
  obj = segtree.Segtree([1,2,3,4])
  obj.sum(0, 2)
  obj.update(1, 35)
'''

from distutils.core import setup, Extension

module1 = Extension('segtree', sources=['segtreemodule.c', 'segtree.c'])
setup(name='segtree', version='1.0', description='This is a Segment Tree package', ext_modules=[module1])
