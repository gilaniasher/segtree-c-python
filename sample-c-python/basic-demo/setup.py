'''
This script actually compiles our C code
Comes from here: https://docs.python.org/3/extending/building.html#building

Build:
  python3 setup.py build

Installing the library:
  sudo python3 setup.py install

Using:
  import spam
  spam.demo('echo hi')
'''

from distutils.core import setup, Extension

module1 = Extension('spam', sources=['spammodule.c'])
setup(name='spam', version='1.1', description='This is a demo package', ext_modules=[module1])
