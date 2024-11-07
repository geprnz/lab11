#include "Functions.h"

bool isDigit(const string& str) {
    return str.find_first_not_of("0123456789") == string::npos;
}

bool isOperator(const string& str) {
    return str.find_first_not_of("-+*/") == string::npos;
}

