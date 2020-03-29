import time
import random


def bubble_sort(l, size):
    if size > 5000:
        print("Too many values!")
        return
    for i in range(size):
        for j in range(size - i - 1):
            if l[j] > l[j + 1]:
                l[j], l[j + 1] = l[j + 1], l[j]

    return l


def count_sort(l, m):
    if m > 10**6:
        print("maxValue too big! Can't sort")
        return
    m += 1
    f = [0]*m
    for val in l:
        f[val] += 1
    newList = []
    for i in range(m):
        newList += [i]*f[i]
    return newList


def radix_sort_b256(l):
    maxShift = 4
    lead = 1 << 8
    bitesEven = [[] for _ in range(256)]
    bitesOdd = [l] + [[] for _ in range(255)]
    even = True
    lead = lead - 1
    for shift in range(maxShift):

        if(even):
            for values in bitesOdd:
                for val in values:
                    leadBites = val & lead
                    leadBites = leadBites >> 8*shift
                    bitesEven[leadBites] += [val]
            bitesOdd = [[] for _ in range(256)]

        else:
            for values in bitesEven:
                for val in values:
                    leadBites = val & lead
                    leadBites = leadBites >> 8*shift
                    bitesOdd[leadBites] += [val]
            bitesEven = [[] for _ in range(256)]

        even = not even
        lead = lead << 8

    return bitesOdd[0]


def find_pivot(start, end):
    middle = start + end//2
    if min(middle, end) <= start <= max(middle, end):
        return start
    elif min(start, end) <= middle <= max(start,end):
        return middle
    return end


def partition(array, start, end):
    pivot = find_pivot(start, end)
    array[start], array[pivot] = array[pivot], array[start]
    pivot = array[start]
    left = start + 1
    right = end

    while True:

        while left <= right and array[right] >= pivot:
            right = right - 1

        while left <= right and array[left] <= pivot:
            left = left + 1

        if left <= right:
            array[left], array[right] = array[right], array[left]
        else:
            break

    array[start], array[right] = array[right], array[start]

    return right


def quick_sort(l, start, end):
    if end - start == 1:
        if l[start] > l[end]:
            l[start], l[end] = l[end], l[start]
        return
    if start >= end:
        return

    p = partition(l, start, end)
    quick_sort(l, start, p - 1)
    quick_sort(l, p + 1, end)

    return l


def merge_sort(l, listSize):
    b=[0]*listSize
    hasChanged = True
    while hasChanged is True:
        hasChanged = False
        leftIsSet = False
        leftStart = 0
        rigthStart = 0
        previous = -1
        delim = 0
        for i in range(listSize +1):
            if i == listSize or l[i] < previous:
                if leftIsSet:
                    delim = i
                    iLeft = leftStart
                    iRight = rigthStart
                    for k in range(leftStart, delim):
                        if iLeft < rigthStart and (iRight >= delim or l[iLeft] <= l[iRight]):
                            b[k] = l[iLeft]
                            iLeft += 1
                        else:
                            b[k] = l[iRight]
                            iRight += 1
                    leftStart = i
                    leftIsSet = False
                else:
                        rigthStart = i
                        leftIsSet= True
            if i != listSize:
                previous = l[i]
        for i in range(delim, listSize):
            b[i] = l[i]
        leftIsSet = False
        leftStart = 0
        rigthStart = 0
        previous = -1
        delim = 0
        for i in range(listSize + 1):
            if i == listSize or b[i] < previous:
                if leftIsSet:
                    hasChanged = True
                    delim = i
                    iLeft = leftStart
                    iRight = rigthStart
                    for k in range(leftStart, delim):
                        if iLeft < rigthStart and (iRight >= delim or b[iLeft] <= b[iRight]):
                            l[k] = b[iLeft]
                            iLeft += 1
                        else:
                            l[k] = b[iRight]
                            iRight += 1
                    leftStart = i
                    leftIsSet = False
                else:
                    rigthStart = i
                    leftIsSet = True
            if i != listSize:
                previous = b[i]
        for i in range(delim, listSize):
            l[i] = b[i]

    return l


fin = open("teste.txt", "r")
testNumber = int(fin.readline())
for test in range(testNumber):
    line = fin.readline().split()
    size = int(line[0])
    maxVal = int(line[1])
    v = [random.randint(1, maxVal) for _ in range(size)]
    v_bubble = v.copy()
    v_count = v.copy()
    v_quick = v.copy()
    v_radix = v.copy()
    v_merge = v.copy()
    ts = time.time()
    v.sort()
    te = time.time()
    print("native sort time:" + str(te-ts))
    ts = time.time()
    v_bubble = bubble_sort(v_bubble, size)
    te = time.time()
    if v_bubble == v:
        print("bubble_sort sorted successfully in: " + str(te-ts))
    else:
        print("bubble sort couldn't sort")
    ts = time.time()
    v_count = count_sort(v_count, maxVal)
    te = time.time()
    if v_count == v:
        print("count_sort sorted successfully in: " + str(te-ts))
    else:
        print("count sort couldn't sort")
    ts = time.time()
    v_quick = quick_sort(v_quick, 0, size-1)
    te = time.time()
    if v_quick == v:
        print("quick_sort sorted successfully in: " + str(te - ts))
    else:
        print("quick sort couldn't sort")
    ts = time.time()
    v_radix = radix_sort_b256(v_radix)
    te = time.time()
    if v_radix == v:
        print("radix_sort sorted successfully in: " + str(te - ts))
    else:
        print("radix sort couldn't sort")
    ts = time.time()
    v_merge = merge_sort(v_merge, size)
    te = time.time()
    if v_merge == v:
        print("merge_sort sorted successfully in: " + str(te - ts))
    else:
        print("merge sort couldn't sort")
