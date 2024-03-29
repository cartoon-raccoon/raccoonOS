#!/bin/sh
set -e
. ./scripts/iso.sh

DEBUG=""

if [[ $1 == "-d" ]]; then
    DEBUG="-d int -no-reboot"
fi

qemu-system-$(./scripts/target-triplet-to-arch.sh $HOST) \
    -serial file:serial.log \
    $DEBUG -cdrom raccoonos.iso