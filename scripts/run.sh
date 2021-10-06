#!/bin/sh
set -e
. ./scripts/iso.sh

DEBUG=""

if [[ $1 == "-d" ]]; then
    DEBUG="-d cpu_reset,int"
fi

qemu-system-$(./scripts/target-triplet-to-arch.sh $HOST) $DEBUG -cdrom raccoonos.iso