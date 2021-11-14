# Demo of Object C Extension as Python Module

## Writing the C Extension

Notes
- Now I can actually keep track of a C struct and manipulate it from Python
- There is a `new` and `init` function. `new` prepares an empty object in memory, `init` is the actual constructor part that puts in values
- There is also a `dealloc` function that cleans up the object. Still confused on freeing memory I malloc (see object-demo)
- I need `structmember.h` to define `members` which just allows me to access fields with dot notation (obj.data)
- Kwargs parsing format string: you put the regular data types, a pipe, and then kwarg types. So `foo(string, int, a=int) => "si|i"`
- C Python API doesnt seem to support ints, does everything through longs

## Building C Extension for Python
`$ python3 setup.py build`

This will create a build folder

## Installing C Extension
`$ sudo python3 setup.py install`

## Verifying
Now you should be able to verify that the module name exists when running:

`$ pip3 list`

You should also be able to use it in a Python script now
```
> import custom
> obj = custom.Custom(count=12)
> obj.increment(5)
> print(obj.get_cnt())
> print(obj.cnt)
```
