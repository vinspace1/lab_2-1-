#include <gtest/gtest.h>
#include "../src/thirteen_array.h"
#include <stdexcept>
#include <string>

TEST(ThirteenArrayTest, DefaultConstructor) {
    ThirteenArray arr;
    EXPECT_EQ(arr.equals(ThirteenArray()), true);
}

TEST(ThirteenArrayTest, ConstructorWithSizeAndValue) {
    ThirteenArray arr1(3, '5');
    ThirteenArray arr2({'5', '5', '5'});
    EXPECT_TRUE(arr1.equals(arr2));
    
    ThirteenArray arr3(2, 'A');
    ThirteenArray arr4({'A', 'A'});
    EXPECT_TRUE(arr3.equals(arr4));
    
    ThirteenArray arr5(2, 'a'); 
    ThirteenArray arr6({'A', 'A'});
    EXPECT_TRUE(arr5.equals(arr6));
    
    ThirteenArray arr7(3, 'G');
    ThirteenArray arr8;
    EXPECT_TRUE(arr7.equals(arr8));
}

TEST(ThirteenArrayTest, InitializerListConstructor) {
    ThirteenArray arr1({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C'});
    EXPECT_EQ(arr1.equals(ThirteenArray("CBA9876543210")), true); 
    
    ThirteenArray arr2({'1', '2', '3'});
    ThirteenArray arr3("321");
    EXPECT_TRUE(arr2.equals(arr3));
}

TEST(ThirteenArrayTest, StringConstructor) {
    ThirteenArray arr1("123ABC");
    ThirteenArray arr2({'C', 'B', 'A', '3', '2', '1'});
    EXPECT_TRUE(arr1.equals(arr2));
    
    ThirteenArray arr3("0");
    ThirteenArray arr4({'0'});
    EXPECT_TRUE(arr3.equals(arr4));
    
    ThirteenArray arr5("");
    ThirteenArray arr6;
    EXPECT_TRUE(arr5.equals(arr6));
}

TEST(ThirteenArrayTest, CopyConstructor) {
    ThirteenArray arr1("123ABC");
    ThirteenArray arr2(arr1);
    EXPECT_TRUE(arr1.equals(arr2));
    
    ThirteenArray arr3(arr1);
    EXPECT_TRUE(arr1.equals(arr3));
}

TEST(ThirteenArrayTest, MoveConstructor) {
    ThirteenArray arr1("123ABC");
    ThirteenArray arr2(std::move(arr1));
    ThirteenArray empty;
    EXPECT_TRUE(arr1.equals(empty));
    EXPECT_FALSE(arr2.equals(empty));
}

TEST(ThirteenArrayTest, Addition) {
    // Test 1: Simple addition - 1 + 2 = 3
    {
        ThirteenArray arr1("1");
        ThirteenArray arr2("2");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("3");
        EXPECT_TRUE(result.equals(expected));
    }
    
    // Test 2: Addition with carry within digit - C + 1 = 10 (12 + 1 = 13 in decimal)
    {
        ThirteenArray arr1("C");
        ThirteenArray arr2("1");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("10");
        EXPECT_TRUE(result.equals(expected));
    }
    
    // Test 3: Addition with multi-digit carry - 2A + 15 = 42
    {
        ThirteenArray arr1("2A");
        ThirteenArray arr2("15");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("42");
        EXPECT_TRUE(result.equals(expected));
    }
    
    // Test 4: Different length numbers - 123 + 45 = 168
    {
        ThirteenArray arr1("123");
        ThirteenArray arr2("45");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("168");
        EXPECT_TRUE(result.equals(expected));
    }
    // Test 5: Numbers of equal length with final carry - C9 + C9 = 1С5
    {
        ThirteenArray arr1("C9");
        ThirteenArray arr2("C9");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("1C5");
        EXPECT_TRUE(result.equals(expected));
    }
    
    // Test 6: Adding to zero - 0 + ABC = ABC
    {
        ThirteenArray arr1("0");
        ThirteenArray arr2("ABC");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("ABC");
        EXPECT_TRUE(result.equals(expected));
    }
    
    // Test 7: Zero + zero = 0
    {
        ThirteenArray arr1("0");
        ThirteenArray arr2("0");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("0");
        EXPECT_TRUE(result.equals(expected));
    }
    
    // Test 8: Large numbers - 999 + 111 = AAA
    {
        ThirteenArray arr1("999");
        ThirteenArray arr2("111");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("AAA");
        EXPECT_TRUE(result.equals(expected));
    }
    
    // Test 9: Mixed case (lowercase input) - a + b = 18 (10 + 11 = 21 decimal = 1*13 + 8)
    {
        ThirteenArray arr1("a");
        ThirteenArray arr2("b");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("18");
        EXPECT_TRUE(result.equals(expected));
    }
    
    // Test 10: Adding with leading zeros - 001 + 002 = 3
    {
        ThirteenArray arr1("001");
        ThirteenArray arr2("002");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("3");
        EXPECT_TRUE(result.equals(expected));
    }
    
    // Test 11: Maximum digit addition - C + C = 1B (12 + 12 = 24 decimal = 1*13 + 11)
    {
        ThirteenArray arr1("C");
        ThirteenArray arr2("C");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("1B");
        EXPECT_TRUE(result.equals(expected));
    }
    
    // Test 12: Complex multi-digit with multiple carries - 9C8 + A7B = 1776
    {
        ThirteenArray arr1("9C8");
        ThirteenArray arr2("A7B");
        ThirteenArray result = arr1.add(arr2);
        ThirteenArray expected("1776");
        EXPECT_TRUE(result.equals(expected));
    }
}
// Test subtraction operation
TEST(ThirteenArrayTest, Subtraction) {
    ThirteenArray arr1("5");
    ThirteenArray arr2("3");
    ThirteenArray result1 = arr1.subtract(arr2);
    ThirteenArray expected1("2");
    EXPECT_TRUE(result1.equals(expected1));
    
    ThirteenArray arr3("10"); 
    ThirteenArray arr4("1");  
    ThirteenArray result2 = arr3.subtract(arr4);
    ThirteenArray expected2("C");
    EXPECT_TRUE(result2.equals(expected2));
    
    ThirteenArray arr5("42"); 
    ThirteenArray arr6("15"); 
    ThirteenArray result3 = arr5.subtract(arr6);
    ThirteenArray expected3("2A"); 
    EXPECT_TRUE(result3.equals(expected3));
    
    ThirteenArray arr7("ABC");
    ThirteenArray arr8("ABC");
    ThirteenArray result4 = arr7.subtract(arr8);
    ThirteenArray expected4("0");
    EXPECT_TRUE(result4.equals(expected4));

    ThirteenArray arr9("12");
    ThirteenArray arr10("123");
    EXPECT_THROW(arr9.subtract(arr10), std::logic_error);
    
    ThirteenArray arr11("5");
    ThirteenArray arr12("6");
    EXPECT_THROW(arr11.subtract(arr12), std::logic_error);
}

TEST(ThirteenArrayTest, Equality) {
    ThirteenArray arr1("123ABC");
    ThirteenArray arr2("123ABC");
    ThirteenArray arr3("123AB");
    ThirteenArray arr4("123ABD");
    
    EXPECT_TRUE(arr1.equals(arr2));
    EXPECT_FALSE(arr1.equals(arr3));
    EXPECT_FALSE(arr3.equals(arr4));
    
    ThirteenArray arr5("123");
    ThirteenArray arr6("0123");
    EXPECT_TRUE(arr5.equals(arr6));
}

TEST(ThirteenArrayTest, Comparisons) {
    ThirteenArray arr1("123");
    ThirteenArray arr2("124");
    ThirteenArray arr3("122");
    ThirteenArray arr4("123");
    ThirteenArray arr5("12");
    ThirteenArray arr6("1234");
    
    EXPECT_TRUE(arr2.bigger(arr1));
    EXPECT_FALSE(arr1.bigger(arr2));
    EXPECT_FALSE(arr1.bigger(arr4)); 
    
    EXPECT_TRUE(arr3.less(arr1));
    EXPECT_FALSE(arr1.less(arr3));
    EXPECT_FALSE(arr1.less(arr4)); 
    
    EXPECT_TRUE(arr1.equals(arr4));
    EXPECT_FALSE(arr1.equals(arr2));

    EXPECT_TRUE(arr6.bigger(arr1)); 
    EXPECT_TRUE(arr1.bigger(arr5)); 
}

TEST(ThirteenArrayTest, Print) {
    ThirteenArray arr("123ABC");
    
    std::stringstream ss;
    arr.print(ss);
    
    EXPECT_EQ(ss.str(), "123ABC");
}

TEST(ThirteenArrayTest, Validation) {
    ThirteenArray arr1("0123456789ABC");
    EXPECT_TRUE(arr1.validate());
    
    ThirteenArray arr2;
    EXPECT_TRUE(arr1.validate());
}

TEST(ThirteenArrayTest, HelperFunctions) {
    EXPECT_EQ(toThirteen(0), '0');
    EXPECT_EQ(toThirteen(5), '5');
    EXPECT_EQ(toThirteen(9), '9');
    EXPECT_EQ(toThirteen(10), 'A');
    EXPECT_EQ(toThirteen(11), 'B');
    EXPECT_EQ(toThirteen(12), 'C');
    
    EXPECT_EQ(sum('0', '0'), 0);
    EXPECT_EQ(sum('5', '3'), 8);
    EXPECT_EQ(sum('9', '1'), 10);
    EXPECT_EQ(sum('A', '2'), 12); 
    EXPECT_EQ(sum('C', 'C'), 24); 
    
    EXPECT_EQ(sub('5', '3'), 2);
    EXPECT_EQ(sub('C', 'A'), 2); 
    EXPECT_EQ(sub('1', '5'), -4);
    
    EXPECT_EQ(toDec('0'), 0);
    EXPECT_EQ(toDec('5'), 5);
    EXPECT_EQ(toDec('9'), 9);
    EXPECT_EQ(toDec('A'), 10);
    EXPECT_EQ(toDec('B'), 11);
    EXPECT_EQ(toDec('C'), 12);
}

TEST(ThirteenArrayTest, EdgeCases) {
    ThirteenArray empty1;
    ThirteenArray empty2;
    EXPECT_TRUE(empty1.equals(empty2));
    
    ThirteenArray zero("0");
    ThirteenArray one("1");
    ThirteenArray result = zero.add(one);
    EXPECT_TRUE(result.equals(one));
    
    ThirteenArray arr1("5");
    ThirteenArray arr2("5");
    ThirteenArray result2 = arr1.subtract(arr2);
    EXPECT_TRUE(result2.equals(zero));
    
    ThirteenArray maxDigit("C");
    ThirteenArray oneAgain("1");
    ThirteenArray result3 = maxDigit.add(oneAgain);
    ThirteenArray expected("10");
    EXPECT_TRUE(result3.equals(expected));
}

TEST(ThirteenArrayTest, CopyMethod) {
    ThirteenArray original("123ABC");
    ThirteenArray copy = original.copy();
    
    EXPECT_TRUE(original.equals(copy));
    EXPECT_FALSE(&original == &copy);
}

TEST(ThirteenArrayTest, SizeComparison) {
    ThirteenArray arr1("123");
    ThirteenArray arr2("123");
    ThirteenArray arr3("1234");
    
    EXPECT_TRUE(arr1.sizeCmp(arr2));
    EXPECT_FALSE(arr1.sizeCmp(arr3));
    EXPECT_FALSE(arr3.sizeCmp(arr1));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}