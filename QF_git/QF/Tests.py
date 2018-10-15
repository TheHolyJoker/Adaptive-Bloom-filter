from QF.Basic_Tests import *
from QF.CQF import *
import numpy as np
from string import *


def tp_lookup(n=16, bits=5, m=5):
    """
    lookup random lookup
    :return:
    """

    qf = CQF(n, 1 / (2 ** bits))
    elements_set = {r_str(bits) for i in range(m)}
    for el in elements_set:
        qf.add(el)
    for el in elements_set:
        if not qf.lookup(el):
            print("Failed")


def tn_lookup(n=16, bits=5, m=5):
    """
    lookup random lookup
    :return:
    """

    qf = CQF(n, 1 / (2 ** bits))
    for i in range(m):
        el = r_str(bits)
        if qf.lookup(el):
            print("Failed")


def fp_rate(capacity, bits, lookups, load_factor=1 / 2):
    # bits = ceil(-log2(1 / eps))
    qf = CQF(capacity, 1 / (2 ** bits))
    m = round(capacity * load_factor)
    my_set = {r_str(bits) for i in range(m)}
    if len(my_set) != m:
        print("my_set to m ratio", len(my_set) / m)
    for el in my_set:
        qf.add(el)

    actual_lf = qf.get_load_factor()
    print("actual_lf:", actual_lf, "Expected:", 1 / 2)
    nom_set = {r_str(bits) for i in range(lookups)}
    if len(nom_set) != lookups:
        print("nom_set to m ratio", len(nom_set) / lookups)
    counter = [0, 0, 0]  # [TN, FP, TP]
    for el in nom_set:
        ans: bool = qf.lookup(el)
        if not ans:
            counter[0] += 1
        else:
            if not el in my_set:
                counter[1] += 1
            else:
                counter[2] += 1
    print(counter, counter[1] / sum(counter), 1 / (2 ** bits))


def r_str(length, diff_char=32):
    chars = ascii_letters[:diff_char]
    return ''.join(choice(chars) for x in range(length))


def np_data(length):
    return np.random.randint(2, size=length)


def c1():
    bits = 5
    qf = CQF(16, 1 / (2 ** 5))
    qf.add(r_str(bits))
