/* example.i */
%module ExampleModule
%{
#include "example.hpp"
%}
%include "std_string.i"
%include "typemaps.i"
%include "stl.i"
%include "example.hpp"
