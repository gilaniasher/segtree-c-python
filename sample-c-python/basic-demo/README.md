# Demo of Basic C Extension as Python Module
Had to read a lot of documentation to figure this out so just wanted to write some of the steps before I forget.

## Writing the C Extension
I still don't know how to hold onto actual objects, just running functions right now.

Notes
- Pretty much all functions have to be static except for `PyInit_modulename`
- The `PyInit_modulename` function has to be named like that, so it has to be `PyInit_spam` in our case
- Main important thing is that you have to export something like `spammodule` which is used by the PyInit function. This `spammodule` struct will have the methods available to users

## Building C Extension for Python
`$ python3 setup.py build`

This will create a build folder

## Installing C Extension
`$ sudo python3 setup.py install`

## Verifying
Now you should be able to verify that the module name (spam in this case) exists when running

`$ pip3 list`

You should also be able to use it in a Python script now
```
> import spam
> spam.demo('echo helloworld')
```