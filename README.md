# How to use:

### First of all clone this repo (and it's submodules automatically) with this command:
```
git clone --recursive https://github.com/CreepyMemes/glTemplate.git
```

### From the _root directory_, to generate the cmake configuration run this command:

- #### If on Linux just run this command:
```
cmake -S . -B build/
```

- #### If on Windows install MinGW from [here](https://www.msys2.org/) then run this command:
```
cmake -S . -B build/ -G "MinGW Makefiles"
```

### Finally to generate the executable file run this command:
    cmake --build build

### Then run the previously generated executable:

- #### If on Linux do:
```
./build/App
```

- #### If on Windows do:
```
.\build\App
```