#!/bin/sh

set -e
. ./scripts/build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/raccoonos.kernel isodir/boot/raccoonos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "raccoonos" {
    multiboot /boot/raccoonos.kernel
}
EOF
grub-mkrescue -o raccoonos.iso isodir