#include "parser.h"
#include "calculator.h"
#include "commandParser.h"
#include <iostream>
#include <cstring>

int main()
{
    try
    {
        Status status;
        Calculator calc;

         std::cout << "\n!q to quit\n";
        do {
            std::cout << "> ";
            Scanner scanner(std::cin);
            if (!scanner.IsEmpty()) {
                if (scanner.IsCommand()) {
                    CommandParser parser(scanner, calc);
                    status = parser.Execute();
                } else {
                    Parser parser(scanner, calc);
                    status = parser.Parse();
                    if (status == stOk) {
                        double result = parser.Calculate();
                        std::cout << result << std::endl;
                    } else {
                        std::cout << "Syntax error.\n";
                    }
                }
            } else {
                break;
            }
        } while (status != stQuit);
    }
    catch(std::bad_alloc)
    {
        std::cerr << "Out of memory!\n";
    }
    catch(...)
    {
        std::cerr << "Internal error\n";
    }

    return 0;
}
