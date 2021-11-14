'''
This script actually compiles our C code
Comes from here: https://docs.python.org/3/extending/building.html#building

Build:
  python3 setup.py build

Installing the library:
  sudo python3 setup.py install

Using:
  import custom
  obj = custom.Custom(count=12)
  obj.increment(5)
  print(obj.get_cnt())
  print(obj.cnt)
'''

from distutils.core import setup, Extension

module1 = Extension('custom', sources=['custommodule.c'])
setup(name='custom_demo', version='1.0', description='This is an object demo package', ext_modules=[module1])
