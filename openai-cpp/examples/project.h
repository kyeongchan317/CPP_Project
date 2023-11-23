#include "openai.hpp"
#include <string>
#include <vector>

enum
{
    blue = 0,
    red = 1,
};
/*
enum
{
    top = 0,
    jungle = 1,
    mid = 2,
    adcarry = 3,
    supporter = 4,
};
 */
enum
{
    done = 1,
    next = 2,
    command1 = 3,
    command2 = 4,
};

int pick_order[10] = {blue, red, red, blue, blue, red, red, blue, blue, red};
std::string pos_str[6] = {"", "Top", "Jungle", "Mid", "ADC", "Supporter"};

namespace champion
{
    class Champion
    {
    public:
        Champion() {}
        virtual ~Champion() {}

        void set_name(const std::string &new_name) { names.push_back(new_name); }
        std::string get_name(int i) const { return names[i]; }

        std::string info_str()
        {
            std::string str;
            for (const auto &name : names)
            {
                str += name;
                str += ", ";
            }
            return str;
        }
        virtual void print() const
        {
            for (const auto &name : names)
            {
                std::cout << name << ", ";
            }
        }

    protected:
        std::vector<std::string> names;
    };

    class Ban_Champion : public Champion
    {
    public:
        Ban_Champion() : Champion() {}
        ~Ban_Champion() {}

        void print() const
        {
            std::cout << "Ban:\t";
            Champion::print();
            std::cout << std::endl;
        }
    };

    class Ally_Champion : public Champion
    {
    public:
        Ally_Champion() : Champion() {}
        ~Ally_Champion() {}

        void set_position(int new_position) { positions.push_back(new_position); }
        int get_position(int i) { return positions[i]; }

        void print() const
        {
            std::cout << "Ally:\t";
            for (size_t i = 0; i < names.size(); i++)
            {
                std::cout << "Name: " << names[i] << ", Position: " << pos_str[positions[i]] << "\t";
            }
            std::cout << std::endl;
        }

    private:
        std::vector<int> positions; // 0: top, 1: jungle, 2: mid, 3: adcarry, 4: supporter
    };

    class Enemy_Champion : public Champion
    {
    public:
        Enemy_Champion() : Champion() {}
        ~Enemy_Champion() {}

        void set_position(int new_position) { positions.push_back(new_position); }
        int get_position(int i) { return positions[i]; }

        std::string get_myOpponent(int myPos)
        {
            for (size_t i = 0; i < names.size(); i++)
            {
                if (positions[i] == myPos)
                    return names[i];
            }
            return "";
        }

        void print() const
        {
            std::cout << "Enemy:\t";
            for (size_t i = 0; i < names.size(); i++)
            {
                std::cout << "Name: " << names[i] << ", Position: " << pos_str[positions[i]] << "\t";
            }
            std::cout << std::endl;
        }

    private:
        std::vector<int> positions; // 0: top, 1: jungle, 2: mid, 3: adcarry, 4: supporter
    };
} // namespace champion

std::string completion(std::string prompt)
{
    nlohmann::json input;

    input["model"] = "text-davinci-003";
    input["prompt"] = prompt;
    input["max_tokens"] = 7;
    input["temperature"] = 0;

    auto completion = openai::completion().create(input);

    return (std::string)completion["choices"][0]["text"];
}

std::string completion(std::string prompt, int max_tokens)
{
    nlohmann::json input;

    input["model"] = "text-davinci-003";
    input["prompt"] = prompt;
    input["max_tokens"] = max_tokens;
    input["temperature"] = 0;

    auto completion = openai::completion().create(input);

    return (std::string)completion["choices"][0]["text"];
}

std::string completion(std::string prompt, int max_tokens, float temperature)
{
    nlohmann::json input;

    input["model"] = "text-davinci-003";
    input["prompt"] = prompt;
    input["max_tokens"] = max_tokens;
    input["temperature"] = temperature;

    auto completion = openai::completion().create(input);

    return (std::string)completion["choices"][0]["text"];
}
std::string imageURL(std::string prompt)
{
    nlohmann::json input;

    input["prompt"] = prompt;
    input["n"] = 1;
    input["size"] = "512x512";

    auto image = openai::image().create(input);

    return (std::string)image["data"][0]["url"];
}

std::string imageURL(std::string prompt, std::string size)
{
    nlohmann::json input;

    input["prompt"] = prompt;
    input["n"] = 1;
    input["size"] = size;

    auto image = openai::image().create(input);

    return (std::string)image["data"][0]["url"];
}

// 1. blue 1 ban suggest
// 2. red 1 ban by computer (with current ban list)(random)
// 3. blue 2 ban suggest (with current ban list)
// 4. red 2 ban by computer (with current ban list)(random)
// 5. blue 3 ban suggest (with current ban list)
// 6. red 3 ban by computer (with current ban list)(random)

// 7. blue 1 pick suggest (with current ban list)
// 8. red 1 pick, 2 pick by computer (with current ban list & pick list)(random)
// 9. blue 2 pick, 3 pick suggest (with current ban list & pick list)
// 10. red 3 pick by computer (with current ban list & pick list)(random)

// 11. red 4 ban by computer (with current ban list & pick list)(random)
// 12. blue 4 ban, 5 ban suggest (with current ban list & pick list)
// 13. red 5 ban by computer (with current ban list & pick list)(random)

// 14. red 4 pick by computer (with current ban list & pick list)(random)
// 15. blue 4 pick, 5 pick suggest (with current ban list & pick list)
// 16. red 5 pick by computer (with current ban list & pick list)(random)