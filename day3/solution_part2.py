import re
from pathlib import Path

input_data = Path("./input.txt").read_text().strip().replace("\n", "")

# input_data = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))don't()mul(30,30))do()"

# remove everything between dont and do
input_data = re.sub(r"don't\(\).*?do\(\)", "", input_data)
input("don't()" in input_data)
input(input_data.count("don't()"))
# remove everything after the last remaining dont which was unmatched because there was no do
input_data = re.sub(r"don't\(\).*", "", input_data)

found_mul = re.findall(r"mul\((\d{1,3}),(\d{1,3})\)", input_data)

total_sum = sum(int(a) * int(b) for a, b in found_mul)

print(found_mul)
print(total_sum)

