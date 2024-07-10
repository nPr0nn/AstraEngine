#!/bin/bash

if [ "$#" -eq 0 ]; then
  echo "Building desktop version..."
  echo "Running..."  
  make linux
  exit 1
  
elif [ "$1" = "web" ]; then
  source ext/emsdk/emsdk_env.sh
  make web
  exit 1
fi
