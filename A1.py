
def hash_function(key, size):
    return key % size


class ChainingHashTable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def insert(self, key, value):
        index = hash_function(key, self.size)
        self.table[index].append((key, value))

    def search(self, key):
        index = hash_function(key, self.size)
        comparisons = 0
        for k, v in self.table[index]:
            comparisons += 1
            if k == key:
                return v, comparisons
        return None, comparisons


class LinearProbingHashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size

    def insert(self, key, value):
        index = hash_function(key, self.size)
        start_index = index
        while self.table[index] is not None:
            index = (index + 1) % self.size
            if index == start_index:
                print("Table is full!")
                return
        self.table[index] = (key, value)

    def search(self, key):
        index = hash_function(key, self.size)
        start_index = index
        comparisons = 0
        while self.table[index] is not None:
            comparisons += 1
            if self.table[index][0] == key:
                return self.table[index][1], comparisons
            index = (index + 1) % self.size
            if index == start_index:
                break
        return None, comparisons


def main():
    size = 10
    chaining_table = ChainingHashTable(size)
    linear_table = LinearProbingHashTable(size)

    while True:
        print("\n--- Telephone Book Menu ---")
        print("1. Add client")
        print("2. Search client")
        print("3. Exit")
        choice = input("Enter your choice: ")

        if choice == '1':
            key = int(input("Enter client ID (integer): "))
            number = input("Enter telephone number: ")
            chaining_table.insert(key, number)
            linear_table.insert(key, number)
            print("Added successfully to both tables.")

        elif choice == '2':
            key = int(input("Enter client ID to search: "))
            value_c, comp_c = chaining_table.search(key)
            value_l, comp_l = linear_table.search(key)

            print("\n-- Chaining Search --")
            if value_c:
                print(f"Found number: {value_c}, Comparisons: {comp_c}")
            else:
                print(f"Number not found, Comparisons: {comp_c}")

            print("-- Linear Probing Search --")
            if value_l:
                print(f"Found number: {value_l}, Comparisons: {comp_l}")
            else:
                print(f"Number not found, Comparisons: {comp_l}")

        elif choice == '3':
            print("Goodbye!")
            break

        else:
            print("Invalid choice, try again.")

if __name__ == "__main__":
    main()
