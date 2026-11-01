import json
from pathlib import Path
import shlex
import subprocess
import sys


output = Path(sys.argv[1])
recipes = subprocess.run(sys.argv[2:], check=True, text=True, capture_output=True)
entries = []
for line in recipes.stdout.splitlines():
    arguments = shlex.split(line)
    if "-c" not in arguments or "-o" not in arguments:
        continue
    entries.append({
        "directory": str(Path.cwd()),
        "file": arguments[arguments.index("-c") + 1],
        "arguments": arguments,
        "output": arguments[arguments.index("-o") + 1],
    })

temporary = output.with_suffix(".json.tmp")
temporary.write_text(json.dumps(entries, indent=2) + "\n")
temporary.replace(output)
