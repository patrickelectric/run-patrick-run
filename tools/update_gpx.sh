#!/usr/bin/env sh
script_path="$( cd "$(dirname "$0")" ; pwd -P )"
adb pull /storage/sdcard0/gpxdata "${script_path}/.."
