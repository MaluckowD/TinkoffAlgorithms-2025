n, c = map(int, input().split())
events = []

for i in range(1, n + 1):
    start_time, duration = map(int, input().split())
    end_time = start_time + duration
    events.append((start_time, end_time, i))

events.sort(key=lambda event: event[1])

selected_events = []
if events:
    selected_events.append(events[0][2])
    current_end_time = events[0][1]

    for start_time, end_time, event_id in events[1:]:
        if start_time >= current_end_time:
            selected_events.append(event_id)
            current_end_time = end_time


total_cost = len(selected_events) * c
print(total_cost)
print(len(selected_events))
print(*selected_events)

