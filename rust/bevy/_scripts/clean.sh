#!/bin/bash

find . -type d -name "target" -print0 \
    | xargs -0 dirname \
    | xargs -I{} sh -c 'cd {}; echo {}; cargo clean'
