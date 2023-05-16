#!/usr/bin/python3
'''
script that finds a string in the heap of a running process, and replaces it
'''

import sys


def find_heap_address(pid):
    maps_path = "/proc/{}/maps".format(pid)

    with open(maps_path) as maps:
        for line in maps:
            if "[heap]" in line:
                address_range, mode = line.split()[:2]
                start, end = map(lambda x: int('0x' + x, 16),
                                 address_range.split('-'))
                return {
                    "start": start,
                    "end": end,
                    "mode": mode
                }

    return None


def replace_string_in_heap(pid, search_string, replace_string):
    mem_path = "/proc/{}/mem".format(pid)
    heap = find_heap_address(pid)

    if heap is None:
        print("Heap not found")
        return

    if replace_string == '':
        replace_string = ' ' * len(search_string)

    with open(mem_path, 'rb+') as mem:
        mem.seek(heap['start'])
        heap_memory = mem.read(heap['end'] - heap['start'])

        try:
            i = heap_memory.index(bytes(search_string, "ASCII"))
        except ValueError:
            print("No matching string found")
            return

        mem.seek(heap['start'] + i)
        mem.write(bytes(replace_string, "ASCII"))


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: {} pid search_string replace_string".format(sys.argv[0]))
        sys.exit(1)

    pid, search, replace = sys.argv[1:]
    if "" in [pid, search]:
        print("Missing value")
        sys.exit(1)

    replace_string_in_heap(pid, search, replace)
