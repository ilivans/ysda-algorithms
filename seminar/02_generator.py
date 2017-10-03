import random as rnd

rnd.seed(7575466)

size = 10 ** 6
data = [rnd.randint(1, 10 ** 9) for _ in range(size)]
data.sort()
queries = [rnd.randint(1, 10 ** 9) for _ in range(size)]

print(size)
print(' '.join(map(str, data)))
print(len(queries))
print('\n'.join(map(str, queries)))
