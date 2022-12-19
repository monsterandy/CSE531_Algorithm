import sys


def merge_and_count_inversions(a_left, a_right):
    a_left.sort()
    a_right.sort()
    i = 0
    j = 0
    inversions = 0
    while i < len(a_left) and j < len(a_right):
        if a_left[i] <= a_right[j]:
            i += 1
        else:
            inversions += len(a_left) - i
            j += 1
    return inversions
    

def count_inversions(a):
    if len(a) == 1:
        return 0
    a_left = a[:len(a)//2]
    a_right = a[len(a)//2:]
    a_left_inversions = count_inversions(a_left)
    a_right_inversions = count_inversions(a_right)
    merged_inversions = merge_and_count_inversions(a_left, a_right)
    return a_left_inversions + a_right_inversions + merged_inversions


if __name__ == "__main__":
    # read the input
    length = int(sys.stdin.readline())
    input = []
    for line in sys.stdin:
        input.append(int(line))
        length -= 1
        if length == 0:
            break
    
    counts = count_inversions(input)
    print(counts)
        
    