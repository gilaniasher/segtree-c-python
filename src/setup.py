'''
This script actually compiles our C code
Build/Deploy Instructions: https://realpython.com/pypi-publish-python-package/

Build:
  sudo python3 setup.py sdist
    This just generates the .tar.gz not wheel files.
    The wheel files make the install process quicker

  sudo python3 setup.py sdist bdist_wheel
    The above produces a specific linux wheel. Need to run several commands to
    generate the manylinux wheel which PyPi allows

  docker pull quay.io/pypa/manylinux_2_24_x86_64:latest
  docker run -v .../seg-tree-c-python:/mnt/segtree -it 045b8d48f0c4
  /opt/python/cp36-cp36m/bin/pip3 wheel src/ -w src/output
  auditwheel repair output/c_segment_tree-1.0-cp36-cp36m-linux_x86_64.whl -w output/

Verify: twine check dist/*
Deploy TestPyPi: twine upload --repository-url https://test.pypi.org/legacy/ dist/*
Deploy PyPi: twine upload  dist/*

Using:
  import segtree
  obj = segtree.Segtree([1,2,3,4], 'sum')
  obj.sum(0, 2)
  obj.update(1, 35)

  obj = segtree.Segtree([1,2,3,4], 'min')
  obj.min(0, 2)
'''

from pathlib import Path
# from distutils.core import setup, Extension
from setuptools import setup, Extension

here = Path(__file__).parent
README = (here / 'README.md').read_text()
module1 = Extension('segtree', sources=['segtreemodule.c', 'segtree.c'], headers=['./segtree.h'])

setup(
  name='c-segment-tree',
  version='1.0',
  description='Segment Tree package written in C',
  long_description=README,
  long_description_content_type='text/markdown',
  url='https://github.com/gilaniasher/segtree-c-python',
  author='Asher Gilani',
  author_email='gilaniasher@gmail.com',
  ext_modules=[module1]
)
