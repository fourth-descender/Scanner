#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

enum state : uint8_t {
    INT_NUM = 1, ID
};

class token {
    private:
        std::string type, value;
    public:

        token(std::string type, std::string value)
            : type(type), value(value) 
            {};

        std::string get_type() const {
            return type;
        };

        std::string get_value() const {
            return value;
        };

        // for gtest assertions.
        friend bool operator==(const token& lhs, const token& rhs) {
            return lhs.get_type() == rhs.get_type() && lhs.get_value() == rhs.get_value();
        };

        // for gtest actual_tokens and expected_tokens.
        friend std::ostream& operator<<(std::ostream& os, const token& t) {
            return os << "{" << t.get_type() << ", " << t.get_value() << ")" << std::endl;
        };

};

extern const std::unordered_map<std::string, token> s_tokens;
extern const std::unordered_map<std::string, token> r_tokens;

class scanner {
    private:
        std::string buffer;
        std::ifstream text;
        std::ofstream output;
        std::vector<token> tokens;
        bool is_special(std::string s) const;
        bool is_reserved(std::string s) const;

    public:
        ~scanner();
        scanner(std::string, std::string);

        state scan(char);

        void scan();
        void save();
        void clear();
        void write();

        std::vector<token> get_tokens() const {
            return tokens;
        };
};


