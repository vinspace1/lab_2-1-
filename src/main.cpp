#include<iostream>
#include<string>

#include"thirteen_array.h"

void clearInputBuffer() {
    std::cin.clear();
}

int main() {
    std::cout << "=== Base-13 Calculator ===\n\n";
    
    // Get first number
    std::string input1;
    std::cout << "Enter first number in base-13 (digits 0-9, A-C): ";
    std::cin >> input1;
    
    // Get second number
    std::string input2;
    std::cout << "Enter second number in base-13 (digits 0-9, A-C): ";
    std::cin >> input2;
    
    try {
        // Create ThirteenArray objects
        ThirteenArray num1(input1);
        ThirteenArray num2(input2);
        
        std::cout << "\n=== Input Numbers ===\n";
        std::cout << "Number 1: ";
        num1.print(std::cout);
        std::cout << " (as entered: " << input1 << ")\n";
        std::cout << "Number 2: ";
        num2.print(std::cout);
        std::cout << " (as entered: " << input2 << ")\n";
        
        std::cout << "\n=== Comparison Operations ===\n";
        
        // equals
        if (num1.equals(num2)) {
            std::cout << "Number 1 EQUALS Number 2\n";
        } else {
            std::cout << "Number 1 DOES NOT EQUAL Number 2\n";
        }
        
        // bigger
        if (num1.bigger(num2)) {
            std::cout << "Number 1 is BIGGER than Number 2\n";
        } else {
            std::cout << "Number 1 is NOT BIGGER than Number 2\n";
        }
        
        // less
        if (num1.less(num2)) {
            std::cout << "Number 1 is LESS than Number 2\n";
        } else {
            std::cout << "Number 1 is NOT LESS than Number 2\n";
        }
        
        std::cout << "\n=== Arithmetic Operations ===\n";
        
        // Addition
        try {
            ThirteenArray sumResult = num1.add(num2);
            std::cout << "Addition (num1 + num2): ";
            sumResult.print(std::cout);
            std::cout << "\n";
        } catch (const std::exception& e) {
            std::cout << "Addition failed: " << e.what() << "\n";
        }
        
        // Subtraction
        try {
            ThirteenArray subResult = num1.subtract(num2);
            std::cout << "Subtraction (num1 - num2): ";
            subResult.print(std::cout);
            std::cout << "\n";
        } catch (const std::exception& e) {
            std::cout << "Subtraction failed: " << e.what() << "\n";
        }
        
        std::cout << "\n=== Other Operations ===\n";
        
        // Copy constructor
        ThirteenArray copy1 = num1.copy();
        std::cout << "Copy of Number 1: ";
        copy1.print(std::cout);
        std::cout << "\n";
        
        // Default constructor
        ThirteenArray defaultNum;
        std::cout << "Default constructed number: ";
        defaultNum.print(std::cout);
        std::cout << " (empty)\n";
        
        // Constructor with size and default value
        ThirteenArray sizedNum(5, 'A');
        std::cout << "Number with size 5, default 'A': ";
        sizedNum.print(std::cout);
        std::cout << "\n";
        
        // Validate
        std::cout << "\n=== Validation ===\n";
        std::cout << "Number 1 is " << (num1.validate() ? "VALID" : "INVALID") << "\n";
        std::cout << "Number 2 is " << (num2.validate() ? "VALID" : "INVALID") << "\n";
        
        // Print in different ways
        std::cout << "\n=== Output Formats ===\n";
        std::cout << "Number 1 (print method): ";
        num1.print(std::cout);
        std::cout << "\n";
        
        std::cout << "Number 2 (print method): ";
        num2.print(std::cout);
        std::cout << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "\nError creating numbers: " << e.what() << "\n";
        return 1;
    }
    
    // Interactive menu for additional operations
    char choice;
    do {
        std::cout << "\n=== Additional Tests ===\n";
        std::cout << "1. Test with different numbers\n";
        std::cout << "2. Test initializer list constructor\n";
        std::cout << "3. Test edge cases\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case '1': {
                std::string numStr;
                std::cout << "Enter a number to test: ";
                std::cin >> numStr;
                
                try {
                    ThirteenArray testNum(numStr);
                    std::cout << "Created number: ";
                    testNum.print(std::cout);
                    std::cout << "\n";
                    
                    // Test operations with itself
                    ThirteenArray selfSum = testNum.add(testNum);
                    std::cout << "Number + itself: ";
                    selfSum.print(std::cout);
                    std::cout << "\n";
                    
                    ThirteenArray zero = testNum.subtract(testNum);
                    std::cout << "Number - itself: ";
                    zero.print(std::cout);
                    std::cout << "\n";
                    
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
                break;
            }
            
            case '2': {
                // Test initializer list constructor
                ThirteenArray initListNum({'1', '2', '3', 'A', 'B', 'C'});
                std::cout << "Initializer list number: ";
                initListNum.print(std::cout);
                std::cout << "\n";
                break;
            }
            
            case '3': {
                // Test edge cases
                std::cout << "\n=== Edge Cases ===\n";
                
                ThirteenArray zero("0");
                std::cout << "Zero: ";
                zero.print(std::cout);
                std::cout << "\n";
                
                ThirteenArray maxDigit("C");
                std::cout << "Max digit (C): ";
                maxDigit.print(std::cout);
                std::cout << "\n";
                
                ThirteenArray largeNum("CCC");
                std::cout << "Large number (CCC): ";
                largeNum.print(std::cout);
                std::cout << "\n";
                
                // Test addition with zero
                ThirteenArray testNum("123");
                ThirteenArray sumWithZero = testNum.add(zero);
                std::cout << "123 + 0 = ";
                sumWithZero.print(std::cout);
                std::cout << "\n";
                
                break;
            }
            
            case '4':
                std::cout << "Goodbye!\n";
                break;
                
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != '4');
    
    return 0;
}