from pathlib import Path
import re

input_data = Path("./input.txt").read_text().strip()

# input_data = """47|53
# 97|13
# 97|61
# 97|47
# 75|29
# 61|13
# 75|53
# 29|13
# 97|29
# 53|29
# 61|53
# 97|53
# 61|29
# 47|13
# 75|47
# 97|75
# 47|61
# 75|61
# 47|29
# 75|13
# 53|13
#
# 75,47,61,53,29
# 97,61,53,29,13
# 75,29,13
# 75,97,47,61,53
# 61,13,29
# 97,13,75,29,47""".strip()
print(input_data)

def parse_input(input_data):
    # find all ordering rules
    order_rules = re.findall(r"(\d{2})\|(\d{2})", input_data)
    # cast all to int
    order_rules = tuple(tuple(int(digit) for digit in curr_rule) for curr_rule in order_rules)
    # and print them
    # print(order_rules)

    orders_to_check = []
    # skip the lines with order rules and the empty line
    for line in input_data.split("\n")[len(order_rules) + 1:]:
        orders_to_check.append(tuple( int(number) for number in line.split(",")))
        # print(line)
    orders_to_check = tuple(orders_to_check)

    return order_rules, orders_to_check

order_rules, orders_to_check = parse_input(input_data)

sum_middle_pages = 0
for order in orders_to_check:
    # print(order)
    order_correct = True
    for left_rule, right_rule in order_rules:
        try:
            # find numbers if present
            left_index = order.index(left_rule)
            right_index = order.index(right_rule)
            # input(f"found {left_rule} at {left_index}, and {right_rule} at {right_index}.")
        except ValueError:
            # input(f"{left_rule} and/or {right_rule} not present")
            # one or both of the rule numbers are not included
            continue

        if left_index > right_index:
            order_correct = False
            break
    if order_correct:
        sum_middle_pages += order[(len(order) - 1) // 2]

print(sum_middle_pages)
