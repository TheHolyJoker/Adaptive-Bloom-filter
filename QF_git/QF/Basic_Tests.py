from QF.BitArray import *
from random import *


def init(n, bits):
    a = BitArray(n, bits)
    return a


def add_random(n, bits, m):
    l = []
    a = init(n, bits)
    for i in range(m):
        temp_data = [randint(0, 1) for i in range(bits)]
        hash_index = randint(0, a.capacity - 1)
        l.append((temp_data, hash_index))
        a.add(temp_data, hash_index)
    print_data_index_list(l)
    print(a)
    return l, a


def lookup_random(n, bits, m):
    l, a = add_random(n, bits, m)
    for data, index in l:
        if not a.lookup(data, index):
            print("False negative with", (data, index))
    print(str(a))
    print_data_index_list(l)


def test_add(a: BitArray, elements_list, to_print: bool = False):
    if to_print:
        print_data_index_list(elements_list)

    for bin_list, hash_index in elements_list:
        a.add(bin_list, hash_index)
        if to_print:
            print(a)


def tp_lookup(a: BitArray, elements_list, to_print=True) -> bool:
    """

    :param a:
    :param elements_list:
    :param to_print:
    :return: False if Pass!
    """
    fp_list = []
    for data, index in elements_list:
        if not (a.lookup(data, index)):
            fp_list.append((data, index))
    if len(fp_list) == 0:
        if to_print:
            print("No FP!", end=":")
        return False
    else:
        print(len(fp_list), "False negative: ", end="")
        print_data_index_list(fp_list)
        return True


def sanity_lookup() -> bool:
    """
    Initializing Empty BitArray, and checking if it contain any element.
    """
    fp_list = []
    n, bits = randint(10, 100), randint(4, 8)
    a = BitArray(n, bits)
    for i in range(32):
        data, index = random_data(bits), randint(0, n - 1)
        if a.lookup(data, index):
            fp_list.append((data, index))
    if len(fp_list) == 0:
        print("No fn!", end=":")
        return False
    else:
        print(len(fp_list), "False positive: ", end="")
        print_data_index_list(fp_list)
        return True


def t1(to_print: bool = False):
    """
    adding elements without any soft collision
    :return:
    """
    n, bits = 5, 5
    l_to_print = [('00000', 0), ('00001', 1), ('00010', 2), ('00011', 3), ('00100', 4)]
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    a = BitArray(n, bits)
    test_add(a, elements_list)
    # tp_lookup(a, elements_list)
    res = ['0:00000|100', '1:00001|100', '2:00010|100', '3:00011|100', '4:00100|100']
    if str(res) == str(a):
        print("Pass t1")
        if not to_print:
            return
    print("Elements_list:", l_to_print)
    print(a)
    print(res)


def t2(to_print: bool = False):
    """
    lookup without any soft collision
    :return:
    """
    n, bits = 5, 5
    l_to_print = [('00000', 0), ('00001', 1), ('00010', 2), ('00011', 3), ('00100', 4)]
    res = ['0:00000|100', '1:00001|100', '2:00010|100', '3:00011|100', '4:00100|100']
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    a = BitArray(n, bits)
    test_add(a, elements_list)
    check(a, res, l_to_print, elements_list, "t2")
    # tp_lookup(a, elements_list)
    #
    # if str(res) == str(a):
    #     print("Pass t2")
    #     if not to_print:
    #         return
    # print("Elements_list:", l_to_print)
    # print(a)
    # print(res)


def t3():
    """
    lookup with soft collisions, right order
    :return:
    """

    n, bits = 5, 5
    l_to_print = [('10101', 0), ('01100', 1), ('10000', 1), ('11010', 1)]
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    res = ['0:10101|100', '1:01100|100', '2:10000|011', '3:11010|011', '4:00000|000']
    a = BitArray(n, bits)
    test_add(a, elements_list)
    check(a, res, l_to_print, elements_list, "t3")
    # tp_lookup(a, elements_list)
    # if str(res) == str(a):
    #     print("Pass t3")
    #     return
    # print("Elements_list:", l_to_print)
    # print("BitArray a:", a)


def t4():
    """
    lookup with soft collisions, reverse order
    :return:
    """

    n, bits = 5, 5
    l_to_print = [('10101', 0), ('11010', 1), ('10000', 1), ('01100', 1)]
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    a = BitArray(n, bits)
    test_add(a, elements_list)
    tp_lookup(a, elements_list)
    res = ['0:10101|100', '1:01100|100', '2:10000|011', '3:11010|011', '4:00000|000']
    check(a, res, l_to_print, elements_list, "t4")
    # if str(res) == str(a):
    #     print("Pass t4")
    # else:
    #     print("Elements_list:", l_to_print)
    #     print(a)
    #     print(res)
    #     assert False


def t5(to_print=False):
    """
    lookup with soft collisions, checking boundaries
    :return:
    """

    n, bits = 4, 5
    l_to_print = [('11111', 1), ('01100', 1), ('10000', 1), ('11010', 1)]
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    a = BitArray(n, bits)
    test_add(a, elements_list, to_print)
    res = ['0:11111|011', '1:01100|100', '2:10000|011', '3:11010|011']
    check(a, res, l_to_print, elements_list, "t5")
    # if str(res) == str(a):
    #     print("Pass t5", end="\t")
    # else:
    #     print()
    #     print()
    #     print_data_index_list(elements_list)
    #     print(a)
    #     print(res)
    #     print("Error in add")
    #     return
    # if tp_lookup(a, elements_list):
    #     print_data_index_list(elements_list)
    #     print(a)
    #     print(res)
    #     print("Error in lookup")
    # else:
    #     print("Pass t5")


def t7_1(to_print_add=False):
    n, bits = 7, 5
    l_to_print = [('00011', 1), ('00100', 2), ('11111', 6), ('11111', 0), ('11000', 0), ('01111', 0)]
    res = ['0:01111|100', '1:11000|111', '2:11111|111', '3:00011|001', '4:00100|001', '5:00000|000', '6:11111|100']
    a = BitArray(n, bits)
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    test_add(a, elements_list, to_print_add)
    if str(a) == str(res):
        print("Pass t7_1")
        return
    print(a)
    print(res)


def t7_2(to_print_add=False):
    n, bits = 7, 5
    l_to_print = [('00011', 1), ('00100', 2), ('11111', 6), ('11111', 0), ('11000', 0), ('01111', 0), ('00111', 2)]
    res = ['0:01111|100', '1:11000|111', '2:11111|111', '3:00011|001', '4:00100|001', '5:00111|011', '6:11111|100']
    a = BitArray(n, bits)
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    test_add(a, elements_list, to_print_add)
    if str(a) == str(res):
        print("Pass t7_2")
        return
    print(a)
    print(res)


def t7_3(to_print_add=False):
    n, bits = 7, 5
    l_to_print = [('00011', 1), ('00100', 2), ('11111', 6), ('11111', 0), ('11000', 0), ('01111', 0)]
    res = ['0:01111|100', '1:11000|111', '2:11111|111', '3:00011|001', '4:00100|001', '5:00000|000', '6:11111|100']
    a = BitArray(n, bits)
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    test_add(a, elements_list, to_print_add)
    check(a, res, l_to_print, elements_list, "t7_3")


def t7(to_print_add=False):
    n, bits = 13, 5
    l_to_print = [('00011', 1), ('00111', 1), ('11111', 4), ('11111', 6), ('11000', 6), ('01111', 6), ('00011', 7),
                  ('00100', 8), ('11111', 12)]
    res = ['0:00000|000', '1:00011|100', '2:00111|011', '3:00000|000', '4:11111|100', '5:00000|000', '6:01111|100',
           '7:11000|111', '8:11111|111', '9:00011|001', '10:00100|001', '11:00000|000', '12:11111|100']
    a = BitArray(n, bits)
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    test_add(a, elements_list, to_print_add)
    check(a, res, l_to_print, elements_list, "t7")


def t8(add_print=False):
    """
    Inserting element (the last) between existing runs, which create a new run
    expected problem : first element continuation bit will be set to True
    :param add_print:
    :return:
    """

    a = BitArray(8, 5)
    l_to_print = [('11010', 0), ('01000', 6), ('11001', 6), ('10101', 6), ('11001', 7)]
    res = ['0:11001|111', '1:11001|001', '2:11010|001', '3:00000|000', '4:00000|000', '5:00000|000', '6:01000|100',
           '7:10101|111']
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    test_add(a, elements_list, add_print)
    check(a, res, l_to_print, elements_list, "t8")


def t_random_lookup(to_print=False, n=8, bits=5, m=5):
    """
    lookup random lookup
    :return:
    """

    a = BitArray(n, bits)
    elements_list = [(random_data(bits), randint(0, a.capacity - 1)) for i in range(m)]
    test_add(a, elements_list, to_print)
    if not tp_lookup(a, elements_list, to_print):
        # print("Pass t_random_lookup")
        return
    print("Failed t_random_lookup:")
    print_data_index_list(elements_list)
    print(a)


def ts_1(add_print=False):
    # 1 False negative: [('00100', 0)]
    l_to_print = [('00100', 0), ('01100', 3), ('10001', 5), ('10111', 7), ('01110', 7)]
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    res = ['0:10111|111', '1:00100|001', '2:00000|000', '3:01100|100', '4:00000|000', '5:10001|100',
           '6:00000|000', '7:01110|100']
    a = BitArray(8, 5)
    test_add(a, elements_list, add_print)
    check(a, res, l_to_print, elements_list, "ts_1")


def ts_2(add_print=False):
    a = BitArray(8, 5)
    l_to_print = [('10010', 1), ('00101', 2), ('01000', 6), ('01000', 6), ('11011', 7)]
    res = ['0:11011|001', '1:10010|100', '2:00101|100', '3:00000|000', '4:00000|000', '5:00000|000', '6:01000|100',
           '7:01000|111']
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    test_add(a, elements_list, add_print)
    check(a, res, l_to_print, elements_list, "ts_2")


def ts_3(add_print=False):
    a = BitArray(6, 5)
    l_to_print = [('01000', 1), ('11001', 2), ('01010', 5), ('10111', 5), ('11110', 6)]

    res = ['0:00000|000', '1:10100|100', '2:11011|111', '3:00110|101', '4:11100|001', '5:00000|000']
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    test_add(a, elements_list, add_print)
    check(a, res, l_to_print, elements_list, "ts_3")


def ts_4(add_print=False):
    a = BitArray(8, 5)
    l_to_print = [('00111', 1), ('10100', 3), ('11011', 3), ('00110', 4), ('11100', 5)]
    res = ['0:00000|000', '1:00111|100', '2:00000|000', '3:10100|100', '4:11011|111', '5:00110|101', '6:11100|001',
           '7:00000|000']

    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    test_add(a, elements_list, add_print)
    check(a, res, l_to_print, elements_list, "ts_4")


def ts_d(l_to_print, add_print=False, res=None):
    a = BitArray(8, 5)

    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    test_add(a, elements_list, add_print)
    if res:
        check(a, res, l_to_print, elements_list, "ts_d")
        return
    if not tp_lookup(a, elements_list):
        print("Pass ts_d without res")
        return
    print_data_index_list(elements_list)
    print(a)


def test00(to_print_add=False):
    n, bits = 32, 5
    l_to_print = [('11000', 9), ('01110', 9), ('10010', 14), ('00000', 19), ('10100', 19), ('11100', 19), ('01100', 20),
                  ('01111', 21), ('11100', 26)]
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    a = BitArray(n, bits)
    print(a)
    print_data_index_list(elements_list)
    test_add(a, elements_list, to_print_add)
    print(a)
    print()
    print()
    tp_lookup(a, elements_list)


def test0(to_print_add=False):
    n, bits = 32, 5
    l_to_print = [('11000', 9), ('01110', 9), ('10010', 14), ('00000', 19), ('10100', 19), ('11100', 19), ('01100', 20),
                  ('01111', 21), ('11100', 26)]
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    a = BitArray(n, bits)
    print(a)
    print_data_index_list(elements_list)
    test_add(a, elements_list, to_print_add)
    print(a)
    print()
    print()
    tp_lookup(a, elements_list)


def test1():
    n, bits, m = 32, 5, 16
    l_to_print = [('10101', 0), ('01100', 1), ('10000', 5), ('11010', 5), ('00000', 7), ('11000', 9), ('01001', 10),
                  ('00100', 12), ('10110', 18), ('11011', 18), ('01010', 21), ('01110', 22), ('01000', 23),
                  ('10111', 23),
                  ('10100', 24), ('00110', 31)]
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    a = BitArray(n, bits)
    test_add(a, elements_list)
    tp_lookup(a, elements_list)
    print("Elements:", l_to_print)
    print(a)


def test2():
    n, bits, m = 4, 5, 2
    l_to_print = [('11111', 1), ('00001', 1)]
    elements_list = [([1] * 5, 1), ([0] * 4 + [1], 1)]
    a = BitArray(n, bits)
    test_add(a, elements_list)
    tp_lookup(a, elements_list)
    print("Elements_list:", l_to_print)
    print("BitArray a:", a)


def test4():
    n, bits = 8, 5
    l_to_print = [('01110', 1), ('01000', 2), ('10111', 2), ('10100', 3)]
    elements_list = [(bin_to_list(i[0]), i[1]) for i in l_to_print]
    a = BitArray(n, bits)
    test_add(a, elements_list, True)
    tp_lookup(a, elements_list)
    print("Elements_list:", l_to_print)
    print(a)

    print(
        ['0:00000|000', '1:01110|100', '2:01000|100', '3:10111|111', '4:10100|001', '5:00000|000', '6:00000|000',
         '7:00000|000'])


def print_data_index_list(bin_list):
    k = [(list_to_bin(i[0]), i[1]) for i in bin_list]
    print(k)
    k_sort = sorted(k, key=lambda x: x[1])
    if k_sort != k:
        print(k_sort)


def list_to_bin(l, bits=5):
    data: int = 1
    for bit in l:
        data = 2 * data + bit
    temp = bin(data)[-len(l):]
    return temp


def bin_to_list(b):
    temp = list(b)
    temp = [int(i) for i in temp]
    if len(temp) != len(b):
        print("ERROR in bin_to_list")
    return temp


def random_data(length):
    return [randint(0, 1) for i in range(length)]


def check(a: BitArray, res, l_to_print, elements_list: list, name: str) -> bool:
    if str(a) != str(res):
        print_data_index_list(elements_list)
        print(a)
        print(res)
        print("Error!")
        return True
    if not tp_lookup(a, elements_list):
        print("Pass", name)
        return False
    print_data_index_list(elements_list)
    print(a)
    return True
