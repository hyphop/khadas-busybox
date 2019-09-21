# khadas busybox mini system

## About

    busybox cross-compilation example. We create standalone busybox and create 
    minimal rootfs, prepare and pack for booting.

## Get sources, Install

## Build, Compile, Pack

    ./prepare
    ./build_bb	# build bb
    ./build_db	# build dropbear ssh
    ./pack	# pack rootfs
    ./packa	# pack squashfs
    ./packb	# pack cpio
    ./packc	# pack mkimake
    ./show

## Custom

    ./build menuconfig
    ./build install

## Requires

+ squashfs-tools ( apt-get install squashfs-tools )
+ ...

## AUTHOR

    ## hyphop ##

## LICENSE
    
    cat ./LICENSE
