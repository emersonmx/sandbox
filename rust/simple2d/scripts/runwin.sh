#!/bin/bash

set -euo pipefail

bin_name="simple2d.exe"
project_name="simple2d"
target_path="target/x86_64-pc-windows-gnu/debug"
output_dir="$OUTPUT_BASE_PATH/$project_name"
bin_path="$target_path/$bin_name"

cargo build --target x86_64-pc-windows-gnu
strip "$bin_path"

rm -rf "$output_dir"
mkdir -p "$output_dir"
cp -vf "$bin_path" "$output_dir"

(cd "$output_dir" && exec "$output_dir/$bin_name")
