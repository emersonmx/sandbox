#!/bin/bash

set -euo pipefail

cd "$1"

cargo build --target x86_64-pc-windows-gnu

cp -vf "target/x86_64-pc-windows-gnu/debug/$1.exe" .
exec "./$1.exe"
