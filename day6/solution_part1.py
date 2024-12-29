from pathlib import Path
from typing import List, Tuple, Set

UP = "^"
RIGHT = ">"
DOWN = "V"
LEFT = "<"

input_data = Path("./input.txt").read_text().strip()

# input_data = """....#.....
# .........#
# ..........
# ..#.......
# .......#..
# ..........
# .#..^.....
# ........#.
# #.........
# ......#...""".strip()

# TOP LEFT IS COORD (0, 0)

obstacles: Set[Tuple[int, int]] = set()
# num rows, num cols
map_size: Tuple[int, int] = (len(input_data.split("\n")), len(input_data.split("\n")[0]))
visited: Set[Tuple[int, int]] = set()
# row, col, direction_row, direction_col
guard: List[int] = []

for i, row in enumerate(input_data.split("\n")):
    for j, symbol in enumerate(row):
        if symbol == ".":
            continue
        elif symbol == "#":
            obstacles.add((i, j))
        elif symbol == "X":
            visited.add((i, j))
        elif symbol == UP:
            guard = [i, j, -1, 0]
        elif symbol == RIGHT:
            guard = [i, j, 0, 1]
        elif symbol == DOWN:
            guard = [i, j, 1, 0]
        elif symbol == LEFT:
            guard = [i, j, 0, -1]

while -1 < guard[0] < map_size[0] and -1 < guard[1] < map_size[1]:
    # as long as the guard is inside the map
    visited.add(tuple(guard[:2]))

    # try to move the guard
    new_pos = (guard[0] + guard[2], guard[1] + guard[3])

    if new_pos in obstacles:
        # rotate
        if guard[2] != 0:
            # UP or DOWN
            guard[3] = guard[2] * -1
            guard[2] = 0
        else:
            # LEFT or RIGHT
            guard[2] = guard[3]
            guard[3] = 0
    else:
        # move
        guard[0] = new_pos[0]
        guard[1] = new_pos[1]
        # input(guard)

print(len(visited))


