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

total_count = 0
total_count += input_data.count("XMAS")
total_count += input_data.count("SAMX")

print(f"original rotation: {total_count}")

# rotate input input_data 90°
rotated_90 = ["" for _ in range(len(input_data.split("\n")[0]))]

for line in input_data.split("\n"):
    for i in range(len(line)):
        rotated_90[i] += line[i]

# join it
rotated_90 = "\n".join(rotated_90)
print(rotated_90)

total_count += rotated_90.count("XMAS")
total_count += rotated_90.count("SAMX")

print(f"90° rotation: {total_count}")

# rotate input_data by 45°

# 1,1 1,2 1,3
# 2,1 2,2 2,3
# 3,1 3,2 3,3

split_input_data = [ [letter for letter in line ] for line in input_data.split("\n")]

rotated_45 = ["" for _ in range(len(input_data.split("\n")[0]) * 2 - 3)]

for i in range(2, len(input_data.split("\n") * len(input_data.split("\n")[0])) + 1):
    for j in range(1, i):
        # print(f"({j-1}, {i-j-1})")
        if j > len(split_input_data) - 1 or i - j > len(split_input_data) - 1:
            continue
        rotated_45[i-2] += split_input_data[j-1][i-j-1]
    # input(i)

# join it
rotated_45 = "\n".join(rotated_45)
print(rotated_45)

total_count += rotated_45.count("XMAS")
total_count += rotated_45.count("SAMX")

print(f"45° rotation: {total_count}")

# rotate the 90 by 45
split_reversed = [ [letter for letter in reversed(line) ] for line in input_data.split("\n")]

rotated_135 = ["" for _ in range(len(input_data.split("\n")[0]) * 2 - 3)]

for i in range(2, len(input_data.split("\n") * len(input_data.split("\n")[0])) + 1):
    for j in range(1, i):
        # print(f"({j-1}, {i-j-1})")
        if j > len(split_reversed) - 1 or i - j > len(split_reversed) - 1:
            continue
        rotated_135[i-2] += split_reversed[j-1][i-j-1]
    # input(i)

# join it
rotated_135 = "\n".join(rotated_135)
print(rotated_135)

total_count += rotated_135.count("XMAS")
total_count += rotated_135.count("SAMX")

print(f"135° rotation: {total_count}")
print(total_count)
