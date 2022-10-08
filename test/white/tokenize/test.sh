#!/bin/sh

set -e

find ../data -name "*.json" | sort | sed "s/.json//" | while IFS= read -r line
do
  $1 "$line.json" | cmp -s "$line.txt"
done
