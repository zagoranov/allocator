#include "alloc.h"
#include <gtest/gtest.h>
#include <memory>


class tests : public ::testing::Test {
public:
    tests() { /* init protected members here */ }
    ~tests() { /* free protected members here */ }
    void SetUp() { /* called before every test */ }
    void TearDown() { /* called after every test */ }

protected:
    /* none yet */
};

TEST_F(tests, CheckCreateMap) {
    auto m2 = std::map<int, int, std::less<int>, tenobj_allocator<std::pair<const int, int>> >{};
    ASSERT_NE(m2, nullptr);
}

TEST_F(tests, CheckCreateMyCont) {
    auto m2 = std::make_unique < MyContainer<tenobj_allocator<MyStruct>>>();
    ASSERT_NE(m2, nullptr);
}

TEST_F(tests, CheckRightStart) {
    auto v3 = std::make_unique < MyContainer<tenobj_allocator<MyStruct>>>();
    ASSERT_EQ(v3->firstElem, v3->currElem);
}

TEST_F(tests, CheckRightAdd) {
    auto v3 = std::make_unique < MyContainer<tenobj_allocator<MyStruct>>>();
    v3->Add(0);
    v3->Add(1);
    ASSERT_NE(v3->firstElem, v3->currElem);
}

TEST_F(tests, CheckConsistence) {
    auto v3 = std::make_unique < MyContainer<tenobj_allocator<MyStruct>>>();
    v3->Add(0);
    v3->Add(1);
    ASSERT_EQ(*(v3->begin()), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
