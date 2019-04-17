//
// Created by tomer on 4/14/19.
//

#ifndef ABF_REMOTE_WRAPPER_H
#define ABF_REMOTE_WRAPPER_H

#include <sstream>
#include <iterator>
#include <ostream>

#include "../../Be_Tree_files/betree.hpp"
#include "../General_BF/GeneralBF.h"
#include "dirent.h"


#define DEFAULT_PATH "/home/tomer/Desktop/Project/Be_Tree/ABF_Remote/New_BF/BS_Paths"
#define DEFAULT_ABS_NAME "/home/tomer/Desktop/Project/Be_Tree/ABF_Remote/New_BF/BS_Paths/tempDir"

#define CACHE_SIZE 1ULL << 16
#define MAX_NODE_SIZE (1ULL << 6)
#define MIN_FLUSH_SIZE (MAX_NODE_SIZE / 4)
#define DELIM " "

typedef one_file_per_object_backing_store fbs;

enum actual_lookup_res {
    true_negative, false_positive, true_positive
};


class Wrapper {
    vector<GeneralBF> BF_Vec;
    fbs bs;
    swap_space sspace;
    betree<uint64_t, string> Remote;
    size_t depth;
    bool isAdaptive;
//    GeneralBF temp;

public:
    Wrapper(size_t n, double eps, bool isAdaptive);

    /*

//    Wrapper(size_t n, double eps, bool is_adaptive) : Wrapper(n, eps, is_adaptive, create_new_path()) {}
//    virtual ~Wrapper();
*/

    void add(string *s, size_t starting_level);

    void naive_add(string *s, size_t starting_level);

    void add(string *s, size_t starting_level, bool remote_trick);

    bool naive_lookup(string *s);

    actual_lookup_res lookup_verifier(string *s, bool call_adapt);

    actual_lookup_res lookup_verifier(string *s, bool call_adapt, bool remote_trick);

    const vector<GeneralBF> &getBfVec() const;

    size_t get_depth() const;

    bool is_adaptive() const;

    friend ostream &operator<<(ostream &os, const Wrapper &wrapper);

    size_t get_hash_vec_size_by_level(size_t level);

    static size_t count_files(const string &path);


private:

    void remote_add(string *s, size_t level);

    void remote_add(string *s, size_t level, const bool *cell_cond);

    actual_lookup_res remote_lookup(string *s, size_t key);

    actual_lookup_res remote_lookup(string *s, size_t key, bool remote_trick);

    void adapt(string *s, size_t level);

    size_t adapt_choose_which_index_to_stale(string *s, size_t level);

    void adapt_by_index_level(size_t level, size_t index);

    void adapt_insertion(string *all_elements, size_t level_to_insert_in);

    Hash get_hashFunc(size_t level, size_t index);

    uint64_t get_key(string *s, size_t level, size_t hashFunc_index = 0);

    static uint64_t get_key(string *s, size_t level, Hash h);



    static string create_new_path();

    static void delete_last_path();

    static void delete_all_paths();

    static bool is_sub_str(string *all_value, string *element);


};

#endif //ABF_REMOTE_WRAPPER_H



/*string retrive(string *s);

 //    int add(string* s, bool get_first_fp_hashFunc_index);

//    int compare_Remote_Filter(string *s);

//private:
Wrapper(size_t n, double eps, bool is_adaptive, string path) : {
    if (is_adaptive) {
        this->depth = get_depth(n, eps);
        size_t mList[depth], kList[depth];
        get_bitArrays_size_list(n, eps, mList, depth);
        get_hashFunctions_num_list(n, eps, kList, mList, depth);
        for (int i = 0; i < depth; ++i)
            BF_Vec.emplace_back(mList[i], kList[i], true);
    } else {
        this->depth = 1;
        BF_Vec.emplace_back(n, eps, false);
    }

    one_file_per_object_backing_store bs(path);
        swap_space sspace(&bs, CACHE_SIZE);
        this->Remote = new betree<uint64_t, std::string>(&sspace, MAX_NODE_SIZE, MIN_FLUSH_SIZE);
        this->is_adaptive = is_adaptive;
    }



public:
    Wrapper(const vector<GeneralBF> &bfVec, const fbs &bs, const swap_space &sspace,
            const betree<uint64_t, string> &remote, size_t depth, bool is_adaptive);
*/
