# Segment Tree written in C as a Python Module
I am a big fan of C even though I tend to use Python for my daily workloads. I wanted to learn more about [Segment Trees](https://en.wikipedia.org/wiki/Segment_tree) so I decided to write one in C and make it available as a Python module.

My library supports basic min/max/sum queries.

## Usage
```
> from segtree import Segtree
> obj = Segtree([1, 2, 3, 4, 5], 'sum') # Accepted types: 'sum', 'min', 'max
> obj.sum(0, 3)                         # Gets range sum of original list in log(n) time
> obj.update(0, 50)                     # Updates index 0 to value 50 in log(n) time
```

You can also use `obj.min` or `obj.max` if you initialized with min/max intead of sum.

## Building and Installing
I want to make this available through pip, but for now it has to be built locally and installed. You may need to run `sudo apt install python3-dev` beforehand.

Navigate into the `src/` directory and we will be using `setup.py` to build and install.

To build, run:
```
$ python3 setup.py build
```

This creates a build directory with the compiled C/Python code.

To install, run:
```
$ sudo python3 setup.py install
```

This installs the library to your Python3 installation. You can verify that the `segtree` module appears when running `pip list`. Now you should be able to use the `segtree` module in your Python scripts as shown above.