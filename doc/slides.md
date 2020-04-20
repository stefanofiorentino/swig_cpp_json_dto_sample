---
marp: true
---
# data transfer object by swig
## **Stefano Fiorentino**

stefano.fiore84@gmail.com
[@fiorentinoing](https://twitter.com/fiorentinoing)

## swig by example

09/10/2018
Milan, IT

---
<!-- theme: gaia -->
<!-- page_number: true -->
<!-- footer: stefanofiorentino.it | stefano.fiore84@gmail.com | [@fiorentinoing](https://twitter.com/fiorentinoing) -->

# Introduction

## what is this talk about?


* export a Modern C++ data-transfer object to several languages 
	* python will be used as example

---

# Introduction



* typing the following code inside a python REPL console

```python
import example; 
print example("{\"id\":\"foo\"}").toJsonString();
```

* returns 
```json
{
  "id" : "foo"
}
```
REPL = Read-Eval Print Loop

---

# Utility function

* typing the following code inside a python REPL console

```cpp
#include <json/json.h>

inline Json::Value fromStringtoJsonValue(std::string const &in)
{
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(in, root);
    if (!parsingSuccessful)
    {
        throw std::runtime_error(reader.getFormattedErrorMessages());
    }
    return root;
}
```

---

# example class: c'tors


```cpp
#include "util/bean.hpp"

class example
{
    std::string id;
public:
    example() = default;

    explicit example (Json::Value const & root) :
        id(root["id"].asString())
    {}

    explicit example (std::string const & str) :
        example(fromStringtoJsonValue(str))
    {}
};
```

---

# example class: serializer


```cpp
class example
{
	...
    
    Json::Value toJsonValue() const
    {
        Json::Value jsonValue;
        jsonValue["id"]=id;
        return jsonValue;
    }

    std::string toJsonString() const
    {
        return this->toJsonValue().toStyledString();
    }
};
```


---

# swig interface file


```swig
/* example.i */
%module ExampleModule
%{
#include "example.hpp"
%}
%include "std_string.i"
%include "typemaps.i"
%include "stl.i"
%include "example.hpp"
```
SWIG = Simplified Wrapper and Interface Generator

---

# clean.sh


```bash
rm -rf ./build
rm -rf ./python
rm -f ./example_wrap.cxx
rm -f ./*.so
rm -f ./*.o
```

---

# swig.python.sh


```bash
mkdir -p python
swig -python -c++ -outdir python example.i

```

---

# make.python.sh



```bash
rm -rf build && mkdir -p build && cd build
g++ -fpic -std=c++11 -x c++ -c ../example.hpp \
    ../example_wrap.cxx \
    -I/usr/include/python2.7 \
    -I/usr/include/jsoncpp
g++ -shared example.o example_wrap.o \
    -o ../_ExampleModule.so
cd ../

```


---

# launch.python.sh


```bash
LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjsoncpp.so \
PYTHONPATH=$PWD/python:$PYTHONPATH \
python -c \
'from ExampleModule import example; 
print example("{\"id\":\"foo\"}").toJsonString();'

```

---

<!-- page_number: false  -->

# Thanks!

https://stefanofiorentino.it

stefano.fiore84@gmail.com

[@fiorentinoing](https://twitter.com/fiorentinoing)

https://github.com/stefanofiorentino/swig_cpp_json_dto_sample
