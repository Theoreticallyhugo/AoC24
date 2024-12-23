import re
from pathlib import Path

input_data = Path("./input.txt").read_text().strip()

input_data = """MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX"""
print(input_data)

# split input_data into 2d array

split_in = [ [letter for letter in line ] for line in input_data.split("\n")]
print(split_in)

"""
we move a 3x3 grid. the top left character is the anchor point
"""

# length of lines
# since its a square, its also the length of columns
max_len = len(split_in)
temp_list = []
xmas_count = 0

for i in range(max_len - 2):
    for j in range(max_len - 2):
        temp_list = split_in[i][j:j+3]
        temp_list += split_in[i+1][j:j+3]
        temp_list += split_in[i+2][j:j+3]
        # input(temp_list)

        # the middle needs to be "A"
        if temp_list[4] != "A":
            continue

        if temp_list[0] == "M" and temp_list[2] == "M" and \
                temp_list[6] == "S" and temp_list[8] == "S":
            xmas_count += 1;
        elif temp_list[0] == "S" and temp_list[2] == "M" and \
                temp_list[6] == "S" and temp_list[8] == "M":
            xmas_count += 1;
        elif temp_list[0] == "S" and temp_list[2] == "S" and \
                temp_list[6] == "M" and temp_list[8] == "M":
            xmas_count += 1;
        elif temp_list[0] == "M" and temp_list[2] == "S" and \
                temp_list[6] == "M" and temp_list[8] == "S":
            xmas_count += 1;
        # else:
        #     print(i, j)
        #     input(temp_list)
        # elif temp_list[0] == "S" and temp_list[2] == "M" and \
        #         temp_list[6] == "M" and temp_list[8] == "S":
        #     xmas_count += 1;
        # elif temp_list[0] == "M" and temp_list[2] == "S" and \
        #         temp_list[6] == "S" and temp_list[8] == "M":
        #     xmas_count += 1;

print(xmas_count)
