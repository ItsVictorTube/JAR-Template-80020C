import os

# 1. Separate your split files into Headers and Source lists
HEADER_FILES = [
    "include/JAR-Template/PID.h",
    "include/JAR-Template/odom.h",
    "include/JAR-Template/curves.h",
    "include/JAR-Template/drive.h"
]

SOURCE_FILES = [
    "src/JAR-Template/util.cpp",
    "src/JAR-Template/PID.cpp",
    "src/JAR-Template/odom.cpp",
    "src/JAR-Template/curves.cpp", 
    "src/JAR-Template/drive.cpp"
]

STANDALONE_FILES = [
    "src/robot-config.cpp",
    "src/autons.cpp"
]

version_file_path = "version.txt"

def get_version(path):
    if os.path.exists(path):
        with open(path, "r") as f:
            return f.read()
        
def get_pragma_content(file_list):
    """Gathers the text inside the pragma regions from a list of files"""
    combined_text = ""
    for path in file_list:
        if os.path.exists(path):
            with open(path, "r") as f:
                text = f.read()
            
            if "#pragma region" in text and "#pragma endregion" in text:
                start = text.find("#pragma region")
                end = text.find("#pragma endregion") + len("#pragma endregion")
                
                # Strip out internal includes meant for separate files so they don't stack up
                block = text[start:end]
                clean_lines = [line for line in block.splitlines() if "JAR-Template/" not in line]
                
                combined_text += "\n".join(clean_lines) + "\n\n"
    return combined_text

def build_and_inject():
    # 2. Gather your split code blocks
    declarations_code = get_pragma_content(HEADER_FILES)
    definitions_code = get_pragma_content(SOURCE_FILES)
    standalone_code = get_pragma_content(STANDALONE_FILES)
    version = get_version(version_file_path)

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

        # 5. Save the finalized main.cpp file back to disk
        with open(f"out/merged_code_{version}.cpp", "w", newline="") as f:
            f.write(main_content)
        with open(version_file_path, "w") as f:
            f.write(str(int(version) + 0.1))  # Increment version for next build
        print("✅ Successfully injected headers into Declarations and source code into Definitions!")
    else:
        print("❌ Error: Could not find the exact empty pragma slots inside src/main.cpp.")
        print("Ensure your main.cpp matches this exact formatting structure:")
        print("#pragma region Declarations\n#pragma endregion\n#pragma region Definitions\n#pragma endregion")

if __name__ == "__main__":
    build_and_inject()
