//
// Created by tomer on 4/14/19.
//

#include "GeneralBF.h"

/*GeneralBF::GeneralBF(size_t n, size_t m, bool is_adaptive) :is_adaptive(is_adaptive), size(m){
    //todo clean this.
    size_t k = get_hashFunction_num(n, m);
    if (is_adaptive)
        m <<= 1;// NOLINT(hicpp-signed-bitwise)
    assert(m >= 4 && k >= 1);
    this->size = m;
    this->bit_array.resize(m, false);
    this->hashVec.resize(k);
    for (int i = 0; i < k; ++i)
        this->hashVec[i] = Hash(size, is_adaptive);

    one_file_per_object_backing_store bs(path);
    swap_space sspace(&bs, CACHE_SIZE);
    this->Remote = new betree<uint64_t, std::string>(&sspace, MAX_NODE_SIZE, MIN_FLUSH_SIZE);
}*/



GeneralBF::GeneralBF(size_t size, size_t k_hashFunc, bool is_adaptive) : is_adaptive(is_adaptive), size(size) {

    //todo clean this.
    if (is_adaptive)
        (this->size) <<= 1; // NOLINT(hicpp-signed-bitwise)
    assert(this->size >= 4 && k_hashFunc >= 1);

    this->bit_array.resize(this->size, false);
    this->hashVec.resize(k_hashFunc);

    for (int i = 0; i < k_hashFunc; ++i)
        this->hashVec[i] = Hash(this->size, is_adaptive);
}

GeneralBF::GeneralBF(size_t n, double eps, bool is_adaptive) : is_adaptive(is_adaptive) {
    this->size = get_bitArray_size_ceil(n, eps);
    size_t k = get_hashFunction_num(n, size);
    if (is_adaptive)
        (this->size) <<= 1; // NOLINT(hicpp-signed-bitwise)
    assert(size >= 4 && k >= 1);
    this->bit_array.resize(this->size, false);
    this->hashVec.resize(k);

    for (int i = 0; i < k; ++i)
        this->hashVec[i] = Hash(size, is_adaptive);

}


bool GeneralBF::add(string *s) {
    if (!this->is_adaptive) {
        this->non_adaptive_add(s);
        return true;
    }

    bool did_not_hit_FP = true;
    for (auto h : this->hashVec) {
        size_t temp_index = h(s) << 1;// NOLINT(hicpp-signed-bitwise)
//        assert(temp_index + 1 < this->size);
        this->bit_array[temp_index] = true;
        if (this->bit_array[temp_index bitor 1]) {  // NOLINT(hicpp-signed-bitwise)
            did_not_hit_FP = false;
            //Todo break here! Rob's and Alex's comment.
        }
    }
    return did_not_hit_FP;
}

bool GeneralBF::add(string *s, bool *cell_cond) {
    if (!this->is_adaptive) {
        this->non_adaptive_add(s, cell_cond);
        return true;
    }

    bool did_not_hit_FP = true;
    for (int i = 0; i < this->get_hash_vec_size(); ++i) {
        size_t temp_index = (this->hashVec[i](s)) << 1;// NOLINT(hicpp-signed-bitwise)
        cell_cond[i] = this->bit_array[temp_index];
        this->bit_array[temp_index] = true;
        if (this->bit_array[temp_index bitor 1])  // NOLINT(hicpp-signed-bitwise)
            did_not_hit_FP = false;

    }
    return did_not_hit_FP;
}

void GeneralBF::non_adaptive_add(string *s) {
    for (auto h : this->hashVec) {
        size_t temp_index = h(s);
        this->bit_array[temp_index] = true;
    }
}

void GeneralBF::non_adaptive_add(string *s, bool *cell_cond) {
    for (int i = 0; i < this->get_hash_vec_size(); ++i) {
        size_t temp_index = this->hashVec[i](s);
        cell_cond[i] = this->bit_array[temp_index];
        this->bit_array[temp_index] = true;
    }
}

filter_lookup_res GeneralBF::lookup(string *s) {
    if (!this->is_adaptive)
        return this->non_adaptive_lookup(s);

//    bool did_hit_FP = false;
    for (auto h : this->hashVec) {
        size_t temp_index = h(s) << 1; // NOLINT(hicpp-signed-bitwise)

        if (!bit_array[temp_index])
            return definitely_not_in_filter;

        //If filter bit is on, check stale bit.
        if (bit_array[temp_index bitor 1])  // Hit a FP?  //NOLINT(hicpp-signed-bitwise)
            return IDK_check_next_level;

        /*if (bit_array[temp_index]) {
            if (bit_array[temp_index bitor 1])  // Hit a FP?  //NOLINT(hicpp-signed-bitwise)
                did_hit_FP = true;
        } else
            return definitely_not_in_filter;*/
    }
    return maybe_in_filter;
//    if (did_hit_FP)
//        return IDK_check_next_level;
}

filter_lookup_res GeneralBF::non_adaptive_lookup(string *s) {
    for (auto h : this->hashVec) {
        if (!this->bit_array[h(s)])
            return definitely_not_in_filter;
    }
    return maybe_in_filter;
}

const vector<bool> &GeneralBF::getBitArray() const {
    return bit_array;
}

const vector<Hash> &GeneralBF::get_hash_vec() const {
    return hashVec;
}

size_t GeneralBF::getSize() const {
    return size;
}

size_t GeneralBF::get_filter_on_bits() const {
    size_t sum = 0;
    if (this->is_adaptive) {
        size_t lim = (this->size) >> 1;  // NOLINT(hicpp-signed-bitwise)
        for (int i = 0; i < lim; i++) {
            if (this->bit_array[(i << 1)]) // NOLINT(hicpp-signed-bitwise)
                sum++;
        }
        return sum;
    }
    for (int i = 0; i < this->size; ++i) {
        if (this->bit_array[i])
            sum++;
    }
    return sum;
}

size_t GeneralBF::get_stale_on_bits() const {
    assert(this->is_adaptive);
    size_t sum = 0;
    size_t counter = 1;
    while (counter < this->size) {
        if (this->bit_array[counter])
            sum++;
        counter += 2;
    }
    return sum;
}
/*

bool* GeneralBF::operator[](size_t index) {
    return &(this->bit_array[index]);

}

bool* GeneralBF::operator[](size_t index) const {
    return &this->bit_array[index];
}
*/

ostream &operator<<(ostream &os, const GeneralBF &generalBf) {
    bool is_adaptive = generalBf.is_adaptive;
    const size_t size = generalBf.getSize();
    const size_t k = generalBf.get_hash_vec().size();
    size_t filter_on_bits = generalBf.get_filter_on_bits();
    size_t stale_on_bits;
    if (is_adaptive) {
        stale_on_bits = generalBf.get_stale_on_bits();
    }
    os << "bit_array size is: " << size;
    os << "\tk is: " << k << endl;

    if (PRINT_HASH)
        print_hashFunctions(os, generalBf);

    os << "Number of on bits in filter: " << filter_on_bits << "\tRatio is: "
       << ((double) filter_on_bits) / size << endl;

    if (is_adaptive)
        os << "Number of on bits in stale: " << stale_on_bits << "\tRatio is: "
           << ((double) stale_on_bits) / size << endl;

    os << endl;
    return os;
}

void GeneralBF::set_stale_on(size_t index) {
    assert(is_adaptive);
    this->bit_array[(index << 1) bitor 1] = true; // NOLINT(hicpp-signed-bitwise)
}

size_t GeneralBF::get_hash_vec_size() const {
    return this->hashVec.size();
}
/*

ostream &operator<<(ostream &os, const GeneralBF &generalBf) {
    const size_t size = generalBf.getSize();
    const size_t k = generalBf.get_hash_vec().size();
    os << "b_filter size: " << size;
    os << "\tk is: " << k;
    print_hashFunctions(os, generalBf);
    os << "Number of on bits in filter: " << generalBf.get_filter_on_bits() << "\tRatio is: "
       << ((double) generalBf.get_filter_on_bits()) / size << endl;
    if (generalBf->is_adaptive)
        os << "Number of on bits in stale: " << generalBf.get_stale_on_bits() << "\tRatio is: "
           << ((double) generalBf.get_stale_on_bits()) / size << endl;
    */
/*for (auto h : bfr.kHashFuncs) {
        const size_t a = h->getMultiConst();
//        if(a >= bfr.size) os << "$$$\n$$$\n$$$\nnext hash function multiConst is too big:";
        os << a << "|";
    }*//*

    os << endl;
    return os;
}
*/

ostream &print_hashFunctions(ostream &os, const GeneralBF &generalBf) {

    if (generalBf.get_hash_vec().empty()) {
        os << "bfr.get_hash_vec()is empty." << endl;
        return os;
    }

    auto &temp_vec = generalBf.get_hash_vec();
    os << "[" << temp_vec[0].getMultiConst();

    for (int i = 1; i < temp_vec.size(); ++i)
        os << ", " << temp_vec[i];

    os << "]" << endl;

    return os;
}

