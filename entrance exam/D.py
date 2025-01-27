def max_balanced_size(n, m, k, a, c):
    # Создаем массив b
    b = []
    for i in range(n):
        b.extend([a[i]] * c[i])

    # Сортируем массив b
    b.sort()

    # Переменная для хранения максимального суммарного размера
    max_size = 0
    # Количество последовательностей, которые мы можем создать
    sequences = []

    # Ищем места, где можно начать новую последовательность
    for i in range(len(b)):
        if not sequences or b[i] - sequences[-1] >= k:
            # Если можно начать новую последовательность
            if len(sequences) < m:
                # Создаем новую последовательность
                sequences.append(b[i])
                if len(sequences) == 1:
                    # Если это первая последовательность
                    max_size += c[a.index(b[i])]
                else:
                    # Увеличиваем максимальный размер
                    max_size += c[a.index(b[i])]

    return max_size

# Пример использования
n, m, k = map(int, input().split())
a = list(map(int, input().split()))
c = list(map(int, input().split()))

result = max_balanced_size(n, m, k, a, c)
print(result)
