#include <gtest/gtest.h>
#include "octal.h"
#include <stdexcept>

TEST(OctalTest, DefaultConstructor) {
    Octal oct;
    EXPECT_TRUE(oct.isZero());
    EXPECT_EQ(oct.toString(), "0");
    EXPECT_EQ(oct.size(), 1);
}

TEST(OctalTest, StringConstructor) {
    Octal oct("1234");
    EXPECT_EQ(oct.toString(), "1234");
    EXPECT_EQ(oct.size(), 4);
}

TEST(OctalTest, StringConstructorWithLeadingZeros) {
    Octal oct("0012");
    EXPECT_EQ(oct.toString(), "12");
    EXPECT_EQ(oct.size(), 2);
}

TEST(OctalTest, SizeConstructor) {
    Octal oct(3, 5);
    EXPECT_EQ(oct.toString(), "555");
    EXPECT_EQ(oct.size(), 3);
}

TEST(OctalTest, InitializerListConstructor) {
    std::initializer_list<unsigned char> list = {1, 2, 3, 4};
    Octal oct(list);
    EXPECT_EQ(oct.toString(), "1234");
    EXPECT_EQ(oct.size(), 4);
}

TEST(OctalTest, InvalidDigitsString) {
    EXPECT_THROW({ Octal oct("128"); }, std::invalid_argument);
}

TEST(OctalTest, InvalidDigitsSize) {
    EXPECT_THROW({ Octal oct(3, 8); }, std::invalid_argument);
}

TEST(OctalTest, InvalidDigitsList) {
    std::initializer_list<unsigned char> bad_list = {1, 2, 8};
    EXPECT_THROW({ Octal oct(bad_list); }, std::invalid_argument);
}

TEST(OctalTest, Addition) {
    Octal oct1("123");
    Octal oct2("456");
    Octal result = oct1.add(oct2);
    EXPECT_EQ(result.toString(), "601");
}

TEST(OctalTest, AdditionWithZero) {
    Octal oct1("123");
    Octal zero;
    Octal result = oct1.add(zero);
    EXPECT_EQ(result.toString(), "123");
}

TEST(OctalTest, Subtraction) {
    Octal oct1("601");
    Octal oct2("456");
    Octal result = oct1.subtract(oct2);
    EXPECT_EQ(result.toString(), "123");
}

TEST(OctalTest, SubtractionSameNumber) {
    Octal oct1("1234");
    Octal result = oct1.subtract(oct1);
    EXPECT_TRUE(result.isZero());
}

TEST(OctalTest, SubtractionUnderflow) {
    Octal oct1("123");
    Octal oct2("456");
    EXPECT_THROW({ oct1.subtract(oct2); }, std::underflow_error);
}

TEST(OctalTest, Multiplication) {
    Octal oct1("12");
    Octal oct2("3");
    Octal result = oct1.multiply(oct2);
    EXPECT_EQ(result.toString(), "36");
}

TEST(OctalTest, MultiplicationByZero) {
    Octal oct1("1234");
    Octal zero;
    Octal result = oct1.multiply(zero);
    EXPECT_TRUE(result.isZero());
}

TEST(OctalTest, ComparisonGreaterThan) {
    Octal oct1("456");
    Octal oct2("123");
    EXPECT_TRUE(oct1.isGreaterThan(oct2));
    EXPECT_FALSE(oct2.isGreaterThan(oct1));
}

TEST(OctalTest, ComparisonLessThan) {
    Octal oct1("123");
    Octal oct2("456");
    EXPECT_TRUE(oct1.isLessThan(oct2));
    EXPECT_FALSE(oct2.isLessThan(oct1));
}

TEST(OctalTest, ComparisonEqual) {
    Octal oct1("1234");
    Octal oct2("1234");
    EXPECT_TRUE(oct1.isEqual(oct2));
    
    Octal oct3("1235");
    EXPECT_FALSE(oct1.isEqual(oct3));
}

TEST(OctalTest, DigitAccess) {
    Octal oct("1234");
    EXPECT_EQ(oct.digitAt(0), 4);
    EXPECT_EQ(oct.digitAt(1), 3);
    EXPECT_EQ(oct.digitAt(2), 2);
    EXPECT_EQ(oct.digitAt(3), 1);
    EXPECT_EQ(oct.digitAt(10), 0);
}

TEST(OctalTest, LargeNumbers) {
    Octal oct1("7777777");
    Octal oct2("1");
    Octal result = oct1.add(oct2);
    EXPECT_EQ(result.toString(), "10000000");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}