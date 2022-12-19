import sys


def merge_and_count_inversions(a_left, a_right):
    # a_left = qsort(a_left)
    # a_right = qsort(a_right)
    i = 0
    j = 0
    merged = []
    inversions = 0
    while i < len(a_left) and j < len(a_right):
        if a_left[i] <= a_right[j]:
            merged.append(a_left[i])
            i += 1
        else:
            merged.append(a_right[j])
            inversions += len(a_left) - i
            j += 1
    return inversions, merged + a_left[i:] + a_right[j:]
    

def count_inversions(a):
    if len(a) == 1:
        return 0, a
    a_left = a[:len(a)//2]
    a_right = a[len(a)//2:]
    a_left_inversions, merged_left = count_inversions(a_left)
    a_right_inversions, merged_right = count_inversions(a_right)
    merged_inversions, merged = merge_and_count_inversions(merged_left, merged_right)
    return a_left_inversions + a_right_inversions + merged_inversions, merged


if __name__ == "__main__":
    # read the input
    length = int(sys.stdin.readline())
    input = []
    for line in sys.stdin:
        input.append(int(line))
        length -= 1
        if length == 0:
            break
    
    counts, _ = count_inversions(input)
    print(counts)
        
    