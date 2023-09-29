#!/bin/bash
git status --ignore-submodules=none
echo "Submodule statuses:"
git submodule status --recursive