#include "async.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <future>

TEST(LIB_test,simple_busket){
    std::size_t bulk = 5;
    std::stringstream in;
    auto h = async::connect(bulk,in);
    async::receive(h, "1", 1);
    async::disconnect(h);
    std::stringstream out;
    out<<"bulk: 1\n"; 
    ASSERT_EQ(in.str(),out.str());
}

TEST(LIB_test,hard_busket){
    std::size_t bulk = 5;
    std::stringstream in;
    auto h = async::connect(bulk,in);
    async::receive(h, "1", 1);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::disconnect(h);
    std::stringstream out;
    out<<"bulk: 1, 2, 3, 4, 5\nbulk: 6\nbulk: a, b, c, d\nbulk: 89\n";
    ASSERT_EQ(in.str(),out.str());
}

TEST(LIB_test,some_contexts_busket){
    std::size_t bulk = 5;
    std::stringstream in;
    auto h = async::connect(bulk,in);
    auto h2 = async::connect(bulk,in);
    auto h3 = async::connect(bulk,in);
    async::receive(h, "1", 1);
    async::receive(h2, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h3, "b\nc\nd\n}\n89\n", 11);
    async::disconnect(h);
    async::disconnect(h2);
    async::disconnect(h3);
    std::stringstream out;
    out<<"bulk: 2, 3, 4, 5, 6\nbulk: 1\nbulk: b, c, d, 89\n";
    ASSERT_EQ(in.str().length(),out.str().length());
}

