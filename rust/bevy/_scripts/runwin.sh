#!/bin/bash

set -euo pipefail

cargo build --target x86_64-pc-windows-gnu

cp -vf "target/x86_64-pc-windows-gnu/debug/$1" .
exec "./$1"
