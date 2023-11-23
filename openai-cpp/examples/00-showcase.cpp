#include "openai.hpp"
#include "project.h"

#include <iostream>
#include <string>

int main()
{
    openai::start(); // Will use the api key provided by `OPENAI_API_KEY` environment variable
                     // openai::start("your_API_key", "optional_organization"); // Or you can handle it yourself

    /*
        auto completion = openai::completion().create(R"(
                             {
                                 "model": "text-davinci-003",
                                 "prompt": "how many champions in league of legends game?",
                                 "max_tokens": 20,
                                 "temperature": 0
                             }
                             )"_json); // Using user-defined (raw) string literals
        std::cout << "Response is:\n"
                  << completion.dump(2) << '\n'

                  << completion["choices"][0]["text"] << '\n';

        auto image = openai::image().create({{"prompt", "A logo with a cello in a heart"},
                                             {"n", 1},
                                             {"size", "512x512"}}); // Using initializer lists
        std::cout << "Image URL is: "
                  << image.dump(2) << '\n'
                  << image["data"][0]["url"] << '\n';
    */

    while (1)
    {
        char team_color; // blue: b or red: r
        char is_my_turn;
        int myPosition;
        std::string myChampion;
        int ally, enemy;

        std::cout << "Choose Blue Team or Red Team [b/r]: ";
        std::cin >> team_color;

        if (team_color == 'b' || team_color == 'B')
        {
            ally = blue;
            enemy = red;
        }
        else if (team_color == 'r' || team_color == 'R')
        {
            ally = red;
            enemy = blue;
        }
        else
        {
            std::cout << "Wrong input : You can input B/b or R/r" << std::endl;
            continue;
        }

        std::cout << "1. Top\t\t2. Jungle\t3. Mid\t\t4. ADC\t\t5. Supporter" << std::endl;
        std::cout << "What is your position?" << std::endl;
        std::cin >> myPosition;

        champion::Ban_Champion Ban_List;
        champion::Ally_Champion Ally_List;
        champion::Enemy_Champion Enemy_List;

        // 1. input 10 ban list
        for (int i = 0; i < 10; i++)
        {
            std::string name;
            std::cout << "Input banned champions "
                      << "[" << i + 1 << "]"
                      << ": ";
            std::cin >> name;

            Ban_List.set_name(name);
        }

        // 2. check your pick turn or not
        int turn;
        for (turn = 0; turn < 10; turn++)
        {
            if (pick_order[turn] == ally)
            {
                std::cout << "Is it your pick turn? [y/n]: ";
                std::cin >> is_my_turn;
                // 2-1. if not, append pick list
                if (is_my_turn == 'n' || is_my_turn == 'N')
                {
                    std::string name;
                    std::cout << "Input picked champion: ";
                    std::cin >> name;

                    int position;
                    std::cout << "1. Top\t\t2. Jungle\t3. Mid\t\t4. ADC\t\t5. Supporter" << std::endl;
                    std::cout << "Input poistion: ";
                    std::cin >> position;

                    Ally_List.set_name(name);
                    Ally_List.set_position(position);
                }
                // 3. my turn -> suggest with ban & pick list
                else if (is_my_turn == 'y' || is_my_turn == 'Y')
                {
                    std::string ban_Str;
                    std::string ally_Str;
                    std::string enemy_Str;
                    std::string question;

                    ban_Str = "Banned Champions: ";
                    ban_Str += Ban_List.info_str();
                    ally_Str = "Ally Champions: ";
                    ally_Str += Ally_List.info_str();
                    enemy_Str = "Enemy Champions: ";
                    enemy_Str += Enemy_List.info_str();

                    question = ban_Str + ally_Str + enemy_Str + ". ";
                    question += "Which champion would be the best for ";
                    question += pos_str[myPosition];
                    question += " ?";

                    std::cout << question << std::endl;

                    // std::cout << completion(question, 300, 0) << std::endl;

                    std::cout << "Input picked champion: ";
                    std::cin >> myChampion;

                    Ally_List.set_name(myChampion);
                    Ally_List.set_position(myPosition);

                    turn++;
                    break;
                }
                else
                {
                    std::cout << "Wrong input : You can input Y/y or N/n";
                    turn--;
                    continue;
                }
            }
            else if (pick_order[turn] == enemy)
            {

                std::string name;
                std::cout << "Input picked champion: ";
                std::cin >> name;

                int position;
                std::cout << "1. Top\t\t2. Jungle\t3. Mid\t\t4. ADC\t\t5. Supporter" << std::endl;
                std::cout << "Input poistion: ";
                std::cin >> position;

                Enemy_List.set_name(name);
                Enemy_List.set_position(position);
            }

            Ban_List.print();
            Ally_List.print();
            Enemy_List.print();
        }
        for (; turn < 10; turn++)
        {
            // 4. append pick list
            if (pick_order[turn] == ally)
            {
                std::string name;
                std::cout << "Input picked champion: ";
                std::cin >> name;

                int position;
                std::cout << "1. Top\t\t2. Jungle\t3. Mid\t\t4. ADC\t\t5. Supporter" << std::endl;
                std::cout << "Input poistion: ";
                std::cin >> position;

                Ally_List.set_name(name);
                Ally_List.set_position(position);
            }
            else
            {

                std::string name;
                std::cout << "Input picked champion: ";
                std::cin >> name;

                int position;
                std::cout << "1. Top\t\t2. Jungle\t3. Mid\t\t4. ADC\t\t5. Supporter" << std::endl;
                std::cout << "Input poistion: ";
                std::cin >> position;

                Enemy_List.set_name(name);
                Enemy_List.set_position(position);
            }

            Ban_List.print();
            Ally_List.print();
            Enemy_List.print();
        }

        // 5. 상대법 with my 상대 라인 champion

        int command;
        do
        {
            std::cout << "1. Exit\t\t2. Next Game\t3. How to deal with my opponent\t\t4. Create a new champion" << std::endl;
            std::cout << "Enter Command: ";
            std::cin >> command;

            std::string question;
            std::string answer;
            std::string image_url;
            switch (command)
            {
            case command1:
                question += "How to deal with ";
                question += Enemy_List.get_myOpponent(myPosition);
                question += " with ";
                question += myChampion;
                question += "?";

                std::cout << question << std::endl;
                // answer = completion(question, 300, 0);
                // std::cout << answer << std::endl;
                break;
            case command2:
                question += "Banned Champions: ";
                question += Ban_List.info_str();
                question += "Ally Champions: ";
                question += Ally_List.info_str();
                question += "Enemy Champions: ";
                question += Enemy_List.info_str();
                question += "Create a new champion for instead of ";
                question += myChampion;
                question += ".";
                std::cout << question << std::endl;
                // answer = completion(question, 300, 0);
                // std::cout << answer << std::endl;

                question = answer;
                question += "Make a image of the champion.";
                std::cout << question << std::endl;
                // image_url = imageURL(question);
                // std::cout << image_url << std::endl;

                break;
            case next: // go to selecting team color
                break;
            case done: // exit program
                return 0;
            default:
                break;
            }
        } while (command != next);
    }

    return 0;
}
