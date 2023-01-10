#include <gtest/gtest.h>
#include "terrorist.h"

TEST(Singletone, Test1){
    terrorist *ter1 = terrorist::get_self();
    terrorist *ter2 = terrorist::get_self();
    ASSERT_EQ(ter1, ter2);
}

TEST(Singletone, Test2){
    terrorist ter1;
    ASSERT_THROW(terrorist ter2, std::runtime_error);
    ASSERT_THROW(terrorist ter2("../test_files/test1"), std::runtime_error);
}

TEST(Singletone, Test3){
    terrorist ter1("../test_files/test1");
    ASSERT_NE(ter1.get_self(), nullptr);
}

TEST(Encryption, Test1){
    std::ifstream in("../test_files/test1/1.txt");
    std::string str = "Vmkvmfkvmdklfvmdflkvmlkvdf";
    std::stringstream buffer;
    buffer << in.rdbuf();
    ASSERT_EQ(str, buffer.str());
}

TEST(Encryption, Test2){
    terrorist ter1("../test_files/test1/");
    ter1.test_execution();
    ASSERT_FALSE(std::filesystem::exists("../test_files/test1/1.txt"));
    ASSERT_FALSE(std::filesystem::exists("../test_files/test1/2.txt"));
    ASSERT_FALSE(std::filesystem::exists("../test_files/test1/3.txt"));
    ASSERT_FALSE(std::filesystem::exists("../test_files/test1/bla/4.txt"));
    ASSERT_TRUE(std::filesystem::exists("../test_files/test1/1.txt.mod"));
    ASSERT_TRUE(std::filesystem::exists("../test_files/test1/2.txt.mod"));
    ASSERT_TRUE(std::filesystem::exists("../test_files/test1/3.txt.mod"));
    ASSERT_TRUE(std::filesystem::exists("../test_files/test1/bla/4.txt.mod"));
}

TEST(Encryption, Test3){
    std::ifstream in("../test_files/test1/1.txt.mod");
    std::string str = "Vmkvmfkvmdklfvmdflkvmlkvdf";
    std::stringstream buffer;
    buffer << in.rdbuf();
    ASSERT_NE(str, buffer.str());
}