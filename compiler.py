import os
import json

def get_pragma_content(file_list):
    combined_text = ""
    for path in file_list:
        # 1. Skip the file if it does not exist on your computer
        if not os.path.exists(path): 
            continue
            
        # 2. Read the whole file as a single block of text
        with open(path, "r") as f:
            text = f.read()
        
        # 3. Skip the file if it is missing either of the required pragma tags
        if "#pragma region" not in text or "#pragma endregion" not in text:
            continue
            
        # 4. Slice out the text exactly from start tag to end tag
        start_idx = text.find("#pragma region")
        end_idx = text.find("#pragma endregion") + len("#pragma endregion")
        pragma_block = text[start_idx:end_idx]
        
        # 5. Filter out your internal folder include lines
        block_lines = pragma_block.splitlines()
        for line in block_lines:
            if "JAR-Template/" not in line:
                combined_text += line + "\n"
                
        # Add a couple of blank spaces at the end of the file content block
        combined_text += "\n\n"

    return combined_text

def compile(declaration_files, definition_files, standalone_files):
    # 2. Gather your split code blocks
    declarations_code = get_pragma_content(declaration_files)
    definitions_code = get_pragma_content(definition_files)
    standalone_code = get_pragma_content(standalone_files)

    # 3. Read your main.cpp file
    with open("src/main.cpp", "r") as f:
        main_content = f.read()

    # 4. Target your specific main.cpp pragma tags
    marker = "//Config and autons"
    decl_marker = "#pragma region Declarations\n#pragma endregion"
    defn_marker = "#pragma region Definitions\n#pragma endregion"

    # Verify both target tags exist before swapping text
    if decl_marker in main_content and defn_marker in main_content and marker in main_content:
        # Wrap the gathered code inside your target main.cpp regions
        new_decl = f"#pragma region Declarations\n{declarations_code}#pragma endregion"
        new_defn = f"#pragma region Definitions\n{definitions_code}#pragma endregion"

        # Swap the empty regions with your fully loaded regions
        main_content = main_content.replace(decl_marker, new_decl)
        main_content = main_content.replace(defn_marker, new_defn)
        main_content = main_content.replace(marker, standalone_code)
        print("✅ Successfully compiled code!")
        return main_content
    else:
        print("❌ Error: Could not find the exact empty pragma slots inside src/main.cpp.")
        print("Ensure your main.cpp matches this exact formatting structure:")
        return None

def read_write(path, content=None):
    # Ensure target output directory exists before attempting to write a file
    parent_dir = os.path.dirname(path)
    if parent_dir and not os.path.exists(parent_dir):
        os.makedirs(parent_dir)

    if content is not None:
        with open(path, "w") as f:
            f.write(content)
            
    if os.path.exists(path):
        with open(path, "r") as f:
            return f.read().strip() # Added .strip() to clean up spacing artifacts
    return

def write(parent, file_name, version_file_path, content_dict):
    if content_dict is None or content_dict["textContent"] is None:
        print("❌ Build process stopped. Project archive output aborted.")
        return

    version = read_write(version_file_path)
    if not version:
        version = "1.0"
        read_write(version_file_path, version)
    
    json_string_content = json.dumps(content_dict, indent=2)
    
    output_file_path = f"{parent}{file_name}-{version}.v5cpp"
    read_write(output_file_path, json_string_content)
    
    try:
        new_version = f"{float(version) + 0.1:.1f}"
    except ValueError:
        new_version = "1.1"
        
    read_write(version_file_path, new_version)
    print(f"📦 Output project built at -> {output_file_path}")

# 2. Open and parse the VS Code configuration json file
with open(".vscode/vex_project_settings.json", "r") as f:
    vscode_config = json.load(f)

# 3. Pull out the target parameters directly
version_file_path = "version.txt"
output_folder = "out/"
file_name = "dabotics-80020C"

# 1. Separate your split files into Headers and Source lists
HEADER_FILES = [
    "include/JAR-Template/PID.h",
    "include/JAR-Template/odom.h",
    "include/curves.h",
    "include/JAR-Template/drive.h"
]

SOURCE_FILES = [
    "src/JAR-Template/util.cpp",
    "src/JAR-Template/PID.cpp",
    "src/JAR-Template/odom.cpp",
    "src/curves.cpp", 
    "src/JAR-Template/drive.cpp"
]

STANDALONE_FILES = [
    "src/robot-config.cpp",
    "src/autons.cpp"
]

sdk_version = vscode_config["project"]["sdkVersion"]
slot_number = vscode_config["project"]["slot"]
platform = vscode_config["project"]["platform"]
language = vscode_config["project"]["language"]

# 4. Pack everything cleanly into the dictionary structure
v5cpp_bundle = {
    "mode": "Text",
    "hardwareTarget": "brain",
    "textContent": compile(HEADER_FILES, SOURCE_FILES, STANDALONE_FILES),
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
    "v5SoundsEnabled": False,
    "aiVisionSettings":{
        "colors":[],
        "codes":[],
        "tags": True,
        "AIObjects": True,
        "AIObjectModel":[],
        "aiModelDropDownValue": None
    }
}

write(output_folder, file_name, version_file_path, v5cpp_bundle)