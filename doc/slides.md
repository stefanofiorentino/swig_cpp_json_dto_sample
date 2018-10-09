<!-- $size: 16:9 -->

<style>
.slide_inner
{
    height: 600px;
}

footer
{
    text-align: right;
    width: 92%;
    bottom: 10px !important;
	left: 90px !important;
}

.points
{
    font-size: 115%;
    margin-left: -40px;
    margin-right: -40px;
}

.inline-link
{
    font-size: 50%;
    margin-top: -2.6em;
    margin-right: 10px;
    text-align: right;
    font-weight: bold;
}

.intxt
{
	font-size: 75%;
    position: absolute;
    top: -80px;
    left: -65px;
    color: grey;
}

.slide_page
{
	top: 0px;
    right: 20px !important;
}
</style>

<span style="font-size: 150%">

<br>

<center style="margin-top: -70px !important">

# data transfer object by swig

</center>

<br>

<div style="float: left; font-size: 70%">

## **Stefano Fiorentino**

stefano.fiore84@gmail.com
[@fiorentinoing](https://twitter.com/fiorentinoing)

</div>

<div style="float: right; font-size: 70%; text-align: right; margin-top: -0px !important">

## swig by example

09/10/2018
Milan, IT

</div>

</span>

---

<!-- page_number: true -->
<!-- footer: stefanofiorentino.it | stefano.fiore84@gmail.com | @fiorentinoing -->

# Introduction
## what is this talk about?

<div class="points">

* export a Modern C++ data-transfer object to several languages 
	* python will be used as example

</div>

---

# Introduction

<div class="points">

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
<div align="right">REPL = Read-Eval Print Loop</div>
</div>

---

# Utility function

<div class="points">

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
</div>

---

# example class: c'tors

<div class="points">

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

</div>

---

# example class: serializer

<div class="points">

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

</div>

---

# swig interface file

<div class="points">

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
<div align="right">SWIG = Simplified Wrapper and Interface Generator</div>
</div>

---

# clean.sh

<div class="points">

```bash
rm -rf ./build
rm -rf ./python
rm -f ./example_wrap.cxx
rm -f ./*.so
rm -f ./*.o
```

</div>

---

# swig.python.sh

<div class="points">

```bash
mkdir -p python
swig -python -c++ -outdir python example.i

```

</div>

---

# make.python.sh

<div class="points">

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

</div>

---

# launch.python.sh

<div class="points">

```bash
LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjsoncpp.so \
PYTHONPATH=$PWD/python:$PYTHONPATH \
python -c \
'from ExampleModule import example; 
print example("{\"id\":\"foo\"}").toJsonString();'

```

</div>

---

<!-- page_number: false  -->

<center style="zoom:80%; font-size: 50px">

# Thanks!

https://stefanofiorentino.it

stefano.fiore84@gmail.com

[@fiorentinoing](https://twitter.com/fiorentinoing)

<small>

https://github.com/stefanofiorentino/swig_cpp_json_dto_sample

</small>

</center>
