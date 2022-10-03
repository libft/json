#!/bin/sh

set -e

make -C assets/leak_test all
make -C src PROFILE=debug TARGET=development .cache/libft.development.debug.a
make -C src PROFILE=debug TARGET=development SANITIZER=undefined .cache/libft.development.debug.undefined.a || echo "[WARNING] Failed to build debug/development/undefined" 1>&2
make -C src PROFILE=debug TARGET=development SANITIZER=address .cache/libft.development.debug.address.a || echo "[WARNING] Failed to build debug/development/address" 1>&2
make -C src PROFILE=debug TARGET=development SANITIZER=memory .cache/libft.development.debug.memory.a || echo "[WARNING] Failed to build debug/development/memory" 1>&2
make -C src PROFILE=debug TARGET=development SANITIZER=leak .cache/libft.development.debug.leak.a || echo "[WARNING] Failed to build debug/development/leak" 1>&2
make -C src PROFILE=debug TARGET=production .cache/libft.production.debug.a
make -C src PROFILE=debug TARGET=production SANITIZER=undefined .cache/libft.production.debug.undefined.a || echo "[WARNING] Failed to build debug/development/undefined" 1>&2
make -C src PROFILE=debug TARGET=production SANITIZER=address .cache/libft.production.debug.address.a || echo "[WARNING] Failed to build debug/development/address" 1>&2
make -C src PROFILE=debug TARGET=production SANITIZER=memory .cache/libft.production.debug.memory.a || echo "[WARNING] Failed to build debug/development/memory" 1>&2
make -C src PROFILE=debug TARGET=production SANITIZER=leak .cache/libft.production.debug.leak.a || echo "[WARNING] Failed to build debug/development/leak" 1>&2
make -C src PROFILE=release TARGET=development .cache/libft.development.release.a
make -C src PROFILE=release TARGET=development SANITIZER=undefined .cache/libft.development.release.undefined.a || echo "[WARNING] Failed to build release/development/undefined" 1>&2
make -C src PROFILE=release TARGET=development SANITIZER=address .cache/libft.development.release.address.a || echo "[WARNING] Failed to build release/development/address" 1>&2
make -C src PROFILE=release TARGET=development SANITIZER=memory .cache/libft.development.release.memory.a || echo "[WARNING] Failed to build release/development/memory" 1>&2
make -C src PROFILE=release TARGET=development SANITIZER=leak .cache/libft.development.release.leak.a || echo "[WARNING] Failed to build release/development/leak" 1>&2
make -C src PROFILE=release TARGET=production .cache/libft.production.release.a
make -C src PROFILE=release TARGET=production SANITIZER=undefined .cache/libft.production.release.undefined.a || echo "[WARNING] Failed to build release/development/undefined" 1>&2
make -C src PROFILE=release TARGET=production SANITIZER=address .cache/libft.production.release.address.a || echo "[WARNING] Failed to build release/development/address" 1>&2
make -C src PROFILE=release TARGET=production SANITIZER=memory .cache/libft.production.release.memory.a || echo "[WARNING] Failed to build release/development/memory" 1>&2
make -C src PROFILE=release TARGET=production SANITIZER=leak .cache/libft.production.release.leak.a || echo "[WARNING] Failed to build release/development/leak" 1>&2
make -C test PROFILE=debug TARGET=development
[ ! -f src/.cache/libft.development.debug.undefined.a ] || make -C test PROFILE=debug TARGET=development SANITIZER=undefined
[ ! -f src/.cache/libft.development.debug.address.a ] || make -C test PROFILE=debug TARGET=development SANITIZER=address
[ ! -f src/.cache/libft.development.debug.memory.a ] || make -C test PROFILE=debug TARGET=development SANITIZER=memory
[ ! -f src/.cache/libft.development.debug.leak.a ] || LSAN_OPTIONS=suppressions="$(pwd)/lsan-suppressions.txt" make -C test PROFILE=debug TARGET=development SANITIZER=leak
make -C test PROFILE=debug TARGET=production
[ ! -f src/.cache/libft.production.debug.undefined.a ] || make -C test PROFILE=debug TARGET=production SANITIZER=undefined
[ ! -f src/.cache/libft.production.debug.address.a ] || make -C test PROFILE=debug TARGET=production SANITIZER=address
[ ! -f src/.cache/libft.production.debug.memory.a ] || make -C test PROFILE=debug TARGET=production SANITIZER=memory
[ ! -f src/.cache/libft.production.debug.leak.a ] || LSAN_OPTIONS=suppressions="$(pwd)/lsan-suppressions.txt" make -C test PROFILE=debug TARGET=production SANITIZER=leak
make -C test PROFILE=release TARGET=development
[ ! -f src/.cache/libft.development.release.undefined.a ] || make -C test PROFILE=release TARGET=development SANITIZER=undefined
[ ! -f src/.cache/libft.development.release.address.a ] || make -C test PROFILE=release TARGET=development SANITIZER=address
[ ! -f src/.cache/libft.development.release.memory.a ] || make -C test PROFILE=release TARGET=development SANITIZER=memory
[ ! -f src/.cache/libft.development.release.leak.a ] || LSAN_OPTIONS=suppressions="$(pwd)/lsan-suppressions.txt" make -C test PROFILE=release TARGET=development SANITIZER=leak
make -C test PROFILE=release TARGET=production
[ ! -f src/.cache/libft.production.release.undefined.a ] || make -C test PROFILE=release TARGET=production SANITIZER=undefined
[ ! -f src/.cache/libft.production.release.address.a ] || make -C test PROFILE=release TARGET=production SANITIZER=address
[ ! -f src/.cache/libft.production.release.memory.a ] || make -C test PROFILE=release TARGET=production SANITIZER=memory
[ ! -f src/.cache/libft.production.release.leak.a ] || LSAN_OPTIONS=suppressions="$(pwd)/lsan-suppressions.txt" make -C test PROFILE=release TARGET=production SANITIZER=leak
