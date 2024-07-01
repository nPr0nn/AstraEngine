#!/bin/bash

if [ "$#" -eq 0 ]; then
  echo "Building desktop version..."
  echo "Running..."  
  ./zig build -Dtarget=x86_64-linux-gnu run --cache-dir "builds/cache-dir" --prefix "builds/linux"
  
  exit 1
elif [ "$1" == "web" ]; then
  echo "Building web version..."
fi
