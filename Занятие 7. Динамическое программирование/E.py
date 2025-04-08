def damerau_levenshtein_distance(str1, str2):

    len1 = len(str1)
    len2 = len(str2)
    d = [[0] * (len2 + 1) for _ in range(len1 + 1)]
    
    for i in range(len1 + 1):
        d[i][0] = i
    for j in range(len2 + 1):
        d[0][j] = j
    
    for i in range(1, len1 + 1):
        for j in range(1, len2 + 1):
            cost = 0 if str1[i-1] == str2[j-1] else 1
            
            d[i][j] = min(
                d[i-1][j] + 1,      
                d[i][j-1] + 1,      
                d[i-1][j-1] + cost
            )
            
            if (i > 1 and j > 1 and 
                str1[i-1] == str2[j-2] and 
                str1[i-2] == str2[j-1]):
                d[i][j] = min(d[i][j], d[i-2][j-2] + cost)
    
    return d[len1][len2]


string1 = input().strip()
string2 = input().strip()

distance = damerau_levenshtein_distance(string1, string2)
print(distance)