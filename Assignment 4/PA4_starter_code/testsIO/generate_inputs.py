import os
import random
import math

def sector_code(x, y, z):
	# Calculate distance from earth
	distance_from_earth = math.sqrt(x**2 + y**2 + z**2)

	# Convert distance to integer and create sector code
	code = str(int(distance_from_earth))

	# Check each coordinate and append the appropriate letter
	code += "S" if x == 0 else ("R" if x > 0 else "L")
	code += "S" if y == 0 else ("U" if y > 0 else "D")
	code += "S" if z == 0 else ("F" if z > 0 else "B")

	return code
	
	
def create_input_files_csv(num_files, directory):
	"""
	Create a specified number of input files with unique test data in CSV format for the assignment.

	Parameters:
	num_files (int): The number of files to create
	directory (str): The directory where the files will be saved
	"""
	if not os.path.exists(directory):
		os.makedirs(directory)

	for file_num in range(1, num_files + 1):
		file_name = f"sectors_{file_num}.dat"
		file_path = os.path.join(directory, file_name)

		with open(file_path, 'w') as file:
			
			codes = set()
			
			# Writing header
			file.write("X,Y,Z\n")
			file.write("0,0,0\n")

			# Generating random coordinates (X, Y, Z) for space sectors
			for _ in range(random.randint(5, 50)):  # Random number of lines per file
			
				while True:
					x = random.randint(-100, 100)
					y = random.randint(-100, 100)
					z = random.randint(-100, 100)
					
					code = sector_code(x,y,z)
					if code not in codes:
						file.write(f"{x},{y},{z}\n")
						codes.add(code)
						break
						
# Directory to save the input files
directory_csv = "inputs"

# Creating 50 input files in CSV format
create_input_files_csv(50, directory_csv)

print(f"50 input files have been created in {directory_csv}")
