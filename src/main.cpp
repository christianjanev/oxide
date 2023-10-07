#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

#include "tokenization.hpp"

std::string tokens_to_asm(const std::vector<Token> &tokens) {
    std::stringstream out;
    out << "global _start\n\n_start:\n";
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens.at(i).type == TokenType::exit) {
            if (i+ 1 < tokens.size() && tokens.at(i+1).type == TokenType::int_lit) {
                if (i + 2 < tokens.size() && tokens.at(i+2).type == TokenType::semi) {
                    out << "    mov rax, 60\n";
                    out << "    mov rdi, " << tokens.at(i+1).value.value() << "\n";
                    out << "    syscall";
                }
            }
        }
    }
    return out.str();
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "[Syntax] ./oxide [source file]" << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer;

    std::vector<Token> tokens = tokenizer.tokenize(contents);
    {
        std::fstream file("out.asm", std::ios::out);
        file << tokens_to_asm(tokens);
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}