from setuptools import setup, find_packages

setup(name='supernova', version='0.1.0', packages=find_packages(),
      setup_requires=["cffi>=1.15.0"],
      cffi_modules=["supernova/build_c_code.py:ffibuilder"],
      install_requires=["cffi>=1.15.0",
                        "pytest",
                        "numpy"],
      options={'build_ext': {'inplace': True}})
