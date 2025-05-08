import sys
from typing import List, Set

def simulate_monsters(n: int, attack_powers: List[int], defense_values: List[int]) -> str:
    attack_powers.append(0)  
    
    if n == 1:
        return "0"
    
    left_neighbor = [i - 1 for i in range(n)]
    right_neighbor = [i + 1 for i in range(n)]
    total_attack = [0] * n
    dead_monsters = []  
    
    total_attack[0] = attack_powers[1]
    if defense_values[0] < attack_powers[1]:
        dead_monsters.append(0)
    
    for i in range(1, n - 1):
        total_attack[i] = attack_powers[i - 1] + attack_powers[i + 1]
        if defense_values[i] < total_attack[i]:
            dead_monsters.append(i)
    
    total_attack[n - 1] = attack_powers[n - 2]
    if defense_values[n - 1] < attack_powers[n - 2]:
        dead_monsters.append(n - 1)
    
    result = [str(len(dead_monsters))]
    already_dead = set(dead_monsters)
    
    for _ in range(n - 1):
        new_dead = []
        affected_monsters = set()
        
        for monster in dead_monsters:
            left = left_neighbor[monster]
            right = right_neighbor[monster]
            
            if left >= 0:
                right_neighbor[left] = right
                affected_monsters.add(left)
            if right < n:
                left_neighbor[right] = left
                affected_monsters.add(right)
            
            if 0 <= left < n:
                total_attack[left] += attack_powers[right] - attack_powers[monster]
            if 0 <= right < n:
                total_attack[right] += attack_powers[left] - attack_powers[monster]
        
        for monster in affected_monsters:
            if total_attack[monster] > defense_values[monster] and monster not in already_dead:
                new_dead.append(monster)
                already_dead.add(monster)
        
        dead_monsters = new_dead
        result.append(str(len(dead_monsters)))
    
    return ' '.join(result)



input = sys.stdin.read
data = input().split()

n = int(data[0])
a = list(map(int, data[1:n+1]))
d = list(map(int, data[n+1:2*n+1]))

print(simulate_monsters(n, a, d))


