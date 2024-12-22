from pathlib import Path

input_data = [report.strip().split() for report in Path("./input.txt").read_text().strip().split("\n")]

input_data = list(map(lambda x: list(map(int, x)), input_data))

safe_reports = 0

def check_report(report):
    did_break = False
    previous = report[0]
    if report[0] < report[1]:
        # increasing
        for level in report[1:]: 
            if level < previous:
                did_break = True
            elif level == previous:
                did_break = True
            elif abs(level - previous) > 3:
                did_break = True
            previous = level
    else: 
        # decreasing
        for level in report[1:]: 
            if level > previous:
                did_break = True
            elif level == previous:
                did_break = True
            elif abs(level - previous) > 3:
                did_break = True
            previous = level
    return did_break

for report in input_data:
    did_break = check_report(report)
    if did_break:
        for i in range(len(report)):
            did_break = check_report(report[0:i] + report[i+1:])
            if not did_break:
                safe_reports += 1
                break
                
        # input(f"{report} did break")
    else:
        # input(f"{report} was fine")
        safe_reports += 1


print(safe_reports)
