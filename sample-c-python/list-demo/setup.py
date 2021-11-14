'''
This script actually compiles our C code
Comes from here: https://docs.python.org/3/extending/building.html#building

Build:
  python3 setup.py build

Installing the library:
  sudo python3 setup.py install

Using:
  import customlist
  obj = customlist.Custom([0,1,2,3])
  obj.get(0)
  obj.increment(0, 5)
  obj.get(0)
'''

from distutils.core import setup, Extension

module1 = Extension('customlist', sources=['customlistmodule.c'])
setup(name='customlist', version='1.0', description='This is an list demo package', ext_modules=[module1])
