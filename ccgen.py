import sys
import itertools
from pathlib import Path
import json

def parse_task(t):
    sections = t.split(" | ")
    task_name = sections[0][5:]
    task_options = []
    with open("lib/build/tmp/{}/options.txt".format(task_name)) as f:
        task_options = [o.strip().replace("\\\\", "\\").replace("\"", "") for o in f.readlines()]

    return {
        "source": [f.replace("]", "") for f in sections[2][1:-2].split(", ")],
        "task": task_name,
        "output": sections[1],
        "options": task_options
    }

compilers = None
tasks = None

with open("ccgen/compilers.txt") as compilers_file:
    compilers = [c[c.find("|") + 1:].strip() for c in set(compilers_file.readlines())]

if len(compilers) == 0:
    print("ccgen/compilers.txt is empty.")
    print("If you are using MSVC, this tool cannot help you, because ", end="")
    print("Gradle doesn't expose the location of the MSVC compiler.")
    sys.exit(0)

with open("ccgen/tasks.txt") as tasks_file:
    tasks = [parse_task(t) for t in set(tasks_file.readlines())]

if len(tasks) == 0:
    print("Run Gradle first.")
    sys.exit(0)

#print("Compilers:", compilers)
#print("Tasks:", tasks)

export = []

for (compiler, task) in itertools.product(compilers, tasks):
    outfile_mapping = {}
    for child_dir in Path(task["output"]).iterdir():
        value = str(child_dir)
        key = list(child_dir.iterdir())[0].name
        outfile_mapping[key] = value

    for src in task["source"]:
        command = task["options"].copy()
        command.insert(0, compiler)

        obj_file = Path(src).stem + ".obj"
        outfile = Path(outfile_mapping[obj_file]).joinpath(obj_file)

        command.extend(["-o", str(outfile), src])

        export.append({
            "file": src,
            
            "arguments": command
        })
with open("compile_commands.json", "w+") as ccjson:
    json.dump(export, ccjson, indent = 2)