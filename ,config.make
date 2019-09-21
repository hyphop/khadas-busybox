#!/bin/sh

## hyphop ##

export ARCH=arm
export ARCH=arm64
export ARCH=aarch64

export CROSS_COMPILE=aarch64-linux-gnu-
export CROSS_COMPILE=aarch64-linux-gnu
export CROSS_COMPILE=aarch64-openwrt-linux-
export CROSS_COMPILE=aarch64-openwrt-linux

export LIBC="$CROSS_COMPILE/libc/lib"

export STAGING_DIR="$PWD/../../tc"

export PATH="$STAGING_DIR/bin/:$PATH"

