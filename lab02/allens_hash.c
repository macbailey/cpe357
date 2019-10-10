import fractions

# Allan Gomez
# CPE 202


class HashTable:

    def __init__(self, table_size=191):     # can add additional attributes
        self.table_size = table_size        # initial table size
        self.hash_table = [None]*table_size # hash table
        self.num_items = 0                  # empty hash table

    def insert(self, key, value):
        """ Inserts an entry into the hash table (using Horner hash function to determine index, 
        and quadratic probing to resolve collisions).
        The key is a string (a word) to be entered, and value is the line number that the word appears on. 
        If the key is not already in the table, then the key is inserted, and the value is used as the first 
        line number in the list of line numbers. If the key is in the table, then the value is appended to that 
        key’s list of line numbers. If value is not used for a particular hash table (e.g. the stop words hash table),
        can use the default of 0 for value and just call the insert function with the key.
        If load factor is greater than 0.5 after an insertion, hash table size should be increased (doubled + 1)."""
        hash_key = self.horner_hash(key)
        quad = 1
        fin_hash = hash_key

        while self.hash_table[fin_hash % self.table_size] != None and self.hash_table[fin_hash % self.table_size][
            0] != key:
            fin_hash += quad
            quad += 2
        if self.hash_table[(fin_hash) % self.table_size] == None:
            self.hash_table[(fin_hash) % self.table_size] = (key, [value])
            self.num_items += 1
        elif self.hash_table[(fin_hash) % self.table_size][0] == key:
            if value > self.hash_table[(fin_hash) % self.table_size][1][
                len(self.hash_table[(fin_hash) % self.table_size][1]) - 1]:
                self.hash_table[(fin_hash) % self.table_size][1].append(value)

        # implement table doubling
        if self.get_load_factor() > 0.5:
            newSize = self.table_size * 2 + 1
            temphash = [None] * (newSize)
            self.table_size = newSize
            for k in self.hash_table:
                if k != None:
                    hashval = self.horner_hash(k[0])
                    quad = 1
                    fin_hash = hashval
                    while temphash[fin_hash % self.table_size] != None:
                        fin_hash += quad
                        quad += 2
                    temphash[fin_hash % self.table_size] = k
            self.hash_table = temphash

    def horner_hash(self, key):
        """ Compute and return an integer from 0 to the (size of the hash table) - 1
        Compute the hash value by using Horner’s rule, as described in project specification."""
        h_hash = 0
        i = 0
        n = min(8, len(key))

        while i <= n - 1:
            h_hash += ord(key[i]) * (31 ** (n - 1 - i))
            i += 1
        return h_hash % self.table_size

    def in_table(self, key):
        """ Returns True if key is in an entry of the hash table, False otherwise."""
        i = self.get_index(key)
        if i is None:
            return False
        return True

    def get_index(self, key):
        """ Returns the index of the hash table entry containing the provided key. 
        If there is not an entry with the provided key, returns None."""
        i = self.horner_hash(key)                               # i is the hash key
        j = 0                                                   # initialize j
        res = 0                                                 # initialize res
        while self.hash_table[i + (j ** 2) - res] is not None:  # while the index in the hash table is not empty
            if self.hash_table[i + (j ** 2) - res][0] == key:   # if the key in hash_table equals the key inserting
                return i + (j ** 2) - res                       # use quadratic probing to find an empty spot
            j += 1                                              # increase the value of j
            if i + (j ** 2) - res >= self.table_size:           # if result of quadratic proving is greater than table
                res += self.table_size                          # increase table size
        return None

    def get_all_keys(self):
        """ Returns a Python list of all keys in the hash table."""
        key_list = []

        for i in self.hash_table:
            if i is not None:
                key_list.append(i[0])
        return key_list

    def get_value(self, key):
        """ Returns the value (list of line numbers) associated with the key. 
        If key is not in hash table, returns None."""
        val = self.get_index(key)
        if val is None:
            return None
        return self.hash_table[val][1]

    def get_num_items(self):
        """ Returns the number of entries (words) in the table."""
        return self.num_items

    def get_table_size(self):
        """ Returns the size of the hash table."""
        return self.table_size

        #return self.hash_table      # gives you the hash table <---[None, None, None, None, None]

    def get_load_factor(self):
        """ Returns the load factor of the hash table (entries / table_size)."""

        if self.num_items != 0:

            load_f = float(float(self.num_items)/float(len(self.hash_table)))
            return round(load_f, 7)
        else:
            return 0

if __name__ == '__main__':
    h = HashTable(7)

    h.insert("cat", 5)
    h.insert("dog", 8)
    h.insert("mouse", 10)
    h.insert("elephant", 12)
    print(h.get_num_items())


    print(h.get_table_size())

    print(h.hash_table)
    #print(test)
    print(h.get_load_factor())
    print(h.get_value('rat'))
    print(h.get_all_keys())
