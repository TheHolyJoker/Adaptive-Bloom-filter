//
// Created by tomer on 9/16/18.
//

#include "Hash.h"



size_t Hash::calc(const char *elementP, size_t size) const {
    uint32_t a, b;
    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), DEFUALT_SEED, &a);
    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), SECOND_SEED, &b);
    return (a % size + this->multiConst * (b % size)) % size;
}

size_t Hash::calc(string *elementP, size_t size) const {
    char const *cp = elementP->c_str();
    return calc(cp,size);
}


Hash::Hash(size_t size) {
    this->multiConst = udr(1, size - 1);
}

size_t Hash::getMultiConst() const {
    return multiConst;
}


//
//unsigned int Hash::calc(char const *elementP, size_t size) const{
//    uint32_t a, b;
//    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), DEFUALT_SEED, &a);
//    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), SECOND_SEED, &b);
//    unsigned int index = (a % size + this->multiConst * (b % size)) % size;
//    return index;
//}
//
//
//unsigned int Hash::calc(string *elementP, size_t size) const {
//    char const *cp = elementP->c_str();
//    return Hash::calc(cp,size);
//}

//unsigned int Hash::calc(string *elementP, size_t size) {
//    char const *cp = elementP->c_str();
//    return Hash::calc(cp,size);
//}

//ostream& operator<<(ostream &os, Hash &h)
//{
//    os << h.getMultiConst();
//}
//

//unsigned int Hash::multipliHash(uint32_t index) {
//    return (this->a * index + )
//}


