#!/bin/bash

project_dir="$1"

if [ -z "$project_dir" ]; then
  echo "Error: project directory is not specified."
  exit 1
fi

find "$project_dir" -name "*.c" -print0 | while IFS= read -r -d $'\0' file; do
  clang-format -i "$file"
  echo "🚀 File formatted successfully: $file"
done

echo "Formatted all C files in $project_dir"
