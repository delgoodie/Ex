#include "Lexer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string.h>

#include "../CompilerCore.h"

static const int NUM_PRES = 6;

static const char PREPROCESSORS[NUM_PRES] = {
    '{', // open hard expr
    '}', // close hard expr
    '(', // open soft expr
    ')', // close soft expr
    '[', // open set expr
    ']'  // close set expr
};

static bool isPreprocessor(char c)
{
    for (int i = 0; i < NUM_PRES; i++)
        if (c == PREPROCESSORS[i])
            return true;
    return false;
}

static std::string FileToString(const std::string& filename)
{
    std::ifstream code(filename);
    std::stringstream ss;
    if (code.is_open())
    {
        std::string line;
        while (std::getline(code, line))
        {
            for (int i = 0; i < line.length(); i++)
                if (line[i] != ' ' && line[i] != '\t')
                    ss << line[i];
            ss << '\n';
        }
        code.close();
        return ss.str();
    }
    else
    {
        return "";
    }
}


namespace Compiler
{
	static bool IsOperator(const char* string)
	{
		for (int i = 0; i < NUM_OPS; i++)
			if (strlen(Operator::STR[i]) == strlen(string)) {
				bool f = true;
				for (int j = 0; j < strlen(string); j++)
					if (Operator::STR[i][j] != string[j]) f = false;
				if (f) return true;
			}
		return false;
	}


    std::vector<Token_Comp> Lex(const char* code)
    {
        std::vector<Token_Comp> tokens;

        int code_length = strlen(code), lineNumber = 0, i = 0;
        bool varFlag = false;
        while (i < code_length)
        {
            if (code[i] == '\n') // New Line
            {
                lineNumber++;
                i++;
            }
			else if (code[i] == ' ' || code[i] == '\t') // Whitespace
			{
				varFlag = false;
				i++;
			}
            else if (code[i] == '\'' || code[i] == '\"') // String
            {
                varFlag = false;
                int j = i;
                std::string str = "";
                while (j++ < code_length && code[j] != code[i])
                {
                    if (code[j] == '\\')
                    {
                        // TODO: handle espace characters
                        j++;
                    }
                    else
                        str.push_back(code[j]);
                }
                tokens.emplace_back(Token_Comp::Type::STR, str, lineNumber);
                i = j + 1;
            }
            else if (code[i] < 58 && code[i] > 47) // Number
            {
                std::string number;
                int j = i;
                while (j < code_length && code[j] < 58 && code[j] > 47)
                    number += code[j++];
                i = j;
                tokens.emplace_back(Token_Comp::Type::NUM, number, lineNumber);
            }
            else if (code[i] == '/' && i != code_length - 1 && code[i + 1] == '/') // Single Line Comment
            {
                varFlag = false;
                int j = i + 2;
                while (code[j] != '\n')
                    j++;
                i = j;
            }
            else if (code[i] == '/' && i != code_length - 1 && code[i + 1] == '*') // Multi Line Comment
            {
                varFlag = false;
                int j = i + 2;
                while (j < code_length - 1 && !(code[j] == '*' && code[j + 1] == '/'))
                    j++;
                i = j + 2;
            }
            else if (isPreprocessor(code[i])) // Preprocessor
            {
                std::string pre(1, code[i]);
                tokens.emplace_back(Token_Comp::Type::PRE, pre, lineNumber);
                varFlag = false;
                i++;
            }
            else // Operators & Variables
            {
                bool found = false;
                // Check for operator
                for (int j = 4; j > 0; j--)
                {
                    if (i + j - 1 < code_length)
                    {
						char op_buf[5];
						memcpy(op_buf, &code[i], j);
						op_buf[j] = '\0';
                        if (IsOperator(op_buf))
                        {
                            tokens.emplace_back(Token_Comp::Type::OP, std::string(op_buf), lineNumber);
                            varFlag = false;
                            found = true;
                            i += j;
                            break;
                        }
                    }
                }

                // Default to variable
                if (!found)
                {
                    if (!varFlag)
                        tokens.emplace_back(Token_Comp::Type::VAR, "", lineNumber);
                    varFlag = true;
                    tokens.back().value.push_back(code[i]);
                    i++;
                }
            }
        }
        return tokens;
    }

    namespace Debug
    {
        void PrintTokens(const std::vector<Token_Comp>& tokens)
        {
            std::printf("Printing Tokens List:\n");
            for (int i = 0; i < tokens.size(); i++)
            {
                char begin, end;
                switch (tokens[i].type)
                {
                case Token_Comp::Type::NUM:
                    begin = '(';
                    end = ')';
                    break;
                case Token_Comp::Type::STR:
                    begin = '\'';
                    end = '\'';
                    break;
                case Token_Comp::Type::OP:
                    begin = '[';
                    end = ']';
                    break;
                case Token_Comp::Type::VAR:
                    begin = '`';
                    end = '`';
                    break;
                case Token_Comp::Type::PRE:
                    begin = '_';
                    end = '_';
                    break;
                }
                std::printf(" %c%s%c ", begin, tokens[i].value.c_str(), end);
            }
            std::printf("\n\n");
        }
    }
}
