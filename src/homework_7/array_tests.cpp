#include "array.h"
#include "common.h"
#include <gtest/gtest.h>

TEST(Array, initialization) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(Array, push_back) {
    Array<int> arr;
    
    arr.push_back(10);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 10);

    arr.push_back(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);

    arr.push_back(30);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(Array, insert_back) {
    Array<int> arr;
    
    arr.insert(0, 10);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 10);

    arr.insert(1, 20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);

    arr.insert(2, 30);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);    
}

TEST(Array, insert_front) {
    Array<int> arr;
    arr.push_back(10);    

    arr.insert(0, 20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 20);
    EXPECT_EQ(arr[1], 10);

    arr.insert(0, 30);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 30);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 10);
}

TEST(Array, insert_middle) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(30);

    arr.insert(1, 20);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    arr.insert(2, 25);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 25);
    EXPECT_EQ(arr[3], 30);
}

TEST(Array, erase_back) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    arr.erase(2);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);

    arr.erase(1);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 10);    

    arr.erase(0);
    EXPECT_EQ(arr.size(), 0);
}

TEST(Array, erase_front) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    arr.erase(0);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 20);
    EXPECT_EQ(arr[1], 30);

    arr.erase(0);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 30);   

    arr.erase(0);
    EXPECT_EQ(arr.size(), 0); 
}

TEST(Array, erase_middle) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    arr.push_back(40);

    arr.erase(1);
    EXPECT_EQ(arr.size(), 3); 
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
    EXPECT_EQ(arr[2], 40);

    arr.erase(1);
    EXPECT_EQ(arr.size(), 2); 
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 40);
}

TEST(Array, get_set) {
    Array<int> arr;

    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    arr.push_back(40);

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 40);

    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] += 1;
    }

    EXPECT_EQ(arr[0], 11);
    EXPECT_EQ(arr[1], 21);
    EXPECT_EQ(arr[2], 31);
    EXPECT_EQ(arr[3], 41);
}

TEST(Array, get_set_iterator) {
    Array<int> arr;

    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);    

    auto it = arr.begin();
    EXPECT_EQ(*it, 10);
    
    ++it;
    EXPECT_EQ(*it, 20);

    ++it;
    EXPECT_EQ(*it, 30);
    

    for (it = arr.begin(); it != arr.end(); ++it) {
        *it += 2;
    }

    it = arr.begin();
    EXPECT_EQ(*it, 12);

    ++it;
    EXPECT_EQ(*it, 22);

    ++it;
    EXPECT_EQ(*it, 32);
}

TEST(Array, copy) {
    Array<int> arr1;

    arr1.push_back(10);
    arr1.push_back(20);
    arr1.push_back(30);

    Array<int> arr2 = arr1;

    EXPECT_EQ(arr1.size(), 3);
    EXPECT_EQ(arr2.size(), 3);

    EXPECT_EQ(arr1[0], 10);
    EXPECT_EQ(arr1[1], 20);
    EXPECT_EQ(arr1[2], 30);

    EXPECT_EQ(arr2[0], 10);
    EXPECT_EQ(arr2[1], 20);
    EXPECT_EQ(arr2[2], 30);
}

TEST(Array, delete_elements) {    
    int cnt = 0;
    {
        Array<TestElement> arr;
        arr.push_back(TestElement(&cnt));
        arr.push_back(TestElement(&cnt));
        arr.push_back(TestElement(&cnt));

        EXPECT_EQ(cnt, 3) << "counter should be 3";
    }

    EXPECT_EQ(cnt, 0) << "after destruction counter should be 0";
}

TEST(Array, move_container) {    
    Array<int> arr1;
    arr1.push_back(10);
    arr1.push_back(20);
    arr1.push_back(30);

    Array<int> arr2;
    arr2.push_back(100);
    arr2.push_back(200);
    arr2.push_back(300);
    arr2.push_back(400);

    arr1 = std::move(arr2);

    EXPECT_EQ(arr1.size(), 4);
    EXPECT_EQ(arr1[0], 100);
    EXPECT_EQ(arr1[1], 200);
    EXPECT_EQ(arr1[2], 300);
    EXPECT_EQ(arr1[3], 400);

    EXPECT_EQ(arr2.size(), 0);
}