#include "single_list.h"
#include "common.h"
#include <gtest/gtest.h>

TEST(List, initialization) {
    SingleList<int> list;
    EXPECT_EQ(list.size(), 0);
}

TEST(List, insert_back) {
    {
        SingleList<int> list;

        list.push_back(10);
        EXPECT_EQ(list.size(), 1);
        EXPECT_EQ(list[0], 10);

        list.push_back(20);
        EXPECT_EQ(list.size(), 2);
        EXPECT_EQ(list[0], 10);
        EXPECT_EQ(list[1], 20);

        list.push_back(30);
        EXPECT_EQ(list.size(), 3);
        EXPECT_EQ(list[0], 10);
        EXPECT_EQ(list[1], 20);
        EXPECT_EQ(list[2], 30);
    }
    {
        SingleList<int> list;

        list.insert(0, 10);
        EXPECT_EQ(list.size(), 1);
        EXPECT_EQ(list[0], 10);

        list.insert(1, 20);
        EXPECT_EQ(list.size(), 2);
        EXPECT_EQ(list[0], 10);
        EXPECT_EQ(list[1], 20);

        list.insert(2, 30);
        EXPECT_EQ(list.size(), 3);
        EXPECT_EQ(list[0], 10);
        EXPECT_EQ(list[1], 20);
        EXPECT_EQ(list[2], 30);
    }
}

TEST(List, insert_front) {
    SingleList<int> list;

    list.insert(0, 10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], 10);

    list.insert(0, 20);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 20);
    EXPECT_EQ(list[1], 10);

    list.insert(0, 30);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], 30);
    EXPECT_EQ(list[1], 20);
    EXPECT_EQ(list[2], 10);
}

TEST(List, insert_middle) {
    SingleList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.insert(1, 15);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 15);
    EXPECT_EQ(list[2], 20);
    EXPECT_EQ(list[3], 30);

    list.insert(2, 17);
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 15);
    EXPECT_EQ(list[2], 17);
    EXPECT_EQ(list[3], 20);
    EXPECT_EQ(list[4], 30);
}

TEST(List, erase_back) {
    SingleList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.erase(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 20);

    list.erase(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], 10);
    
    list.erase(0);
    EXPECT_EQ(list.size(), 0);    
}

TEST(List, erase_front) {
    SingleList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.erase(0);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 20);
    EXPECT_EQ(list[1], 30);

    list.erase(0);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], 30);
    
    list.erase(0);
    EXPECT_EQ(list.size(), 0);
}

TEST(List, erase_middle) {
    SingleList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    list.erase(1);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 30);
    EXPECT_EQ(list[2], 40);

    list.erase(1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 40);
}

TEST(List, get_set) {
    SingleList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 20);
    EXPECT_EQ(list[2], 30);
    EXPECT_EQ(list[3], 40);

    for (size_t i = 0; i < list.size(); i++) {
        list[i] += 1;
    }

    EXPECT_EQ(list[0], 11);
    EXPECT_EQ(list[1], 21);
    EXPECT_EQ(list[2], 31);
    EXPECT_EQ(list[3], 41);
}

TEST(List, get_set_iterator) {
    SingleList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);    

    auto it = list.begin();
    EXPECT_EQ(*it, 10);
    
    ++it;
    EXPECT_EQ(*it, 20);

    ++it;
    EXPECT_EQ(*it, 30);
    

    for (it = list.begin(); it != list.end(); ++it) {
        *it += 2;
    }

    it = list.begin();
    EXPECT_EQ(*it, 12);

    ++it;
    EXPECT_EQ(*it, 22);

    ++it;
    EXPECT_EQ(*it, 32);
}

TEST(List, copy) {
    SingleList<int> list1;

    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    SingleList<int> list2 = list1;

    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list2.size(), 3);

    EXPECT_EQ(list1[0], 10);
    EXPECT_EQ(list1[1], 20);
    EXPECT_EQ(list1[2], 30);

    EXPECT_EQ(list2[0], 10);
    EXPECT_EQ(list2[1], 20);
    EXPECT_EQ(list2[2], 30);
}

TEST(List, delete_elements) {
    int cnt = 0;
    {
        SingleList<TestElement> list;
        list.push_back(TestElement(&cnt));
        list.push_back(TestElement(&cnt));
        list.push_back(TestElement(&cnt));

        EXPECT_EQ(cnt, 3) << "counter should be 3";
    }

    EXPECT_EQ(cnt, 0) << "after destruction counter should be 0";
}

TEST(List, move_container) {    
    SingleList<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    SingleList<int> list2;
    list2.push_back(100);
    list2.push_back(200);
    list2.push_back(300);
    list2.push_back(400);

    list1 = std::move(list2);

    EXPECT_EQ(list1.size(), 4);
    EXPECT_EQ(list1[0], 100);
    EXPECT_EQ(list1[1], 200);
    EXPECT_EQ(list1[2], 300);
    EXPECT_EQ(list1[3], 400);

    EXPECT_EQ(list2.size(), 0);
}