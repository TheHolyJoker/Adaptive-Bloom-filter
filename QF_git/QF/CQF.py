from typing import List

from QF.BitArray import *

from QF.Hash import *


class CQF:
    A: BitArray
    capacity: int
    bits: int
    h: Hash

    def __init__(self, n, eps):
        q, r = ceil(log2(n)), ceil(log2(1 / eps))
        if q + r > 32:
            assert False
        self.capacity = n
        self.bits = ceil(log2(1 / eps))
        self.A = BitArray(n, self.bits)
        self.h = Hash(2 ** (q + r))

    def str_to_data_index(self, s: str):
        ans = self.h(s)
        data = ans % (2 ** self.bits)
        index = ans // (2 ** self.bits)
        # assert index.is_integer()
        index = int(index)

        temp_s = list(bin(data)[2:])
        if len(temp_s) < self.bits:
            temp_s = [0] * (self.bits - len(temp_s)) + temp_s
        data_l = [int(i) for i in temp_s]
        return data_l, index

    def add(self, s: str):
        data, hash_index = self.str_to_data_index(s)
        self.A.add(data, hash_index)

    def lookup(self, s: str) -> bool:
        data, hash_index = self.str_to_data_index(s)
        return self.A.lookup(data, hash_index)

    def get_load_factor(self):
        load_factor = 0
        for i in range(self.capacity):
            load_factor += self.A[i].get_occupied()
        return load_factor / self.capacity
