# Embedding Python in C++ Example

A simple example of embedding python straight from [the python docs](https://docs.python.org/3/extending/embedding.html), with some minor changes for C++.

Compiled on Arch with g++ 9.2.0 and python3.8

Compile with a line like:  
```sh
g++ -g -std=c++17 -Wall -Wextra -Werror main.cpp -o main -I/usr/include/python3.8 -lfmt -lpython3.8
```

Replace the C++ standard version and python version with whatever you want.

Run with:  
```sh
PYTHONPATH=. ./main multiply multiply 10 50
```

The python path environment variable ensures that python finds `multiply.py`
