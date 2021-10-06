#!/bin/sh
set -e
. ./scripts/iso.sh

qemu-system-$(./scripts/target-triplet-to-arch.sh $HOST) -cdrom raccoonos.iso