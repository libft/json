#!/bin/sh

set -e

find data -name "*.json" | sed "s/.json//" | while IFS= read -r line
do
  echo $1 "$line.json" | diff - "$line.txt"
done
