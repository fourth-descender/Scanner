#include "scanner.hpp"

#define entry(identifier, keyword) \
    {identifier, token(#keyword, identifier)}

#define map(name) \
    const std::unordered_map<std::string, token> name

map(r_tokens) {
    entry("int", INT), entry("main", MAIN), entry("void", VOID), 
    entry("break", BREAK), entry("do", DO), entry("else", ELSE),
    entry("if", IF), entry("while", WHILE), entry("return", RETURN), 
    entry("scanf", READ), entry("printf", WRITE)
};

map(s_tokens) {
    entry("{", LBRACE), entry("}", RBRACE), entry("[", LSQUARE),
    entry("]", RSQUARE), entry("(", LPAR), entry(")", RPAR),
    entry(";", SEMI), entry("+", PLUS), entry("-", MINUS),
    entry("*", MUL_OP), entry("/", DIV_OP), entry("&", AND_OP),
    entry("|", OR_OP), entry("!", NOT_OP), entry("=", ASSIGN),
    entry("<", LT), entry(">", GT), entry("<<", SHL_OP), 
    entry(">>", SHR_OP), entry("==", EQ), entry("!=", NOTEQ), 
    entry("<=", LTEQ), entry(">=", GTEQ), entry("&&", ANDAND),
    entry("||", OROR), entry(",", COMMA)
};

scanner::~scanner() {
    text.close();
    output.close();
};

scanner::scanner(std::string file_path, std::string output_name)
    : text(file_path, std::ios::in) {
    output.open("results/" + output_name);
};

state scanner::scan(char ch) {
    return std::isdigit(ch) ? INT_NUM : ID;
};

void scanner::clear() {
    buffer = "";
};

void scanner::write() {
    for (auto token : tokens) {
        output << "Token: " << token.get_type() << std::endl;
    };
};

bool scanner::is_reserved(std::string s) const {
    return r_tokens.find(s) != r_tokens.end();
};

bool scanner::is_special(std::string s) const {
    return s_tokens.find(s) != s_tokens.end();
};

void scanner::scan() {
    // for handling eof.
    char ch, tail;
    state type;
    while (!text.eof()) {
        text >> std::noskipws >> ch;
        tail = text.peek();

        // skips if empty.
        if (ch == ' ' || ch == '\n') {
            continue;
        };

        switch (scan(ch)) {
            case ID: {
                // terminating state -> reserved word.
                if (is_reserved(buffer + ch) && (tail == ' ' || tail == '\n' || tail == EOF)) {
                    buffer += ch;
                    save();
                    break;
                };

                #define str(character) std::string(1, character)
                if (is_special(str(ch))) {
                    // sChar -> sCharTail.
                    // terminating state -> id.
                    if (is_special(str(ch) + tail)) {
                        save();
                        buffer += ch;
                        break;
                    };
                    // sChar -> INT_NUM and sChar -> sChar.
                    // second part of one special char.
                    if (is_special(buffer + ch)) {
                        buffer += ch;
                        // terminating state -> special.
                        save();
                        break;
                    };

                    // possible terminating state -> id on nonempty buffer.
                    save();
                    
                    // terminating state -> single length special.
                    buffer = ch;
                    save();
                    break;
                };

                // either alphabet -> alphabet / number.
                buffer += ch;
                break;
            };

            case INT_NUM: {
                buffer += ch;

                // breaking point for integers.
                // edge case number -> space or end of line.
                if (tail == ' ' || tail == '\n' || tail == EOF) {
                    save();
                };

                break;
            };
        };
    };
};

void scanner::save() {
    if (buffer.empty()) {
        return;
    };
    
    #define insert(type, value) \
        tokens.push_back(token(type, value)); \
        clear(); \
        return

    if (is_special(buffer)) {
        insert(s_tokens.at(buffer).get_type(), buffer);
    };

    if (is_reserved(buffer)) {
        insert(r_tokens.at(buffer).get_type(), buffer);
    };

    // non-numeric first character means token is ID.
    if (scan(buffer[0]) == ID) {
        insert("ID", buffer);
    }
    
    insert("INT_NUM", buffer);
};
