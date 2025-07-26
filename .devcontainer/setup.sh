#!/usr/bin/env bash

apt update && apt install clangd -y

git submodule update --init --recursive --depth 1 -- qmk_firmware
git submodule update --init --recursive --depth 1 -- sm_td
git submodule update --init --depth 1 -- kbd_firmware # kbd_firmware has qmk and vial as submodules, avoid cloning them

qmk config user.qmk_home="$(realpath qmk_firmware)"
qmk config user.overlay_dir="$(realpath .)"

qmk compile --compiledb -kb crkbd/rev4_1/standard -km mazharenko
