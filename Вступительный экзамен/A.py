n, a = map(int, input().split())
arrivals = list(map(int, input().split()))

finish_times = []
current_time = 0

for arrival_time in arrivals:
  start_time = max(current_time, arrival_time)
  finish_time = start_time + a
  finish_times.append(finish_time)
  current_time = finish_time
  
print(*finish_times, sep = '\n')
