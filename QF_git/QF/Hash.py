from random import *
import mmh3

DEFAULT_SEED = 42


class Hash:
    multi_const = None
    size = None

    def __init__(self, array_size: int):
        self.size = array_size
        self.multi_const = randint(0, array_size - 1)
        if not self.multi_const:
            print("multi index is 0")

    def calc(self, s: str):
        return (mmh3.hash(s) + self.multi_const * mmh3.hash(s, DEFAULT_SEED)) % self.size

    def __call__(self, s):
        return (mmh3.hash(s) + self.multi_const * mmh3.hash(s, DEFAULT_SEED)) % self.size
