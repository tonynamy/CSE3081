from numbers import Number
import random
import typing

arr: typing.List[Number] = []


def insertionSort():
    for i in range(1, len(arr)):

        j = 0

        while j <= i:
            if arr[j] >= arr[i]:
                break
            j += 1

        t = arr[i]
        del arr[i]
        arr.insert(j, t)


if __name__ == "__main__":

    SIZE = 10
    RANGE = 100

    for _ in range(SIZE):
        arr.append(random.randint(-RANGE, RANGE))

    insertionSort()

    sorted_arr = sorted(arr)
    is_accurate = arr == sorted_arr

    print(arr)

    if is_accurate:
        print("accurate")
    else:
        print("inaccurate")
        print("should be :", sorted_arr)
