#!/usr/bin/env bash

apt update && apt install clangd -y

git submodule update --init --recursive --depth 1 -- vial-qmk
git submodule update --init --depth 1 -- kbd_firmware # kbd_firmware has qmk and vial as submodules, avoid cloning them

qmk config user.qmk_home="$(realpath vial-qmk)"
qmk config user.overlay_dir="$(realpath .)"

qmk compile --compiledb -kb crkbd/rev4_1/standard -km mazharenko
