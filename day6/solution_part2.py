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
# row, col, direction_row, direction_col
guard: List[int] = []
initial_guard = []

for i, row in enumerate(input_data.split("\n")):
    for j, symbol in enumerate(row):
        if symbol == ".":
            continue
        elif symbol == "#":
            obstacles.add((i, j))
        elif symbol == "X":
            visited.add((i, j))
        elif symbol == UP:
            initial_guard = [i, j, -1, 0]
        elif symbol == RIGHT:
            initial_guard = [i, j, 0, 1]
        elif symbol == DOWN:
            initial_guard = [i, j, 1, 0]
        elif symbol == LEFT:
            initial_guard = [i, j, 0, -1]



# =========================================
# only places the guard visits need to be checked for possible loops
# so find those places first
# =========================================

def calculate_path(guard, map_size, obstacles, loop_obstacle = []):
    if loop_obstacle:
        obstacles.add(loop_obstacle)
        # print(obstacles)
    # visited coords with their direction
    visited = set()

    while -1 < guard[0] < map_size[0] and -1 < guard[1] < map_size[1]:
        # as long as the guard is inside the map
        if loop_obstacle:
            visited.add(tuple(guard))
        else:
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

        if loop_obstacle and tuple(guard) in visited:
            # we found a loop
            return True

    if loop_obstacle:
        # print(visited)
        return False
    else:
        return visited

visited = calculate_path(initial_guard.copy(), map_size, obstacles)
print("number of tiles visited: ", end="")
print(len(visited))

loop_obstacles = 0

for new_obstacle in visited:
    # do not add the obstacle where the guard starts 
    if new_obstacle == initial_guard[:2]:
        continue
    # input(new_obstacle)
    if calculate_path(initial_guard.copy(), map_size, obstacles.copy(), new_obstacle):
        loop_obstacles += 1

print(f"{loop_obstacles} loop obstacles")
