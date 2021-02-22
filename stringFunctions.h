#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H

#define expressionLength 100
#define nameOfVariable 15
#define countOfAvailableFunctions 11

static char* availableFunctions[countOfAvailableFunctions] = {       "sin",  "cos",  "tan",  "arctg", "log",  "lg",   "ln",   "sqrt", "pow",  "abs", "exp"};  // "-"
static char* availableFunctionsSymbols[countOfAvailableFunctions] ={ "!",    "@",    "#",    "№",     "$",    "%",    "&",    "?",    "_",    ":",   "\\"}; // "~"


void strclear(char str[]);

void strReplace(char* string, char what[], char forWhat[], int sizeOfString);

void addSpaces(char* expression);

void delSpaces(char* expression);

void strPrepare(char* expression);

#endif //STRINGFUNCTIONS_H