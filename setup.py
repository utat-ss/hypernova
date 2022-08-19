from setuptools import setup, find_packages

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

setup(name='hypernova-orbit',
      version='0.2.0',
      author="Mingde Yin",
      description="Orbit propagation and analysis tool.",
      long_description=long_description,
      long_description_content_type="text/markdown",
      url="https://github.com/spacesys-finch/hypernova/",
      license="LGPLv3",
      packages=find_packages(),
      setup_requires=["cffi>=1.15.0"],
      cffi_modules=["hypernova/build_c_code.py:ffibuilder"],
      install_requires=["cffi>=1.15.0",
                        "numpy",
                        "matplotlib"],
      options={'build_ext': {'inplace': True}},
      classifiers=["Development Status :: 3 - Alpha",
                   "Programming Language :: Python :: 3",
                   "License :: OSI Approved :: MIT License",
                   "Operating System :: OS Independent",
                   "Programming Language :: C",
                   "Topic :: Scientific/Engineering :: Physics",
                   "Intended Audience :: Science/Research"],
      python_requires='>=3.6')
