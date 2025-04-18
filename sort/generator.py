import os
import random


def generate_array(size, array_type='random'):
    if array_type == 'random':
        return [random.randint(0, size) for _ in range(size)]
    elif array_type == 'sorted':
        return list(range(size))
    elif array_type == 'reversed':
        return list(range(size, 0, -1))
    elif array_type == 'almost_sorted':
        arr = list(range(size))
        for _ in range(size // 10): 
            i, j = random.randint(0, size - 1), random.randint(0, size - 1)
            arr[i], arr[j] = arr[j], arr[i]
        return arr
    elif array_type == 'few_unique':
        return [random.choice([2341425, 2456745, 3349233, 4765473,4531245]) for _ in range(size)]
    else:
        raise ValueError(f"Unknown array type: {array_type}")

def save_array_to_file(arr, filename):
    with open(filename, 'w') as f:
        f.write(str(len(arr)) + "\n")
        chunk_size = 1000 
        for i in range(0, len(arr), chunk_size):
            f.write(' '.join(map(str, arr[i:i+chunk_size])) + "\n")

def generate_and_save_all(sizes, types, folder='Tests'):
    os.makedirs(folder, exist_ok=True)
    for size in sizes:
        for array_type in types:
            arr = generate_array(size, array_type)
            filename = os.path.join(folder, f"{array_type}_{size}.txt")
            save_array_to_file(arr, filename)
            print(f"Saved {filename}")

if __name__ == "__main__":
    sizes = [10_000_000,50_000_000,100_000_000,500_000_000] 
    types = ['random', 'sorted', 'reversed', 'almost_sorted', 'few_unique']
    generate_and_save_all(sizes, types)
