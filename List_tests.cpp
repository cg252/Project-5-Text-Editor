#include "List.hpp"
#include "unit_test_framework.hpp"
#include <vector>
#include <string>
#include <utility>

using namespace std;

// create a function to convert hte linked list 
//c ontetn into a regular vector so we can us e
// ASSERT_SEQUWNCE_EQUAL to check equality.
// way more efficient than using front() and iteators 
template <typename T>
// returns a vector, as desired. 
static vector<T> list_vec(const List<T> &l) {
    vector<T> v;

    for (typename List<T>::Iterator it = l.begin(); it != l.end(); ++it) {

        v.push_back(*it);
    }
    return v;
}

TEST(emptyCtor) {
    List<int> l;
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);

    ASSERT_TRUE(l.begin() == l.end());
}

TEST(push_front_one_then_more) {
    List<int> l;
    l.push_front(7);
    ASSERT_FALSE(l.empty());

    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.front(), 7);
    ASSERT_EQUAL(l.back(), 7);

    l.push_front(3);
    l.push_front(2);
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.front(), 2);
    ASSERT_EQUAL(l.back(), 7);

    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{2, 3, 7}));
}

TEST(push_back_one_then_more) {
    List<int> l;
    l.push_back(1);
    ASSERT_FALSE(l.empty());
    ASSERT_EQUAL(l.size(), 1);

    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 1);

    l.push_back(2);
    l.push_back(9);
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 9);
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{1, 2, 9}));
}

TEST(push_mix_front_back_order) {
    List<int> l;
    l.push_back(2);
    l.push_front(1);
    l.push_back(3);
    l.push_front(0);
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{0, 1, 2, 3}));

    ASSERT_EQUAL(l.front(), 0);
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_EQUAL(l.size(), 4);
}

TEST(pop_front_till_empty) {
    List<int> l;
    for (int k = 0; k < 5; ++k) l.push_back(k);
    ASSERT_EQUAL(l.front(), 0);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.size(), 4);
    l.pop_front();
    l.pop_front();

    ASSERT_EQUAL(l.front(), 3);
    ASSERT_EQUAL(l.back(), 4);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 4);
    ASSERT_EQUAL(l.back(), 4);
    l.pop_front();
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
    ASSERT_TRUE(l.begin() == l.end());
}

TEST(pop_back_til_empty) {
    List<int> l;
    for (int k = 0; k < 5; ++k) l.push_back(k);
    ASSERT_EQUAL(l.back(), 4);
    l.pop_back();
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_EQUAL(l.size(), 4);
    l.pop_back();
    l.pop_back();
    ASSERT_EQUAL(l.front(), 0);
    ASSERT_EQUAL(l.back(), 1);
    l.pop_back();
    ASSERT_EQUAL(l.front(), 0);
    ASSERT_EQUAL(l.back(), 0);
    l.pop_back();
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
}

TEST(clear_works_and_is_repeatable) {
    List<int> l;
    for (int i = 0; i < 12; ++i) {
        if (i % 2 == 0) l.push_front(i);
        else l.push_back(i);
    }
    ASSERT_FALSE(l.empty());
    l.clear();
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
    ASSERT_TRUE(l.begin() == l.end());

    l.clear(); // again
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
}

TEST(iterator_default_rules_basic) {
    List<int>::Iterator it;
    List<int>::Iterator it2;
    ASSERT_TRUE(it == it2);
    ASSERT_FALSE(it != it2);

    List<int> l;
    ASSERT_TRUE(l.begin() == l.end());
    ASSERT_TRUE(it != l.end());
    ASSERT_TRUE(it != l.begin());
}

TEST(iterator_forward_traverse_matches_inserts) {
    List<int> l;
    for (int i = 0; i < 6; ++i) l.push_back(i * 10);

    vector<int> v;

    for (List<int>::Iterator it = l.begin(); it != l.end(); ++it) {
        v.push_back(*it);
    }
    ASSERT_SEQUENCE_EQUAL(v, (vector<int>{0, 10, 20, 30, 40, 50}));
}

TEST(iterator_backward_from_end_is_ok) {
    List<int> l;
    for (int i = 0; i < 4; ++i) l.push_back(i + 1); // 1 2 3 4

    List<int>::Iterator it = l.end();
    --it;
    ASSERT_EQUAL(*it, 4);
    --it;
    ASSERT_EQUAL(*it, 3);
    --it;
    ASSERT_EQUAL(*it, 2);
    --it;
    ASSERT_EQUAL(*it, 1);
    ASSERT_TRUE(it == l.begin());
}

TEST(insert_on_end_is_push_backish) {
    List<int> l;
    auto it = l.insert(l.end(), 99);
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.front(), 99);
    ASSERT_EQUAL(l.back(), 99);
    ASSERT_EQUAL(*it, 99);
    ++it;
    ASSERT_TRUE(it == l.end());
}

TEST(insert_on_begin_is_push_frontish) {
    List<int> l;
    l.push_back(2);
    l.push_back(3);
    auto it = l.insert(l.begin(), 1);
    ASSERT_EQUAL(*it, 1);
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{1, 2, 3}));
    ASSERT_EQUAL(l.size(), 3);
}

TEST(insert_middle_real_middle) {
    List<int> l;
    for (int i = 1; i <= 5; ++i) l.push_back(i); 
    // 1 2 3 4 5

    auto it = l.begin();
    ++it;
    ++it; 
    auto it2 = l.insert(it, 888);
    ASSERT_EQUAL(*it2, 888);
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{1, 2, 888, 3, 4, 5}));
    ASSERT_EQUAL(l.size(), 6);
}

TEST(erase_begin_returns_new_begin) {
    List<int> l;
    for (int i = 0; i < 4; ++i) l.push_back(i);
    auto it = l.erase(l.begin());

    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(*it, 1);
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{1, 2, 3}));
}

TEST(erase_middle_returns_next_one) {
    List<int> l;
    for (int i = 0; i < 6; ++i) l.push_back(i);
    auto it = l.begin();
    ++it; 
    ++it; 
    auto ans = l.erase(it);
    ASSERT_EQUAL(*ans, 3);
    ASSERT_EQUAL(l.size(), 5);

    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{0, 1, 3, 4, 5}));
}

TEST(erase_last_returns_end) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);

    auto it = l.end();
    --it;
    ASSERT_EQUAL(*it, 30);
    auto ans = l.erase(it);
    ASSERT_TRUE(ans == l.end());
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.back(), 20);

    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{10, 20}));
}

TEST(erase_one_doesnt_break_other_iterator) {
    List<int> l;
    for (int i = 0; i < 5; ++i) l.push_back(i);

    auto it = l.begin();
    ++it; ++it; ++it; 
    ASSERT_EQUAL(*it, 3);

    auto it2 = l.begin();
    ++it2; 
    l.erase(it2);

    ASSERT_EQUAL(*it, 3);
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{0, 2, 3, 4}));
}

TEST(copy_ctor_is_deep_enough) {
    List<int> l;
    for (int i = 0; i < 7; ++i) l.push_back(i);
    List<int> l2(l);

    ASSERT_SEQUENCE_EQUAL(list_vec(l), list_vec(l2));
    ASSERT_EQUAL(l.size(), l2.size());

    l.pop_front();
    l.pop_back();

    ASSERT_SEQUENCE_EQUAL(list_vec(l2), (vector<int>{0, 1, 2, 3, 4, 5, 6}));
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{1, 2, 3, 4, 5}));
}

TEST(assign_operator_replaces_old_contents) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    List<int> l2;
    l2.push_back(9);
    l2.push_back(9);

    l2 = l;
    ASSERT_SEQUENCE_EQUAL(list_vec(l2), (vector<int>{1, 2, 3}));
    ASSERT_EQUAL(l2.size(), 3);
    ASSERT_EQUAL(l2.front(), 1);

    ASSERT_EQUAL(l2.back(), 3);

    l.pop_back();
    l.push_front(0);
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{0, 1, 2}));
    ASSERT_SEQUENCE_EQUAL(list_vec(l2), (vector<int>{1, 2, 3}));
}

TEST(self_assignment_is_fine_probably) {
    List<int> l;
    for (int i = 0; i < 4; ++i) l.push_back(i * 3);
    List<int> *p = &l;
    l = *p;
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{0, 3, 6, 9}));
    ASSERT_EQUAL(l.size(), 4);
}

TEST(references_are_real_refs_not_copies) {
    List<int> l;
    l.push_back(5);
    l.push_back(6);
    l.push_back(7);

    l.front() = 55;
    l.back() = 77;
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{55, 6, 77}));

    auto it = l.begin();
    ++it;
    *it = 655;
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<int>{55, 655, 77}));
}

TEST(works_with_string_too) {
    List<string> l;
    l.push_back("hi");
    l.push_front("yo");
    l.push_back("ok");

    ASSERT_EQUAL(l.front(), "yo");
    ASSERT_EQUAL(l.back(), "ok");
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<string>{"yo", "hi", "ok"}));

    auto it = l.begin();
    ++it;
    ASSERT_EQUAL(*it, "hi");
    l.erase(it);
    ASSERT_SEQUENCE_EQUAL(list_vec(l), (vector<string>{"yo", "ok"}));
}

TEST(iterator_arrow_operator_with_pair) {
    List<pair<int,int>> l;
    l.push_back({1, 2});
    
    l.push_back({3, 4});
    auto it = l.begin();
    ASSERT_EQUAL(it->first, 1);
    ASSERT_EQUAL(it->second, 2);
    ++it;
    ASSERT_EQUAL(it->first, 3);
    ASSERT_EQUAL(it->second, 4);
}

TEST_MAIN()
