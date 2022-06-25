# Supernova Nova 🌠
Re-implementation of the Supernova orbit propagator in a faster and more accessible package.

# Installation
You can install Supernova as a Python package directly using the following command:

`pip install git+https://github.com/spacesys-finch/supernova-nova`

You can then import everything from supernova, as expected with a normal Python package.

Supernova will automatically compile C code into suitable binaries for your system on installation -- no more fiddling around with gcc or ctypes anymore!

# Testing Suite
Supernova is equipped with a testing suite to validate its functionality. The way to run the testing suite is to copy the scripts from the `/tests` folder and run `pytest` from your command terminal.
