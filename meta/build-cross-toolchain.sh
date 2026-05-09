#!/bin/bash
set -e

PWD="$(pwd)"
BUILT_FILE="toolchain-exists"

if ! [ "$(basename "$PWD")" = "build" ]; then
    echo "Error: not in build directory, cancelling cross-toolchain build"
    exit 1
fi

# setting desired GCC and Binutils versions
# from https://wiki.osdev.org/Cross-Compiler_Successful_Builds

TARGET="x86_64-elf"

BINUTILS_VER="2.45.1"
GCC_VER="15.2.0"

BINUTILS_DIR="binutils-$BINUTILS_VER"
GCC_DIR="gcc-$GCC_VER"

BINUTILS_BUILD_DIR="build-$BINUTILS_DIR"
GCC_BUILD_DIR="build-$GCC_DIR"

CROSS_PATH="cross"

if [ "$1" = "--clean" ]; then
    echo "Running clean"

    rm -rf "$BINUTILS_DIR"
    rm -rf "$BINUTILS_BUILD_DIR"

    rm -rf "$GCC_DIR"
    rm -rf "$GCC_BUILD_DIR"

    rm -rf "$CROSS_PATH"

    rm -f "$BUILT_FILE"

    exit
fi

if [ -e "$BUILT_FILE" ]; then
    echo "Toolchain already built, to rebuild, please delete ./toolchain-exists"
    exit 0
fi

# download and extract our sources

function download_and_extract() {
    local URL_BASE=$1
    local DIR=$2
    local ARXV="$DIR.tar.xz"

    if ! [ -e "$DIR" ]; then
        echo " - Downloading $ARXV..."
        wget -c "$URL_BASE/$ARXV"

        echo " - Extracting $ARXV..."
        tar xf "$ARXV"

        rm "$ARXV"
    else
        echo "$DIR already exists, skipping"
    fi
}

BINUTILS_URL_BASE="ftp.gnu.org/gnu/binutils"
GCC_URL_BASE="ftp.gnu.org/gnu/gcc/$GCC_DIR"

download_and_extract "$BINUTILS_URL_BASE" "$BINUTILS_DIR"
download_and_extract "$GCC_URL_BASE" "$GCC_DIR"

if ! [ -e "$CROSS_PATH" ]; then
    mkdir -p "$CROSS_PATH"
elif ! [ -d "$CROSS_PATH" ]; then
    echo "Error: $CROSS_PATH exists but is not a directory"
    echo "./$CROSS_PATH needs to be a directory to install the toolchain"
    exit 1
fi

# apply mno-red-zone patch
patch -p0 < patch-gcc.diff

# export the required env vars
export PREFIX="$PWD/$CROSS_PATH"
printf "\$PREFIX: %s\n" "$PREFIX"

export TARGET="$TARGET"
printf "\$TARGET: %s" "$TARGET"

export PATH="$PREFIX/bin:$PATH"

echo "Building binutils"

mkdir -p "$BINUTILS_BUILD_DIR" && cd "$BINUTILS_BUILD_DIR"

"../$BINUTILS_DIR/configure" \
    --target=$TARGET \
    --prefix="$PREFIX" \
    --with-sysroot \
    --disable-nls \
    --disable-werror

make "-j$(nproc)"
make install "-j$(nproc)"

cd ../

echo "Building GCC"

mkdir -p "$GCC_BUILD_DIR" && cd "$GCC_BUILD_DIR"

# build GCC
"../$GCC_DIR/configure" \
    --target=$TARGET \
    --prefix="$PREFIX" \
    --enable-languages=c,c++ \
    --disable-nls \
    --without-headers \
    --disable-hosted-libstdcxx

make all-gcc "-j$(nproc)"
make all-target-libgcc "-j$(nproc)"
make all-target-libstdc++-v3 "-j$(nproc)"

make install-gcc "-j$(nproc)"
make install-target-libgcc "-j$(nproc)"
make install-target-libstdc++-v3 "-j$(nproc)"

cd ../

touch "$BUILT_FILE"

echo "Toolchain successfully built"