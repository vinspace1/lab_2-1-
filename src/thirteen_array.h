#pragma once

#include <string>
#include <iostream>

class ThirteenArray {
public:
    ThirteenArray();
    ThirteenArray(const size_t& arraySize, unsigned char defaultValue = 0);
    ThirteenArray(const std::initializer_list<unsigned char>& initialValues);
    ThirteenArray(const std::string& sourceString);
    
    ThirteenArray(const ThirteenArray& other);
    ThirteenArray(ThirteenArray&& other) noexcept;

    ThirteenArray add(const ThirteenArray& other);
    ThirteenArray copy();
    ThirteenArray subtract(const ThirteenArray& other);
    bool sizeCmp(const ThirteenArray& other);
    bool equals(const ThirteenArray& other) const;
    bool bigger(const ThirteenArray& other) const;
    bool less(const ThirteenArray& other) const;
    std::ostream& print(std::ostream& outputStream);
    bool validate();

    virtual ~ThirteenArray() noexcept;

private:
    size_t arraySize;           
    unsigned char* dataArray;   
};

unsigned char toThirteen(int num);
int sum(unsigned char left, unsigned char right);
int sub(unsigned char left, unsigned char right);
int toDec(unsigned char num);