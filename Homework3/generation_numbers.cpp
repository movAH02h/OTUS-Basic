
#include "generation_numbers.h"

int print_each_minimum_efforts()
{
    std::fstream reading_file("result.txt", std::ios_base::in);
    std::unordered_map<std::string, int> um;
    if (reading_file.is_open())
    {
        std::string name = "";
        int efforts = 0;
        while (reading_file >> name >> efforts)
        {
            if (um.find(name) != um.end())
            {
                um[name] = std::min(um[name], efforts);
            }
            else um[name] = efforts;
        }
        reading_file.close();
    }
    else
    {
        return EXIT_FAILURE;
    } 

    std::cout << "\nHigh scores table:\n";
    for (const auto& [key, value] : um)
    {
        std::cout << key << " " << value << "\n";
    }

    return EXIT_SUCCESS;
}

int print_result_table()
{
    std::fstream reading_file("result.txt", std::ios_base::in);
    if (reading_file.is_open())
    {
        std::cout << "High score table:\n";
        std::string name = "";
        int efforts = 0;
        while (reading_file >> name >> efforts)
        {
            std::cout << name << " " << efforts << "\n";
        }
        reading_file.close();
    }
    else
    {
        return EXIT_FAILURE;
    } 

    return EXIT_SUCCESS;
}

int get_random_number(int _max)
{
    std::srand(time(nullptr));
    return rand() % _max;
}

int update_table(std::string name, int new_result)
{
    std::cout << "Updating result table...\n";
    std::fstream reading_file("result.txt", std::ios::in);
    std::unordered_map<std::string, int> um;
    if (reading_file.is_open())
    {
        std::string temp_name = "";
        int efforts = 0;
        while (reading_file >> temp_name >> efforts)
        {
            if (um.find(temp_name) != um.end())
            {
                um[temp_name] = std::min(um[temp_name], efforts);
            }
            else um[temp_name] = efforts;
        }
    }
    else
    {
        return EXIT_FAILURE;
    }

    if (um.find(name) != um.end())
    {
        um[name] = std::min(new_result, um[name]);
    }
    else
    {
        um[name] = new_result;
    } 


    std::fstream writing_file("result.txt", std::ios::out);
    if (writing_file.is_open())
    {
        for (const auto& [key, value] : um)
        {
            writing_file << key << " " << value << "\n";
        }
        writing_file.close();
    }
    else
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

