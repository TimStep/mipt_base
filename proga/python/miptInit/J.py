def invert_array(arr, N):
    outarr = []
    for i in range(N-1, -1, -1):
        outarr.append(arr[i])
    return outarr
