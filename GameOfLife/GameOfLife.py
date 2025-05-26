def main():
    line = "   ******    "
    start(line)


def start(line):
    print(line)
    tmp = ""
    for i in range(len(line)):
        tmp += born(neighbors(line, i), line, i)
    if "*" in tmp:
        return start(tmp)


def neighbors(line, i):
    cnt = 0
    for j in range(-2, 3):
        go = i + j
        if 0 <= go < len(line) and line[go] == "*" and j != 0:
            cnt += 1
    return cnt


def born(neighbors, line, i):
    return (
        "*"
        if ((neighbors == 2 or neighbors == 3) and line[i] == " ")
        or ((neighbors == 2 or neighbors == 4) and line[i] == "*")
        else " "
    )


main()
