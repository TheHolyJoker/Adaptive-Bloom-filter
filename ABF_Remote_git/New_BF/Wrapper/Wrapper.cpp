//
// Created by tomer on 4/14/19.
//

#include "Wrapper.h"

Wrapper::Wrapper(size_t n, double eps, bool isAdaptive) : isAdaptive(isAdaptive), bs(create_new_path()),
                                                          sspace(&this->bs, CACHE_SIZE),
                                                          Remote(&sspace, MAX_NODE_SIZE, MIN_FLUSH_SIZE) {
    if (isAdaptive) {
        this->depth = getDepth(n,eps);

        size_t mList[depth], kList[depth];

        get_bitArrays_size_list(n, eps, mList, depth);
        get_hashFunctions_num_list(n, eps, kList, mList, depth);

        for (int i = 0; i < depth; ++i)
            BF_Vec.emplace_back(mList[i], kList[i], true);
    } else {
        this->depth = 1;
        BF_Vec.emplace_back(n, eps, false);
    }
}


//// Basic functions.
void Wrapper::add(string *s, size_t starting_level) {
    if (!this->isAdaptive) {
        this->BF_Vec[0].add(s);
        this->remote_add(s, 0);
        return;
    }

    for (int i = starting_level; i < depth; ++i) {
        this->remote_add(s, i);
        if (this->BF_Vec[i].add(s))
            return;
    }
    //todo Rebuilt here.
    assert(false);
    /*size_t i = 0;
    while (i < depth) {

        ++i;
    }

    assert(i < depth);*/
/*
    *reBuildCall = true;
    this->reBuild();
    this->add(s);
*/

}

void Wrapper::naive_add(string *s, size_t starting_level) {
    if (!this->isAdaptive) {
        this->BF_Vec[0].add(s);
        return;
    }

    for (int i = starting_level; i < depth; ++i) {
        if (this->BF_Vec[i].add(s))
            return;
    }
    //todo Rebuilt here.
    assert(false);
}

void Wrapper::remote_add(string *s, size_t level) {
    for (auto h : this->BF_Vec[level].get_hash_vec()) {
        uint64_t key = get_key(s, level, h);
        this->Remote.update(key, *s + DELIM);
    }

}

bool Wrapper::naive_lookup(string *s) {
    if (!this->isAdaptive)
        return this->BF_Vec[0].lookup(s);

    for (int i = 0; i < depth; ++i) {
        filter_lookup_res temp_res = this->BF_Vec[i].lookup(s);
        if (temp_res == IDK_check_next_level) // Maybe s is in the next level Filter.
            continue;

        return temp_res;
    }
    assert(false);
}

actual_lookup_res Wrapper::lookup_verifier(string *s, bool call_adapt) {
    if (!this->isAdaptive) {
        filter_lookup_res temp_res = this->BF_Vec[0].lookup(s);
        if (temp_res == definitely_not_in_filter)
            return true_negative; // True Negative.

        size_t key = get_key(s, 0, 0);
        return this->remote_lookup(s, key);
    }

    for (int i = 0; i < depth; ++i) {
        filter_lookup_res temp_res = this->BF_Vec[i].lookup(s);
        if (temp_res == definitely_not_in_filter)
            return true_negative;
        if (temp_res == IDK_check_next_level)
            continue;

        size_t key = get_key(s, i, 0);

        actual_lookup_res res = this->remote_lookup(s, key);
        if (call_adapt & (res == 1))
            this->adapt(s, i);
        return res;
    }
    assert(false);

}

actual_lookup_res Wrapper::remote_lookup(string *s, size_t key) {
    try {
        string temp = this->Remote.query(key);
        if (is_sub_str(&temp, s))
            return true_positive;
        return false_positive;
    } catch (out_of_range e) {
        assert(false);
        return false_positive; // False Positive.
        //todo Should not be here!
    }
}

/*string Wrapper::retrive(string *s) {
    if (!this->is_adaptive) {
        if (this->BF_Vec[0].lookup(s))
            auto h = this->BF_Vec[0].get_hash_vec()[0];
//            try {
//                string res = this->Remote.query(h())
//            }

    }
    return std::__cxx11::string();
}*/

//// Adapt.

void Wrapper::adapt(string *s, size_t level) {
    size_t index = adapt_choose_which_index_to_stale(s, level);
    return adapt_by_index_level(level, index);

}

size_t Wrapper::adapt_choose_which_index_to_stale(string *s, size_t level) {
    auto h = this->get_hashFunc(level, 0); // todo
    return h(s);
}

void Wrapper::adapt_by_index_level(size_t level, size_t index) {
    this->BF_Vec[level].set_stale_on(index);
    uint64_t key = (index << 4) + level; // NOLINT(hicpp-signed-bitwise)
    string elements_to_move;
    try {
        elements_to_move = this->Remote.query(key);
        return adapt_insertion(&elements_to_move, level + 1);
    } catch (out_of_range e) {
        assert(false);
    }

}

void Wrapper::adapt_insertion(string *all_elements, size_t level_to_insert_in) {
    assert(level_to_insert_in <= depth);

    istringstream iss(*all_elements);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    for (auto s: tokens)
        this->add(&s, level_to_insert_in);
}

//Wrapper::Wrapper(size_t n, double eps, bool is_adaptive) {
//
//
//}


//size_t Wrapper::count_files(const string *path) {
//    return count_files(*path);
//}
/*

Wrapper::~Wrapper() {
    delete Remote;
}
*/
//// Remote optimization attempt.

actual_lookup_res Wrapper::lookup_verifier(string *s, bool call_adapt, bool remote_trick) {
    if (!this->isAdaptive) {
        filter_lookup_res temp_res = this->BF_Vec[0].lookup(s);
        if (temp_res == definitely_not_in_filter)
            return true_negative; // True Negative.

        size_t key = get_key(s, 0, 0);
        return this->remote_lookup(s, key, true);
    }

    for (int i = 0; i < depth; ++i) {
        filter_lookup_res temp_res = this->BF_Vec[i].lookup(s);
        if (temp_res == definitely_not_in_filter)
            return true_negative;
        if (temp_res == IDK_check_next_level)
            continue;

        size_t key = get_key(s, i, 0);

        actual_lookup_res res = this->remote_lookup(s, key, true);
        if (call_adapt & (res == 1))
            this->adapt(s, i);
        return res;
    }
    assert(false);

}

actual_lookup_res Wrapper::remote_lookup(string *s, size_t key, bool remote_trick) {
    string temp = this->Remote.query(key);
    if (is_sub_str(&temp, s))
        return true_positive;
    return false_positive;
}


void Wrapper::add(string *s, size_t starting_level, bool remote_trick) {
    if (!this->isAdaptive) {
        bool cell_cond[BF_Vec[0].get_hash_vec_size()];
        this->BF_Vec[0].add(s, cell_cond);
        this->remote_add(s, 0, cell_cond);
        return;
    }

    for (int i = starting_level; i < depth; ++i) {
        bool cell_cond[this->get_hash_vec_size_by_level(i)];
        bool res = this->BF_Vec[i].add(s, cell_cond);
        this->remote_add(s, i, cell_cond);
        if (res)
            return;
    }
    //todo Rebuilt here.
    assert(false);
}

void Wrapper::remote_add(string *s, size_t level, const bool *cell_cond) {
    vector<Hash> hashVec = this->BF_Vec[level].get_hash_vec();
    for (int i = 0; i < hashVec.size(); ++i) {
        uint64_t key = get_key(s, level, hashVec[i]);
        if (cell_cond[i])
            this->Remote.update(key, *s + DELIM);
        else
            this->Remote.insert(key, *s + DELIM);
    }
}




bool Wrapper::is_sub_str(string *all_value, string *element) {
    char *all = const_cast<char *>(all_value->c_str());
    char *sub = const_cast<char *>(element->c_str());
    char *pch;
    pch = strtok(all, DELIM);
    while (pch != nullptr) {
        if (strcmp(pch, sub) == 0)
            return true;
        pch = strtok(nullptr, DELIM);
    }
    return false;
}

////Getters Setters

ostream &operator<<(ostream &os, const Wrapper &wrapper) {
    for (int i = 0; i < wrapper.depth; ++i) {
        os << endl << "level " << i << endl;
        os << wrapper.BF_Vec[i] << endl;
    }
    return os;
}

const vector<GeneralBF> &Wrapper::getBfVec() const {
    return BF_Vec;
}

size_t Wrapper::get_depth() const {
    return depth;
}

bool Wrapper::is_adaptive() const {
    return isAdaptive;
}

size_t Wrapper::get_hash_vec_size_by_level(size_t level) {
    return this->BF_Vec[level].get_hash_vec_size();
}

uint64_t Wrapper::get_key(string *s, size_t level, size_t hashFunc_index) {
    return get_key(s, level, this->get_hashFunc(level, hashFunc_index));
}

uint64_t Wrapper::get_key(string *s, size_t level, Hash h) {
    return (h(s) << 4) + level; // NOLINT(hicpp-signed-bitwise)
}

Hash Wrapper::get_hashFunc(size_t level, size_t index) {
//    assert(level < depth);
    return this->BF_Vec[level].get_hash_vec()[index];
}


////paths
size_t Wrapper::count_files(const string &path) {
    size_t counter = 0;
    DIR *dir;
    struct dirent *ent;
    const char *char_path = path.c_str();
    if ((dir = opendir(char_path)) != nullptr) {
        while ((ent = readdir(dir)) != nullptr)
            counter++;
        closedir(dir);
        return counter;
    }
    return -1;
}

string Wrapper::create_new_path() {
    size_t counter = count_files(DEFAULT_PATH);
    string fileNum = to_string(counter);
    string new_file_name = DEFAULT_ABS_NAME + fileNum;
    string string_command = "mkdir " + new_file_name;
    const char *command = string_command.c_str();
    system(command);
    return new_file_name;
}

void Wrapper::delete_last_path() {
    size_t counter = count_files(DEFAULT_PATH);
    string fileNum = to_string(--counter);
    string new_file_name = DEFAULT_ABS_NAME + fileNum;
    string string_command = "rm -r " + new_file_name;
//    cout << string_command << endl;
    const char *command = string_command.c_str();
    system(command);

}

void Wrapper::delete_all_paths() {
    string temp = DEFAULT_PATH;
    string string_command = "rm -r " + temp + "*";
//    cout << string_command << endl;
    const char *command = string_command.c_str();
    system(command);
}
