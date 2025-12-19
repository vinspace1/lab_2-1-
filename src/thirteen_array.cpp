#include "thirteen_array.h"

// Конструктор по умолчанию
ThirteenArray::ThirteenArray() : arraySize(0), dataArray(nullptr) {}

// Конструктор с заполнением
ThirteenArray::ThirteenArray(const size_t& arraySize, unsigned char defaultValue) {
    // преобразуем символы в верхний регистр для однообразия
    if(defaultValue >= 'a' && defaultValue <= 'c'){
        defaultValue += 'A' - 'a';
    }
    //проверка на соответствие символа используемым символам в тринадцатеричной системе
    if(!(defaultValue >= '0' && defaultValue <= '9') && !(defaultValue >= 'A' && defaultValue <= 'C')){
        this->arraySize = 0;
        this->dataArray = nullptr;
    }
    else{
        this->arraySize = arraySize;
        this->dataArray = new unsigned char[arraySize];
        for (size_t i = 0; i < arraySize; ++i) {
            this->dataArray[i] = defaultValue;
        }
    }
}

// Конструктор из списка инициализации (C++11)
ThirteenArray::ThirteenArray(const std::initializer_list<unsigned char>& initialValues) {
    arraySize = initialValues.size();
    dataArray = new unsigned char[arraySize];
    
    size_t index = 0;
    for (const auto& value : initialValues) {
        unsigned char processedValue = value;
        
        // Convert lowercase to uppercase
        if (value >= 'a' && value <= 'c') {
            processedValue = value + ('A' - 'a');
        }
        
        // Validate the character
        if ((processedValue >= '0' && processedValue <= '9') || 
            (processedValue >= 'A' && processedValue <= 'C')) {
            dataArray[index++] = processedValue;
        } else {
            // Invalid character found - clean up and set to empty array
            delete[] dataArray;
            dataArray = nullptr;
            arraySize = 0;
            return;
        }
    }
}

// Конструктор из строки
ThirteenArray::ThirteenArray(const std::string& sourceString) {
    // Handle empty string
    if (sourceString.empty()) {
        arraySize = 0;
        dataArray = nullptr;
        return;
    }
    
    // Find the first non-zero character (skip leading zeros)
    size_t startPos = 0;
    while (startPos < sourceString.length() - 1 && sourceString[startPos] == '0') {
        startPos++;
    }
    
    // Calculate actual size (excluding leading zeros)
    arraySize = sourceString.length() - startPos;
    
    // Allocate memory
    dataArray = new unsigned char[arraySize];
    
    // Process and copy characters (store in reverse order - least significant digit first)
    size_t destIndex = 0;
    for (size_t i = sourceString.length(); i > startPos; --i) {
        unsigned char ch = sourceString[i - 1]; // Access from the end
        
        // Convert lowercase to uppercase
        if (ch >= 'a' && ch <= 'c') {
            ch = ch + ('A' - 'a');
        }
        
        // Validate character
        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'C')) {
            dataArray[destIndex++] = ch;
        } else {
            // Invalid character found - clean up and create empty array
            delete[] dataArray;
            dataArray = nullptr;
            arraySize = 0;
            return;
        }
    }
}

// Копирующий конструктор (глубокое копирование)
ThirteenArray::ThirteenArray(const ThirteenArray& other) {
    arraySize = other.arraySize;
    dataArray = new unsigned char[arraySize];
    
    for (size_t i = 0; i < arraySize; ++i) {
        dataArray[i] = other.dataArray[i];
    }
}

// Перемещающий конструктор (C++11) - "крадет" ресурсы
ThirteenArray::ThirteenArray(ThirteenArray&& other) noexcept {
    arraySize = other.arraySize;
    dataArray = other.dataArray;
    
    other.arraySize = 0;
    other.dataArray = nullptr;
}

// Сложение
ThirteenArray ThirteenArray::add(const ThirteenArray& other) {
    size_t maxSize = (arraySize > other.arraySize) ? arraySize : other.arraySize;
    
    ThirteenArray result(maxSize + 1, '0');
    
    int carry = 0;
    
    for (size_t i = 0; i < maxSize; ++i) {
        int digit1 = (i < arraySize) ? toDec(dataArray[i]) : 0;
        int digit2 = (i < other.arraySize) ? toDec(other.dataArray[i]) : 0;
        
        int sum = digit1 + digit2 + carry;
        result.dataArray[i] = toThirteen(sum % 13);
        carry = sum / 13;
    }
    
    if (carry > 0) {
        result.dataArray[maxSize] = toThirteen(carry);
    } else {
        ThirteenArray trimmedResult(maxSize, '0');
        for (size_t i = 0; i < maxSize; ++i) {
            trimmedResult.dataArray[i] = result.dataArray[i];
        }
        return trimmedResult;
    }
    
    return result;
}

ThirteenArray ThirteenArray::copy(){
    ThirteenArray result(*this);
    return result;
}

bool ThirteenArray::sizeCmp(const ThirteenArray& other){
    return arraySize == other.arraySize;
}

bool ThirteenArray::bigger(const ThirteenArray& other) const {
    if (arraySize > other.arraySize) {
        return true;
    }
    if (arraySize < other.arraySize) {
        return false;
    }
    
    for (size_t i = arraySize; i > 0; --i) {
        size_t idx = i - 1;
        if (dataArray[idx] > other.dataArray[idx]) {
            return true;
        }
        if (dataArray[idx] < other.dataArray[idx]) {
            return false;
        }
    }

    return false;
}

bool ThirteenArray::less(const ThirteenArray& other)const{
    return !(bigger(other) || equals(other));
}

// Разность (может выбрасывать исключение)
ThirteenArray ThirteenArray::subtract(const ThirteenArray& other) {
    if (this->less(other)) {
        throw std::logic_error("второе число не может быть больше первого");
    }
    
    if (this->equals(other)) {
        return ThirteenArray(1, '0');
    }
    
    size_t resultSize = arraySize;
    
    ThirteenArray result(resultSize, '0');
    
    int borrow = 0;
    
    for (size_t i = 0; i < resultSize; ++i) {
        int digit1 = toDec(dataArray[i]);
        
        int digit2 = (i < other.arraySize) ? toDec(other.dataArray[i]) : 0;
        
        digit1 -= borrow;
        borrow = 0;
        
        if (digit1 < digit2) {
            digit1 += 13;  
            borrow = 1;    
        }
        
        int diff = digit1 - digit2;
        result.dataArray[i] = toThirteen(diff);
    }
    
    size_t newSize = result.arraySize;
    while (newSize > 1 && result.dataArray[newSize - 1] == '0') {
        newSize--;
    }

    if (newSize != result.arraySize) {
        ThirteenArray trimmed(newSize, '0');
        for (size_t i = 0; i < newSize; ++i) {
            trimmed.dataArray[i] = result.dataArray[i];
        }
        return trimmed;
    }
    
    return result;
}

// Сравнение чисел на равенство
bool ThirteenArray::equals(const ThirteenArray& other) const {
    size_t thisFirstNonZero = arraySize;
    size_t otherFirstNonZero = other.arraySize;
    
    for (size_t i = arraySize; i > 0; --i) {
        if (dataArray[i - 1] != '0') {
            thisFirstNonZero = i;
            break;
        }
    }
    
    for (size_t i = other.arraySize; i > 0; --i) {
        if (other.dataArray[i - 1] != '0') {
            otherFirstNonZero = i;
            break;
        }
    }
    
    if (thisFirstNonZero == 0 && otherFirstNonZero == 0) {
        return true;
    }
    
    if ((thisFirstNonZero == 0) != (otherFirstNonZero == 0)) {
        return false;
    }
    
    if (thisFirstNonZero != otherFirstNonZero) {
        return false;
    }
    
    for (size_t i = 0; i < thisFirstNonZero; ++i) {
        if (dataArray[i] != other.dataArray[i]) {
            return false;
        }
    }
    
    return true;
}

// Вывод массива в поток
std::ostream& ThirteenArray::print(std::ostream& outputStream) {
    if (arraySize == 0 || dataArray == nullptr) {
        outputStream << "0";
        return outputStream;
    }
    
    for (size_t i = arraySize; i > 0; --i) {
        outputStream << dataArray[i - 1];
    }
    
    return outputStream;
}

bool ThirteenArray::validate(){
    for(size_t i = 0; i < arraySize; ++i){
        if((dataArray[i]<'0' || dataArray[i]>'9') && (dataArray[i]<'A' || dataArray[i]>'C')){
            return false;
        }
    }
    return true;
}

// Деструктор - освобождает динамическую память
ThirteenArray::~ThirteenArray() noexcept {
    
    // Освобождаем память, если она была выделена
    if (dataArray != nullptr) {
        delete[] dataArray;
        dataArray = nullptr;
    }
    
    // Обнуляем размер для безопасности
    arraySize = 0;
}

//Вспомогательные функции

unsigned char toThirteen(int num) {
    if (num >= 0 && num < 10) {
        return static_cast<unsigned char>('0' + num);
    } else if (num >= 10 && num <= 12) {
        return static_cast<unsigned char>('A' + (num - 10));
    }
    return '0';  // Invalid
}

int sum(unsigned char left, unsigned char right) {
    int bufLeft = toDec(left);
    int bufRight = toDec(right);
    return bufLeft + bufRight;
}

int sub(unsigned char left, unsigned char right) {
    int bufLeft = toDec(left);
    int bufRight = toDec(right);
    return bufLeft - bufRight;
}

int toDec(unsigned char num) {
    if (num >= '0' && num <= '9') {
        return num - '0';
    } else if (num >= 'A' && num <= 'C') {
        return 10 + (num - 'A');
    } else if (num >= 'a' && num <= 'c') {
        return 10 + (num - 'a');
    }
    return 0;  // Invalid
}