import re
from pathlib import Path

input_data = Path("./input.txt").read_text().strip()

# input_data = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))"

found_mul = re.findall(r"mul\((\d{1,3}),(\d{1,3})\)", input_data)

total_sum = sum(int(a) * int(b) for a, b in found_mul)

print(found_mul)
print(total_sum)

