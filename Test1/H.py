def builder(n, arr):
    counts = {}
    for char in arr:
        counts[char] = counts.get(char, 0) + 1

    left_side = []
    middle_char = ""
    for char_code in range(ord("A"), ord("Z") + 1):
        char = chr(char_code)
        if char in counts:
            count = counts[char]
            if count >= 2:
                left_side.append(char * (count // 2))
            if count % 2 != 0 and not middle_char:
                middle_char = char

    return "".join(left_side) + middle_char + "".join(reversed(left_side))

N = int(input())
s = input().strip()

print(builder(N, s))