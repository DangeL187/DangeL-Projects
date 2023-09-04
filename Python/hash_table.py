import hashlib


def hashCode(string):
    sha256_hash = hashlib.sha256()
    sha256_hash.update(string.encode('utf-8'))
    return int(sha256_hash.hexdigest(), 16)


class HashTable:
    def __init__(self):
        self.names_amount = 0
        self.buckets = [[] for _ in range(5)]

    def add(self, other):
        if not self.contains(other):
            if self.names_amount == len(self.buckets):
                new_buckets = [[] for _ in range(len(self.buckets) * 2)]
                for i in range(len(self.buckets)):
                    for j in range(len(self.buckets[i])):
                        new_buckets[hashCode(self.buckets[i][j][0]) % len(new_buckets)].append(self.buckets[i][j])
                self.buckets = new_buckets
            self.buckets[hashCode(other[0]) % len(self.buckets)].append(other)
            self.names_amount += 1

    def contains(self, other):
        if other in self.buckets[hashCode(other[0]) % len(self.buckets)]:
            return True
        else:
            return False

    def remove(self, other):
        try:
            (self.buckets[hashCode(other[0]) % len(self.buckets)]).remove(other)
        except:
            print('ERROR:', str(other), 'not in list')
        self.names_amount -= 1

    def get(self, other):
        for i in self.buckets[hashCode(other) % len(self.buckets)]:
            if i[0] == other:
                return i[1]
        else:
            return False


if __name__ == "__main__":
    hash_set = HashTable()
    hash_set.add(('Миша', 13))
    hash_set.add(('Рома', 24))
    hash_set.add(('Толя', 14))
    hash_set.add(('Даша', 15))
    hash_set.add(('Катя', 16))
    print(hash_set.buckets)
    hash_set.remove(('Миша', 13))
    print(hash_set.buckets)
    hash_set.add(('Ваня', 18))
    print(hash_set.buckets)
    hash_set.add(('Коля', 19))
    print(hash_set.buckets)
    print()
    print(hash_set.get('Коля'))
