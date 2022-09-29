from numbers import Number
import random
import typing

arr: typing.List[Number] = []


def divide(
    s: int, e: int, pivot: int
) -> typing.Tuple[typing.List[Number], typing.List[Number]]:
    return list(
        filter(lambda x: x < arr[pivot], arr[s:pivot] + arr[pivot + 1 : e + 1])
    ), list(filter(lambda x: x >= arr[pivot], arr[s:pivot] + arr[pivot + 1 : e + 1]))


def quickSort(s: int, e: int):

    if e <= s:
        return

    pivot = s
    # pivot = (s + e) // 2

    smaller_seg, bigger_seg = divide(s, e, pivot)

    arr[s : e + 1] = smaller_seg + [arr[pivot]] + bigger_seg

    quickSort(s, s + len(smaller_seg) - 1)
    quickSort(e - len(bigger_seg) + 1, e)


if __name__ == "__main__":

    SIZE = 100
    RANGE = 100

    arr = []
    for _ in range(SIZE):
        arr.append(random.randint(-RANGE, RANGE))

    quickSort(0, len(arr) - 1)

    sorted_arr = sorted(arr)
    is_accurate = arr == sorted_arr

    print(arr)

    if is_accurate:
        print("accurate")
    else:
        print("inaccurate")
        print("should be :", sorted_arr)
