#!/bin/bash

set -euo pipefail

bin_name="$1.exe"
project_name="$1"
assets_dir="$1/assets"
target_path="$project_name/target/x86_64-pc-windows-gnu/debug"
output_dir="/mnt/d/code/rust/tmp/bevy_sandbox/$project_name"
bin_path="$target_path/$bin_name"

(cd "$project_name" && cargo build --target x86_64-pc-windows-gnu)

rm -rf "$output_dir"
mkdir -p "$output_dir"
cp -vf "$bin_path" "$output_dir"
[[ -d "$assets_dir" ]] && rsync -auL "$assets_dir" "$output_dir"

exec "$output_dir/$bin_name"
