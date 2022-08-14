# Hypernova 🌠
Re-implementation of the [Supernova orbit propagator](https://github.com/spacesys-finch/supernova) in a faster and more accessible package.

Hypernova is a fast orbit propagator implemented in C and wrapped for Python using `cffi`, designed for the University of Toronto Aerospace Team's FINCH mission. FINCH orbits in a 550 km Sun-Synchronous orbit, and as such the solvers and physics models used by Hypernova were selected for the best simulation fidelity in a low-Earth orbit.

# Installation
You can install Hypernova as a Python package directly using the following command:

`pip install git+https://github.com/spacesys-finch/hypernova`

Hypernova will automatically compile C code into suitable binaries for your system on installation -- no more fiddling around with gcc or ctypes needed!

The Python wrapper takes care of calls to the propagator, making it easier to use for seasoned Python users.

# Demos
Hypernova comes with a few examples which you can run.
## Basic Orbit and Plot
`python -m hypernova.examples.basic_orbit_and_plot`

This will generate the following output:
![Demo Image](../assets/basic_orbit_demo.png?raw=true)


# Testing Suite
Hypernova is equipped with a testing suite to validate its functionality. The way to run the testing suite is to copy the scripts from the `/tests` folder into your working path and run `pytest` from your command terminal.
