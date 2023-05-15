'''
Author: yh
Date: 2023-05-10 00:00:45
LastEditTime: 2023-05-10 00:01:20
Description: 
FilePath: /Linux/compdb.py
'''

#!/usr/bin/python3
import sys
import json
import os
from pathlib import Path

if len(sys.argv) != 4:
    print("Usage: python3 main.py <project directory> <input compiledb path> <output compiledb path>")
    sys.exit()

files = Path(sys.argv[1])
result = list(map(os.path.realpath, map(str, list(files.rglob("*.cpp")) + list(files.rglob("*.c")))))

with open(sys.argv[2]) as compdb_input:
    compdb_origin = json.load(compdb_input)
    compdb_gen = []
    for obj in compdb_origin:
        full_path = obj["directory"] + '/' + obj["file"]
        if full_path in result:
            print("Find file: %s" % full_path)
            compdb_gen.append(obj)

with open(sys.argv[3], "w") as compdb_out:
    compdb_out.write(json.dumps(compdb_gen, indent=1))
