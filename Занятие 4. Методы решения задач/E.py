def can_divide(arr, k, max_sum):
    count = 1  
    current_sum = 0
    for num in arr:
        if num > max_sum:  
            return False
        current_sum += num
        if current_sum > max_sum:
            count += 1
            current_sum = num  
    return count <= k


n, k = map(int, input().split())
arr = list(map(int, input().split()))

left = max(arr)  
right = sum(arr)  

result = right  

while left <= right:
    mid = (left + right) // 2
    if can_divide(arr, k, mid):
        result = mid  
        right = mid - 1  
    else:
        left = mid + 1  

print(result)


