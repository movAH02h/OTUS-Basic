#include <bits/stdc++.h>
#include "generation_numbers.h"

bool check(int argc, char* argv[])  
{
    bool flag_max = false;
    bool flag_level = false;
    for (int i = 0; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-max")) flag_max = true;
        else if (!strcmp(argv[i], "-level")) flag_level = true;
    }

    return flag_max && flag_level;
}

int main(int argc, char* argv[])
{
    if (check(argc, argv))
    {
        std::cerr << "Invalid parameters";
        return EXIT_SUCCESS;
    }

    // обработка параметров при запуске
    int _max = 100;
    for (int i = 1; i < argc; ++i)
    {
        if (!(strcmp(argv[i], "-table")))
        {
            if (!print_result_table())
            {
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
        else if (i + 1 < argc && !(strcmp(argv[i], "-max")))
        {
            _max = std::atoi(argv[i + 1]);
        }
        else if (i + 1 < argc && !(strcmp(argv[i], "-level")))
        {
            int level = std::atoi(argv[i + 1]);
            if (level == 1)
            {
                _max = 10;
            }
            else if (level == 2)
            {
                _max = 50; 
            }
        }
    }

    // Основная программа
    std::cout << "Hi! Enter your name:\n";
    std::string name; std::cin >> name;

    int target = get_random_number(_max);

    int efforts = 0;
    while (true)
    {
        std::cout << "Enter your guess: ";
        int number; std::cin >> number;
        efforts++;
        if (number < target)
        {
            std::cout << "greater than " << number << "\n";
        }
        else if (number > target)
        {
            std::cout << "less than " << number << "\n";
        }
        else
        {
            std::cout << "You win! attempts = " << efforts << "\n";
            // Для 4 дополнительного задания: update_table(name, efforts);

            // Для обычного (основного) задания ниже
            std::fstream output_file("result.txt", std::ios_base::app);
            if (output_file.is_open())
            {
                output_file << name << " " << efforts << "\n";
                output_file.flush();
                output_file.close();
            }
            else
            {
                std::cerr << "An error occured while opening the file\n";
                return EXIT_FAILURE;
            }
            break;
        }
    }

    // Проверка работы написанных функций
    std::cout << "\n"; 
    if (print_result_table())
    {
        std::cerr << "Error while executing print_result_table function";
        return 0;
    }


    std::cout << "Print only best results:\n";
    if (print_each_minimum_efforts())
    {
        std::cerr << "Error while executing get_minimum_efforts function";
        return EXIT_FAILURE;
    }

    // Пример работы 4 функции (это просто как работает функция для 4 доп задания)
    // Можно любые пары ключ-значения обновлять
    update_table("Kirill", 2);

    // Печать после обновления результатов
    print_result_table();
    return EXIT_SUCCESS;
}