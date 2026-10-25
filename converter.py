import json
import os

version_file_path = "version.txt"
file_name = "dabotics_80020C"

def get_version(path):
    if os.path.exists(path):
        with open(path, "r") as f:
            return f.read()

version = get_version(version_file_path)

# 1. Read your C++ source code text string
with open(f"src/merged_code_{version}.cpp", "r") as f:
    cpp_code_string = f.read()

# 2. Open and parse the VS Code configuration json file
with open("vex_project_settings.json", "r") as f:
    vscode_config = json.load(f)

# 3. Pull out the target parameters directly
sdk_version = vscode_config["project"]["sdkVersion"]
slot_number = vscode_config["project"]["slot"]
platform = vscode_config["project"]["platform"]
language = vscode_config["project"]["language"]

# 4. Pack everything cleanly into the dictionary structure
v5cpp_bundle = {
    "mode": "Text",
    "hardwareTarget": "brain",
    "textContent": cpp_code_string,
    "textLanguage": language,
    "robotConfig":[],
    "slot": slot_number,
    "platform": platform,
    "sdkVersion":sdk_version,
    "appVersion":"4.68.0",
    "fileFormat":"2.0.0",
    "targetBrainGen":"First",
    "v5Sounds":[
        {
            "name":"game over",
            "url":"static/sounds/mixkit-arcade-retro-game-over-213.wav"
        }
    ],
    "v5SoundsEnabled":false,
    "aiVisionSettings":{
        "colors":[],
        "codes":[],
        "tags":true,
        "AIObjects":true,
        "AIObjectModel":[],
        "aiModelDropDownValue":null
    }
}

# 5. Output the single final .v5cpp package file
with open(f"{file_name}_{version}.v5cpp", "w") as f:
    json.dump(v5cpp_bundle, f)

print(f"✅ Created {file_name}_{version}.v5cpp using SDK {sdk_version} on Slot {slot_number}!")
