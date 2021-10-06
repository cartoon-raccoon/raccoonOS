#!/bin/sh
set -e
. ./scripts/config.sh

for PROJECT in $PROJECTS; do
    (cd $PROJECT && $MAKE clean)
done

rm -rf sysroot
rm -rf isodir
rm -rf raccoonos.iso