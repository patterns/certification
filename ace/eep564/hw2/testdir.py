import os
import re
import glob
import json
from pathlib import Path
strokes = []

for  dp, dn, fn in os.walk('/home/husky/Public/eep564/hw2/ds30'):

    js_files = [f for f in fn if f.endswith('.json')]

    for jn in js_files:
        # 1. extract label in filename
        # 2. from json get item at index=2
        # 3. append item to the strokes list
        parts = re.split("[-.]", jn)
        label_of_file = parts[1]
        # ~ print(f' between hyphen and dot: {label_of_file} w/ {jn}')

        jsonpath = Path(dp).joinpath(jn)
        with open(jsonpath, "r") as file:
            file_contents = file.read()
        file_data = json.loads(file_contents)

        # TODO the index needs to be renumbered
        for stroke in file_data["strokes"]:
            if stroke["index"] == 1:
                stroke["label"] = label_of_file
                stroke["filename"] = jn
                strokes.append(stroke)

        print(f'{strokes}')
