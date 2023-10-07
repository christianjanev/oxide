#pragma once

enum class TokenType {
    exit,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

class Tokenizer {

public:
    static std::vector<Token> tokenize(const std::string &str) {
        std::string buf{};
        std::vector<Token> tokens;

        for (int i = 0; i < str.length(); i++) {
            char c = str.at(i);
            if (std::isalpha(c)) {
                do {
                    buf.push_back(str.at(i));
                    i++;
                } while (std::isalnum(str.at(i)));
                i--;

                if (buf == "exit") {
                    tokens.push_back({.type = TokenType::exit});
                    buf.clear();
                } else {
                    std::cerr << "You messed up!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else if (std::isdigit(c)) {
                do {
                    buf.push_back(str.at(i));
                    i++;
                } while (std::isalnum(str.at(i)));
                i--;
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
            } else if (c == ';')
                tokens.push_back({.type = TokenType::semi});
            else if (std::isspace(c))
                continue;
            else {
                std::cerr << "You messed up!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        return tokens;
    }
};