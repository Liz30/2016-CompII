#include <iostream>
#include <string>

using namespace std;

typedef struct TokenInfo TokenInfo;

enum Type{
  INT,
  STRING
};

struct TokenInfo {
  int value;
  string lexem;
  Type type;
};
