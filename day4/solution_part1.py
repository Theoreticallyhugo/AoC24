from pathlib import Path

input_data = Path("./input.txt").read_text().strip()

XMAS = "XMAS"

# input_data = """MMMSXXMASM
# MSAMXMSMSA
# AMXSXMAAMM
# MSAMASMSMX
# XMASAMXAMM
# XXAMMXXAMA
# SMSMSASXSS
# SAXAMASAAA
# MAMMMXMMMM
# MXMXAXMASX"""
print(input_data)

total_count = 0
total_count += input_data.count(XMAS)
total_count += input_data.count(XMAS[::-1])

print(f"original rotation: {total_count}")

# rotate input input_data 90°
rotated_90 = ["" for _ in range(len(input_data.split("\n")[0]))]

for line in input_data.split("\n"):
    for i in range(len(line)):
        rotated_90[i] += line[i]

# join it
rotated_90 = "\n".join(rotated_90)
print(rotated_90)

total_count += rotated_90.count(XMAS)
total_count += rotated_90.count(XMAS[::-1])

print(f"90° rotation: {total_count}")

# rotate input_data by 45°

# 0,0 0,1 0,2 x,3 x,4 x,5
# 1,0 1,1 1,2 y,3 y,4
# 2,0 2,1 2,2 z,3

split_input_data = [ [letter for letter in line ] for line in input_data.split("\n")]

rotated_45 = ["" for _ in range(len(input_data.split("\n")[0]) * 2)]

# for i in range(len(input_data.split("\n")[0]) * 2):
    
max_len = len(input_data.split("\n"))

for i in range(2 * max_len + 1):
    for j in range(i + 1):
        # input(f"({j}, {i-j})")
        if j > len(split_input_data) - 1 or i - j > len(split_input_data) - 1:
            continue
        rotated_45[i] += split_input_data[j][i-j]
    # input(i)

# join it
rotated_45 = "\n".join(rotated_45)
print(rotated_45)

total_count += rotated_45.count(XMAS)
total_count += rotated_45.count(XMAS[::-1])

print(f"45° rotation: {total_count}")

# rotate the 90 by 45
split_reversed = [ [letter for letter in reversed(line) ] for line in input_data.split("\n")]

rotated_135 = ["" for _ in range(len(input_data.split("\n")[0]) * 2)]

for i in range(2 * max_len + 1):
    for j in range(i + 1):
        # input(f"({j}, {i-j})")
        if j > len(split_reversed) - 1 or i - j > len(split_reversed) - 1:
            continue
        rotated_135[i] += split_reversed[j][i-j]
    # input(i)

# join it
rotated_135 = "\n".join(rotated_135)
print(rotated_135)

total_count += rotated_135.count(XMAS)
total_count += rotated_135.count(XMAS[::-1])

print(f"135° rotation: {total_count}")
print(total_count)
