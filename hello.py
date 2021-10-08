import sys
from ctypes import cdll

lib = cdll.LoadLibrary("newplus/libnewplus.so")


def run(count):
    start = lib.current_timestamp()

    x = 0
    while x < count:
        x = lib.plusone(x)

    print(lib.current_timestamp() - start)


def main():
    if len(sys.argv) == 1:
        print("First arg (0 - 2000000000) is required.")
        return

    try:
        count = int(sys.argv[1])
        if count <= 0 or count > 2000000000:
            raise ValueError
    except ValueError:
        print("Must be a positive number not exceeding 2 billion.")
        return

    run(count)


if __name__ == '__main__':
    main()
