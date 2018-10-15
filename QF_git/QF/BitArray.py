from QF.Element import *
from math import *


class BitArray:
    capacity = 0
    bit_per_element = 0
    array = []

    def __init__(self, n, bits):
        self.capacity = n
        self.bit_per_element = bits
        self.array = [Element(bits) for i in range(self.capacity)]

    def __getitem__(self, item):
        return self.array[item]

    def __setitem__(self, key, value):
        self[key].set_data(value[0])
        self[key].set_mb(value[1])

    def get_next_empty(self, index):
        runs_to_move = 0
        while not self[index].is_empty():
            runs_to_move += self[index].is_run_start()
            index = (index + 1) % self.capacity
        return index, runs_to_move

    def get_run_start_counter(self, index):
        occupied_counter = 0
        while self.array[index].get_continuation():
            occupied_counter += self.array[index].get_occupied()
            index = (index - 1) % self.capacity
        return index, occupied_counter

    def get_run_start_naive(self, index):
        while self.array[index].get_continuation():
            index = (index - 1) % self.capacity
        return index

    def get_next_run_start(self, index):
        if not self.array[index].get_continuation():
            index = (index + 1) % self.capacity
        while self.array[index].get_continuation():
            index = (index + 1) % self.capacity
        return index

    def get_cluster_start(self, index):
        if self[index].is_cluster_start() or self[index].is_empty():
            return index, 0
        occupied_counter = 0
        while self[index].get_shifted():  # change when adaptive
            index = (index - 1) % self.capacity
            occupied_counter += self.array[index].get_occupied()
        return index, occupied_counter

    def get_comp_run(self, index):
        cluster_start, occupied_counter = self.get_cluster_start(index)
        temp_run_start = cluster_start
        for i in range(occupied_counter):
            temp_run_start = self.get_next_run_start(temp_run_start)
        return temp_run_start

    def run_shift(self, empty_index, index):
        self[empty_index].set_continuation()
        self[empty_index].set_shifted()
        while empty_index != index:
            self[empty_index].set_data(self[empty_index - 1].get_data())
            empty_index = (empty_index - 1) % self.capacity

        if self[index].is_run_start():
            index = (index + 1) % self.capacity
            self[index].set_shifted()
            self[index].set_continuation(False)

        return empty_index

    def push(self, index, to_push_again=False):
        if self[index].is_empty():
            return
        empty_index, complete_runs_to_move = self.get_next_empty(index)
        temp_run_start = self.get_run_start_naive((empty_index - 1) % self.capacity)

        for i in range(complete_runs_to_move):
            empty_index = self.run_shift(empty_index, temp_run_start)
            temp_run_start = self.get_run_start_naive((empty_index - 1) % self.capacity)
        if to_push_again:
            self.run_shift(empty_index, index)

    def add(self, data: List[int], hash_index: int) -> None:
        is_part_of_existing_run = self[hash_index].get_occupied()

        run_index = self.get_comp_run(hash_index)
        if self[run_index].is_empty():
            is_shifted = (run_index != hash_index)
            if is_shifted:
                self[run_index] = [data, [False, False, True]]
            else:
                self[run_index] = [data, [True, False, False]]
            self[hash_index].set_occupied()
            return
        self[hash_index].set_occupied()

        if not is_part_of_existing_run:  # new run
            self.push(run_index)
            self[run_index].set_data(data)
            self[run_index].set_shifted()
            return

        if self[run_index].less_than(data):  # not first
            run_index = (run_index + 1) % self.capacity
            while self[run_index].get_continuation() and self[run_index].less_than(data):
                run_index = (run_index + 1) % self.capacity

            if self[run_index].is_empty():
                self[run_index] = [data, [False, True, True]]
                return

            self.push(run_index, True)
            self[run_index].set_data(data)

        else:  # element will be inserted first to an existing run
            self.push(run_index)
            self[run_index].set_data(data)
            run_index = (run_index + 1) % self.capacity
            self[run_index].set_continuation()

    def lookup(self, data: list, hash_index: int) -> bool:
        if not self[hash_index].get_occupied():
            # print("In lookup: Occ False")
            return False

        run_index = self.get_comp_run(hash_index)
        if self[run_index].get_data() == data:
            return True
        run_index = (run_index + 1) % self.capacity
        while self[run_index].get_continuation():
            if self[run_index].get_data() == data:
                return True
            if not self[run_index].less_than(data):
                return False
            run_index = (run_index + 1) % self.capacity
        return False

    def __str__(self):
        l = [str(i) + ":" + str(self[i]) for i in range(self.capacity)]
        return str(l)

#    def delete(self, data: List[int], hash_index: int) -> bool:
#        del_index = self.find_index(data, hash_index)
#        if del_index == -1:
#            return False
# 
#    def find_index(self, data: List[int], hash_index: int) -> int:
#        if not self[hash_index].get_occupied():
#            print("Finding element that is not in the BitArray")
#            return -1
# 
#        run_index = self.get_comp_run(hash_index)
#        if self[run_index].get_data() == data:
#            return run_index
#        run_index = (run_index + 1) % self.capacity
#        while self[run_index].get_continuation():
#            if self[run_index].get_data() == data:
#                return run_index
#            if not self[run_index].less_than(data):
#                return -1
#            run_index = (run_index + 1) % self.capacity
#        return -1
# 
#    def push_back(self, index: int):
#        if self[index].is_empty():
#            return
#        cluster_last_index, complete_runs_to_move = self.get_cluster_end(index)
#        temp_run_start = self.get_run_start_naive((cluster_last_index - 1) % self.capacity)
# 
#        if self[index].is_cluster_start():
#            return 
#        for i in range(complete_runs_to_move):
#            cluster_last_index = self.run_shift(cluster_last_index, temp_run_start)
#            temp_run_start = self.get_run_start_naive((cluster_last_index - 1) % self.capacity)
#        # if to_push_again:
#        #     self.run_shift(cluster_last_index, index)
# 
#    def run_shift_back(self, empty_index, index):
#        return
# 
#    def get_cluster_end(self, index):
#        if self[index].is_empty():
#            return index, 0
# 
#        occupied_counter = 0
#        if self[index].is_cluster_start():
#            occupied_counter = 1
#            index = (index + 1) % self.capacity
# 
#        while self[index].get_shifted():  # change when adaptive
#            occupied_counter += self.array[index].get_occupied()
#            index = (index + 1) % self.capacity
# 
#        index = (index - 1) % self.capacity
#        return index, occupied_counter
