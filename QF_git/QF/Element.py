from typing import List

META_BITS = 3


class Element:
    bits_per_element = None
    value = None

    def __init__(self, bits):
        self.bits_per_element = bits
        self.value = [False] * (self.bits_per_element + META_BITS)

    def get_val(self):
        return self.value

    def set_val(self, data, mb):
        if self.get_occupied() and not mb[0]:
            assert False
        self.set_data(data)
        self.set_mb(mb)

    def get_data(self):
        return self.value[:self.bits_per_element]

    def set_data(self, data):
        self.value[:self.bits_per_element] = data

    def get_mb(self):
        return self.value[self.bits_per_element:]

    def set_mb(self, mb):
        if self.get_occupied() and not mb[0]:
            assert False
        self.value[self.bits_per_element:] = mb

    def get_occupied(self):
        return self.value[-META_BITS]

    def get_continuation(self):
        return self.value[-META_BITS + 1]

    def get_shifted(self):
        return self.value[-META_BITS + 2]

    def set_occupied(self, val=True):
        assert val
        self.value[-META_BITS] = val

    def set_continuation(self, val=True):
        self.value[-META_BITS + 1] = val

    def set_shifted(self, val=True):
        self.value[-META_BITS + 2] = val

    def is_run_start(self):
        a, b, c = self.get_mb()
        return (not b) and (a or c)

    def is_cluster_start(self):
        a, b, c = self.get_mb()
        return a and (not b) and (not c)

    def is_empty(self):
        a, b, c = self.get_mb()
        return not (a or b or c)

    def set_empty(self):
        if self.get_occupied():
            assert False
        print("Set Empty call")
        self.set_mb([False, False, False])

    def __str__(self):
        bits = self.bits_per_element
        data = 1
        for bit in self.value[:bits]:
            data = 2 * data + bit
        mb = 1
        for bit in self.value[bits:]:
            mb = 2 * mb + bit
        return bin(data)[-bits:] + "|" + bin(mb)[-META_BITS:]

    def less_than(self, data) -> bool:
        a = self.get_data()
        for bit in range(self.bits_per_element):
            if a[bit] != data[bit]:
                return a[bit] < data[bit]
        return False
