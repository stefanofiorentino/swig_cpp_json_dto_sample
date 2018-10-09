LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjsoncpp.so \
PYTHONPATH=$PWD/python:$PYTHONPATH \
python -c 'from ExampleModule import example; print example("{\"id\":\"foo\"}").toJsonString();'