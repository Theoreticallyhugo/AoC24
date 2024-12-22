from pathlib import Path
input_data = Path("./input.txt").read_text()

left_list = []
right_list = []

for i, line in enumerate(input_data.strip().split("\n")):
    # input(f"{line} --> {line.split('   ')}")
    try:
        left, right = line.split("   ")
        left_list.append(int(left))
        right_list.append(int(right))
    except:
        input(f"{i}: {line} --> {line.split('   ')}")

left_list = sorted(left_list)
right_list = sorted(right_list)

similarity = dict()

for left in list(set(left_list)):
    counter = 0
    for right in right_list:
        if left == right:
            counter += 1
    similarity[left] = counter

sum = 0
for left, right in zip(left_list, right_list):
    sum += abs(left * similarity[left])

print(sum)
