// Task 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <string>

using Word = unsigned short;

constexpr Word signMask = static_cast<Word>(1u << 15);
constexpr Word magnitudeMask = static_cast<Word>((1u << 15) - 1u);

Word directCode(short value)
{
    const Word magnitude = static_cast<Word>(value < 0 ? -static_cast<int>(value) : value);
    return static_cast<Word>((value < 0 ? signMask : 0) | (magnitude & magnitudeMask));
}

Word directSum(Word first, Word second)
{
    const Word firstSign = first & signMask;
    const Word secondSign = second & signMask;
    const Word firstMagnitude = first & magnitudeMask;
    const Word secondMagnitude = second & magnitudeMask;

    if (firstSign == secondSign)
    {
        const Word magnitude = static_cast<Word>((firstMagnitude + secondMagnitude) & magnitudeMask);
        return static_cast<Word>(firstSign | magnitude);
    }

    if (firstMagnitude > secondMagnitude)
    {
        return static_cast<Word>(firstSign | (firstMagnitude - secondMagnitude));
    }

    if (secondMagnitude > firstMagnitude)
    {
        return static_cast<Word>(secondSign | (secondMagnitude - firstMagnitude));
    }

    return 0;
}


std::string binary(Word value)
{
    std::string result;
    result.reserve(19);

    for (int bit = 15; bit >= 0; --bit)
    {
        result += ((value >> bit) & 1u) ? '1' : '0';
        if (bit != 0 && bit % 4 == 0)
        {
            result += ' ';
        }
    }

    return result;
}

void printLine(short arithmeticValue, Word code)
{
    std::cout << std::dec << std::setw(6) << arithmeticValue << " | "
              << binary(code) << " | "
              << std::setfill('0') << std::setw(6) << std::oct
              << static_cast<unsigned int>(code) << " | "
              << std::setw(4) << std::hex
              << static_cast<unsigned int>(code) << '\n'
              << std::setfill(' ');
}

int main()
{
    short x;
    short y;
    std::cin >> x >> y;

    const short ordinarySum = static_cast<short>(x + y);

    printLine(x, static_cast<Word>(x));
    printLine(y, static_cast<Word>(y));
    printLine(ordinarySum, static_cast<Word>(ordinarySum));

    const Word xDirect = directCode(x);
    const Word yDirect = directCode(y);
    const Word sumDirect = directSum(xDirect, yDirect);

    printLine(x, xDirect);
    printLine(y, yDirect);
    printLine(ordinarySum, sumDirect);
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
