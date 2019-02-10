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

TEST_F(tests, CheckRightStart) {
    auto v3 = std::make_unique < MyContainer<logging_allocator<MyStruct>>>();
    ASSERT_EQ(v3->firstElem, v3->currElem);
}

TEST_F(tests, ChaeckRightAdd) {
    auto v3 = std::make_unique < MyContainer<logging_allocator<MyStruct>>>();
    v3->Add(0);
    ASSERT_NE(v3->firstElem, v3->currElem);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
