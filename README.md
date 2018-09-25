> mkdir -p python

> swig -python -c++ -outdir python example.i


> rm -rf build && mkdir -p build && cd build

> g++ -fpic -std=c++11 -x c++ -c ../example.hpp ../example_wrap.cxx -I/usr/include/python2.7 -I/usr/include/jsoncpp

> g++ -shared example.o example_wrap.o -o ../_ExampleModule.so

> cd ../
