import os
import json

def find_duplicate_sector_codes(directory):
    # Iterate through all files in the specified directory
    for filename in os.listdir(directory):
        if filename.startswith("expected_") and filename.endswith(".json"):

            file_path = os.path.join(directory, filename)
            with open(file_path, "r") as file:
                data = json.load(file)
                duplicates = get_duplicate_sector_codes(data)
                if duplicates:
                    print(f"Duplicate sector codes found in {file_path}: {', '.join(duplicates)}")

def get_duplicate_sector_codes(data):
    sector_codes = set()
    duplicate_codes = set()
    check_duplicate_sector_codes(data, sector_codes, duplicate_codes)
    return list(duplicate_codes)

def check_duplicate_sector_codes(data, sector_codes, duplicate_codes):
    if "sector_code" in data:
        sector_code = data["sector_code"]
        if sector_code in sector_codes:
            duplicate_codes.add(sector_code)
        else:
            sector_codes.add(sector_code)

    for key, value in data.items():
        if isinstance(value, dict):
            check_duplicate_sector_codes(value, sector_codes, duplicate_codes)

if __name__ == "__main__":
    directory_path = "."  # Replace with the actual path to your JSON files directory
    find_duplicate_sector_codes(directory_path)
