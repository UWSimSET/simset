# Basic installation instructions

You can build SimSET either via `make` or CMake. In both cases, you might want
to add the installation directory of the SimSET binary to your `PATH`.

## Using `make`
A convenience script will build `simset` in the `bin` subdirectory

```sh
./make_all.sh
```

## Using CMake

You could install as follows
```sh
# set variables where you want to build and install
INSTALL_DIR="$PWD/install"
BUILD_DIR="$PWD/build"
# configure
cmake -B "${BUILD_DIR}" -S . \
    -DCMAKE_INSTALL_PREFIX:PATH="${INSTALL_DIR}" \
    -DCMAKE_INSTALL_RPATH_USE_LINK_PATH:BOOL=TRUE \
    -DCMAKE_INSTALL_RPATH:PATH="${INSTALL_DIR}/lib"
# build
cmake --build "${BUILD_DIR}" --config Release
# install
cmake --install "${BUILD_DIR}"
```

When using CMake, the following will be installed in `CMAKE_INSTALL_PREFIX`
- a static library and a shared library in `lib`
- `SimSETConfig.cmake` etc in `lib/cmake/SimSET-X.Y`
- include files in `include/SimSET-X.Y`
- executable and symbolic links in `bin`

You should then be able to use the SimSET library from an external project by saying
```sh
cmake -DSimSET_DIR:PATH=/wherever/you/installed/lib/cmake/SimSET-X.Y
```
