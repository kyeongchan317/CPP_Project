#include "openai.hpp"

#include <iostream>
#include <string>

enum
{
    blue = 0,
    red = 1,
};

enum
{
    top = 0,
    jungle = 1,
    mid = 2,
    adcarry = 3,
    supporter = 4,
};

enum
{
    exit = 0,
    next = 1,
    command1 = 2,
};

namespace champion
{
    class Champion
    {
    public:
    private:
        std::string name;
        int position; // 0: top, 1: jungle, 2: mid, 3: adcarry, 4: supporter
    };
} // namespace champion

int main()
{
    openai::start(); // Will use the api key provided by `OPENAI_API_KEY` environment variable
                     // openai::start("your_API_key", "optional_organization"); // Or you can handle it yourself

    auto completion = openai::completion().create(R"(
                         {
                             "model": "text-davinci-003",
                             "prompt": "롤 챔피언의 수",
                             "max_tokens": 10,
                             "temperature": 0
                         }
                         )"_json); // Using user-defined (raw) string literals
    std::cout << "Response is:\n"
              << completion.dump(2) << '\n';

    auto image = openai::image().create({{"prompt", "A logo with a cello in a heart"},
                                         {"n", 1},
                                         {"size", "512x512"}}); // Using initializer lists
    std::cout << "Image URL is: " << image["data"][0]["url"] << '\n';

    while (1)
    {
        std::cout << "Choose Blue Team or Red Team [b/r]: \n"
                  << std::endl;

        char team_color; // blue: b or red: r
        std::cin >> team_color;

        if (team_color == 'b')
        {
        }
        else
        {
        }

        int next_command;
        do
        {
            std::cin >> next_command;
            switch (next_command)
            {
            case command1:
                break;
            case next: // go to selecting team color
                break;
            case exit: // exit program
                return;
            default:
                break;
            }
        } while (next_command != next);
    }
}
