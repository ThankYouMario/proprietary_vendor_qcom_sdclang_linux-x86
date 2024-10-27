#! /bin/sh

# Copyright (c) 2024, Paranoid Android. All rights reserved.

# PA Changes:
# Strip binaries to optimize size (thanks Ju Hyung Park)
# Split files over 100MB into split archives.

# Strip binaries:
find . -type f -exec file {} \; \
    | grep "x86" \
    | grep "not strip" \
    | grep -v "relocatable" \
        | tr ':' ' ' | awk '{print $1}' | while read file; do
            strip $file
done

find . -type f -exec file {} \; \
    | grep "ARM" \
    | grep "aarch64" \
    | grep "not strip" \
    | grep -v "relocatable" \
        | tr ':' ' ' | awk '{print $1}' | while read file; do aarch64-linux-android-strip $file
done

find . -type f -exec file {} \; \
    | grep "ARM" \
    | grep "32.bit" \
    | grep "not strip" \
    | grep -v "relocatable" \
        | tr ':' ' ' | awk '{print $1}' | while read file; do arm-linux-androideabi-strip $file
done

# Split files over 100MB into partial archives
cd compiler/bin
split --bytes=99M -d clang-19 clang-19.part
split --bytes=99M -d clang-repl clang-repl.part
split --bytes=99M -d flang-new flang-new.part
cd ../..

# Capture version number for automatic committing
VERSION=$(./compiler/bin/clang --version | grep 'version' | sed 's/clang version //g')

# Commit new version
git add .
git commit -m "Import stripped Snapdragon LLVM ARM Compiler $VERSION" -m "See compiler/RELEASE_NOTES and upgrade.sh for more information on what changed"
