import fileinput
import math
import re
import sys
from typing import Dict, Iterator, List, NamedTuple, Set, Tuple, Union, cast


class Result(NamedTuple):
    distance: Union[int, float]
    intermidiate: Iterator[str]


def generate_spf(edges: Dict[Tuple[str, str], int], adjacencies: Dict[str, Set[str]], start: str):
    distances = {start: 0}
    previous = {start: start}

    candidates = {start, }
    visited: Set[str] = set()

    while candidates:
        u = cast(str, min(candidates, key=distances.get))
        for v in adjacencies.get(u, set()):
            if v in visited:
                continue
            distance = distances.get(u, math.inf) + \
                edges.get((u, v), math.inf)
            if distance < distances.get(v, math.inf):
                distances[v] = distance
                previous[v] = u
                candidates.add(v)
        candidates.remove(u)
        visited.add(u)

    results: Dict[str, Result] = dict()
    for v in distances:
        # walk back "previous" to get path
        u = v
        path = [v]
        while previous[u] != u:
            u = previous[u]
            path.append(u)
        results[v] = Result(distances[v], reversed(path[1:-1]))

    return results


def generate_functors(edges: Dict[Tuple[str, str], int], adjacencies: Dict[str, Set[str]]):
    spf_map: Dict[str, Dict[str, Result]] = dict()

    def distance(*args: str):
        distance = 0
        for i in range(len(args) - 1):
            u, v = args[i], args[i + 1]
            if u not in spf_map:
                spf_map[u] = generate_spf(edges, adjacencies, u)
            distance += spf_map[u].get(v, Result(math.inf, [])).distance
        return distance

    def path(*args: str):
        path: List[str] = list()
        for i in range(len(args) - 1):
            u, v = args[i], args[i + 1]
            path.append(u)
            if u not in spf_map:
                spf_map[u] = generate_spf(edges, adjacencies, u)
            path.extend(spf_map[u][v].intermidiate)
        path.append(args[-1])
        return path

    return distance, path


def parse():
    nodes_re = re.compile('(\w+)\s+(\w+)\s+(\w+)\s+(\w+)')
    edge_re = re.compile('(\w+) -> (\w+): (\d+)')

    edges: Dict[Tuple[str, str], int] = dict()
    adjacencies: Dict[str, Set[str]] = dict()

    # read from standard input and parse each line
    lines = cast(Iterator[str], (line for line in fileinput.input()))
    for line in lines:
        match = edge_re.search(line)
        if match:
            u, v, w = match.group(1), match.group(2), int(match.group(3))
            edges[(u, v)] = w

            if u in adjacencies:
                adjacencies[u].add(v)
            else:
                adjacencies[u] = {v, }
            continue

        match = nodes_re.search(line)
        if match:
            start, finish, mask, alcohol = match.group(1), match.group(2), \
                match.group(3), match.group(4)
            continue

    distance, path = generate_functors(edges, adjacencies)

    return (start, finish, mask, alcohol, distance, path)


def main():
    start, finish, mask, alcohol, distance, path = parse()

    mask_first_distance = distance(start, mask, alcohol, finish)
    alcohol_first_distance = distance(start, alcohol, mask, finish)

    if mask_first_distance < alcohol_first_distance:
        solution = path(start, mask, alcohol, finish)
        distance = mask_first_distance
    else:
        solution = path(start, alcohol, mask, finish)
        distance = alcohol_first_distance

    print(' '.join(solution))
    print(distance)

    return 0


if __name__ == '__main__':
    sys.exit(main())
