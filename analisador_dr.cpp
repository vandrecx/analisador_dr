#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class LLParser {
private:
    string input;
    size_t index;

    char currentChar() {
        if (index < input.length()) {
            return input[index];
        }
        return '$'; // End of input
    }

    void match(char expected) {
        if (currentChar() == expected) {
            index++;
        } else {
            cout << "Erro: Esperado '" << expected << "', mas encontrado '" << currentChar() << "'" << endl;
            exit(1);
        }
    }

    void S() {
        CADEIA();
    }

    void CADEIA() {
        VAR();
        CONJUNTO();
    }

    void VAR() {
        if (currentChar() == 'v') {
            match('v');
        } else {
            cout << "Erro: Esperado 'v', mas encontrado '" << currentChar() << "'" << endl;
            exit(1);
        }
    }

    void CONJUNTO() {
        if (currentChar() == '[') {
            match('[');
            ÍNDICE();
            match(']');
        } else {
            cout << "Erro: Esperado '[', mas encontrado '" << currentChar() << "'" << endl;
            exit(1);
        }
    }

    void ÍNDICE() {
        if (isdigit(currentChar()) || currentChar() == 's') {
            ELEMENTO();
        } else if (currentChar() == ':') {
            ELEMENTO();
            match(':');
            ELEMENTO();
        } else {
            cout << "Erro: Esperado ELEMENTO ou ':', mas encontrado '" << currentChar() << "'" << endl;
            exit(1);
        }
    }

    void ELEMENTO() {
        if (isdigit(currentChar())) {
            NÚMERO();
        } else if (currentChar() == 's') {
            STRING();
        } else {
            cout << "Erro: Esperado NÚMERO ou STRING, mas encontrado '" << currentChar() << "'" << endl;
            exit(1);
        }
    }

    void NÚMERO() {
        if (currentChar() == 'p' || currentChar() == 'n') {
            match(currentChar());
        } else {
            cout << "Erro: Esperado 'p' ou 'n', mas encontrado '" << currentChar() << "'" << endl;
            exit(1);
        }
    }

    void STRING() {
        if (currentChar() == 's') {
            match('s');
        } else {
            cout << "Erro: Esperado 's', mas encontrado '" << currentChar() << "'" << endl;
            exit(1);
        }
    }

public:
    LLParser(const string& inputStr) : input(inputStr), index(0) {}

    void parse() {
        S();
        if (currentChar() == '$') {
            cout << "Análise bem-sucedida!" << endl;
        } else {
            cout << "Erro: Entrada extra após fim de análise!" << endl;
        }
    }
};

int main() {
    string input;
    cout << "Digite a cadeia para análise: ";
    cin >> input;

    LLParser parser(input);
    parser.parse();

    return 0;
}
