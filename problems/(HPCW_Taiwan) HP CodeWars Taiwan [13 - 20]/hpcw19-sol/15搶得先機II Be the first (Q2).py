#!/usr/bin/env python3
import re
from functools import reduce
from collections import deque


def bfs(maze, start, end):
    def inbound(x, y, maze):
        return 0 <= x < len(maze[0]) and 0 <= y < len(maze)

    route = deque([(tuple(), start)])
    paths = list()
    while route:
        path, pos = route.popleft()
        x, y = pos
        if pos in path:
            continue
        if not int(maze[y][x]):
            path += (pos, )
            if pos == end:
                paths.append(path)
            route.extend((path, ptr) for ptr in ((x+1, y), (x, y+1), (x-1, y), (x, y-1))
                         if inbound(*ptr, maze))
    return paths


def find_routes(maze, identifies='zabcdefghijklmnopqrstuvwxy'):
    routes, fail = dict(), False
    for char in identifies:
        for y, row in enumerate(maze):
            try:
                x = row.index(char)
                routes[char] = (x, y)
                fail = False
                break
            except ValueError:
                fail = True
        if fail:
            break
    return routes


def main(lines):
    m_str = "\n".join(lines)
    routes = find_routes(lines)
    maze = re.sub('[%s]' % "".join(routes), '0', m_str).split("\n")
    paths = [routes[k] for k in sorted(routes)]
    paces = [min(bfs(maze, start, end), key=len)
             for start, end in zip(paths, paths[1:])]
    paces = reduce(lambda x, y: x + list(y)[:-1], paces, []) + [paths[-1]]
    print("-".join("%X%X" % (x, y) for x, y in paces))


if __name__ == '__main__':
    lines = []
    while True:
        try:
            line = input()
        except EOFError:
            break
        else:
            lines.append(line)

    main(lines)
