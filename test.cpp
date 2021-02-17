#include "../header/rectangle.hpp"

#include "gtest/gtest.h"

TEST(RectangleTest,AreaTest) {
    int test_width = 3;
    int test_height = 4;
    Rectangle test_rect;
    test_rect.set_width(test_width);
    test_rect.set_height(test_height);
    EXPECT_EQ(11,test_rect.area());
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
