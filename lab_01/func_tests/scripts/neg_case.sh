#!/bin/bash
file_app_in="${1}"
file_app_args=""

if [ $# -gt 1 ]; then
  file_app_args=$(cat "${2}")
fi

if [ -n "$USE_VALGRIND" ]; then
  eval "valgrind --log-file=valgrind_out.txt -q ../../app.exe ../../$file_app_args ./program_out.txt"
else
  eval "../../app.exe < $file_app_in &> /dev/null"
fi

if test $? -ne 0; then
  exit 0
else
  exit 1
fi