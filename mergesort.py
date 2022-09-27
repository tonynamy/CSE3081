import random


arr = []


def merge(l: int, m: int, r: int):

    if r <= l:
        return

    larr = arr[l : m + 1]
    rarr = arr[m + 1 : r + 1]

    ldx = 0
    rdx = 0

    while ldx < len(larr) or rdx < len(rarr):
        if ldx == len(larr):
            arr[l + ldx + rdx] = rarr[rdx]
            rdx += 1
        elif rdx == len(rarr):
            arr[l + ldx + rdx] = larr[ldx]
            ldx += 1
        elif larr[ldx] < rarr[rdx]:
            arr[l + ldx + rdx] = larr[ldx]
            ldx += 1
        else:
            arr[l + ldx + rdx] = rarr[rdx]
            rdx += 1


def mergeSort(l: int, r: int):
    if r <= l:
        return

    m = (l + r) // 2

    mergeSort(l, m)
    mergeSort(m + 1, r)
    merge(l, m, r)


if __name__ == "__main__":

    SIZE = 1000
    RANGE = 100

    for _ in range(SIZE):
        arr.append(random.randint(-RANGE, RANGE))

    mergeSort(0, len(arr) - 1)

    sorted_arr = sorted(arr)
    is_accurate = arr == sorted_arr

    print(arr)

    if is_accurate:
        print("accurate")
    else:
        print("inaccurate")
        print("should be :", sorted_arr)
