# Demo of List C Extension as Python Module

## Writing the C Extension

Notes
- Now my struct object holds onto an int pointer which I malloc when my object is being created
- Constructor takes a python list as input, verifying it is in fact a list
- I also iterate through all the entries verifying that each item is a long
- I then take the long and add it to my C array
- I'm not sure if I have to free my malloc'd memory, trying to do so in the destructor complains saying I'm freeing an invalid pointer. This malloc'd memory must exist in Python space now which is why it is complaining. Maybe just doing the Python decrease ref count is enough idk

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
> import customlist
> obj = customlist.Custom([1,2,3])
> obj.get(0)
> obj.increment(0, 3)
```
