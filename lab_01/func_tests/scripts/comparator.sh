#!/bin/bash

if cmp "$1" "$2" &>/dev/null; then
  exit 0
fi
exit 1