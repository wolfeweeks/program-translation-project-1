#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "token.h"

int fsaTable[25][25] = {
  //ws low   _  up num   =   <   >   !   :   +   -   *   /   %   .   (   )   ,   {   }   ;   [   ] eof
  {  0,  1,  1,999, 23,  2,  3,  4,  6,  7,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24}, //0 start
  {101,  1,101,  1,  1,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101}, //1 id
  {102,102,102,102,102,  5,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102}, //2 =
  {999,999,999,999,999,103,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999}, //3 <=
  {999,999,999,999,999,104,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999}, //4 >=
  {105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105}, //5 ==
  {999,999,999,999,999,106,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999}, //6 !=
  {107,107,107,107,107,  8,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107}, //7 :
  {108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108}, //8 :=
  {109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109}, //9 +
  {110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110}, //10 -
  {111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111}, //11 *
  {112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112}, //12 /
  {113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113}, //13 %
  {114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114}, //14 .
  {115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115}, //15 (
  {116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116}, //16 )
  {117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117}, //17 ,
  {118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118}, //18 {
  {119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119}, //19 }
  {120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120}, //20 ;
  {121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121}, //21 [
  {122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122}, //22 ]
  {123,123,123,123, 23,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123}, //23 number
  {124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124}, //24 eof
};

int getColumn(char c) {
  if (c == '\t' || c == ' ' || c == '\n') return 0;
  if (c >= 65 && c <= 90) return 3;
  if (c >= 97 && c <= 122) return 1;
  if (c == '_') return 2;
  if (c >= 48 && c <= 57) return 4;
  if (c == '=') return 5;
  if (c == '<') return 6;
  if (c == '>') return 7;
  if (c == '!') return 8;
  if (c == ':') return 9;
  if (c == '+') return 10;
  if (c == '-') return 11;
  if (c == '*') return 12;
  if (c == '/') return 13;
  if (c == '%') return 14;
  if (c == '.') return 15;
  if (c == '(') return 16;
  if (c == ')') return 17;
  if (c == ',') return 18;
  if (c == '{') return 19;
  if (c == '}') return 20;
  if (c == ';') return 21;
  if (c == '[') return 22;
  if (c == ']') return 23;
  if (c == EOF) return 24;

  printf("SCANNER ERROR: Unrecognized character \"%c\"\n", c);
  exit(1);
}

char* addCharToString(char* string, char c) {
  char* newString = (char*)malloc(sizeof(char) * (2 + strlen(string)));
  memcpy(newString, string, strlen(string) + 1);
  newString[strlen(string)] = c;
  newString[strlen(string) + 1] = '\0';
  return newString;
}

tokenId getTokenId(int state, char* instance) {
  if (state == 101) return IDENT_TK;
  if (state == 102) return ONE_EQUALS_TK;
  if (state == 103) return LESS_THAN_EQUALS_TK;
  if (state == 104) return GREAT_THAN_EQUALS_TK;
  if (state == 105) return TWO_EQUALS_TK;
  if (state == 106) return NOT_EQUALS_TK;
  if (state == 107) return COLON_TK;
  if (state == 108) return COLON_EQUALS_TK;
  if (state == 109) return PLUS_TK;
  if (state == 110) return MINUS_TK;
  if (state == 111) return TIMES_TK;
  if (state == 112) return DIVIDE_TK;
  if (state == 113) return MODULO_TK;
  if (state == 114) return DOT_TK;
  if (state == 115) return LEFT_PAREN_TK;
  if (state == 116) return RIGHT_PAREN_TK;
  if (state == 117) return COMMA_TK;
  if (state == 118) return LEFT_CURL_TK;
  if (state == 119) return RIGHT_CURL_TK;
  if (state == 120) return SEMI_TK;
  if (state == 121) return LEFT_BRACKET_TK;
  if (state == 122) return RIGHT_BRACKET_TK;
  if (state == 123) return NUM_TK;
  if (state == 124) return EOF_TK;

  if (state == 999) {
    printf("SCANNER ERROR: Invalid Token: %s\n", instance);
    exit(1);
  }
}

Token scanner(FILE* file, int lineNo) {
  int currentState = 0;
  int nextState = 0;
  int currentChar;
  int nextChar;
  char* instance = "";

  while (currentState < 101) {
    currentChar = fgetc(file);
    nextChar = fgetc(file);
    if (nextChar != EOF) {
      fseek(file, -1, SEEK_CUR);
    }

    //skip through any comments
    if (currentChar == '#' && nextChar == '#') { //if comment opened...
      int commentClosed = 0;
      fgetc(file);

      //until comment closed...
      while (1) {
        if (currentChar == EOF) {
          printf("SCANNER ERROR: Comment opened but not closed\n");
          exit(1);
        }

        currentChar = fgetc(file);
        nextChar = fgetc(file);

        if (nextChar != EOF) {
          fseek(file, -1, SEEK_CUR);
        }

        if (currentChar == '#' && nextChar == '#') {
          fgetc(file);
          currentChar = fgetc(file);
          nextChar = fgetc(file);
          if (nextChar != EOF) {
            fseek(file, -1, SEEK_CUR);
          }
          commentClosed = 1;
          break;
        }
      }

    }

    currentState = fsaTable[currentState][getColumn(currentChar)];

    if (nextChar != '#' && currentState < 101) {
      nextState = fsaTable[currentState][getColumn(nextChar)];
    }

    if (currentState != 0 && currentState < 101) {
      instance = addCharToString(instance, currentChar);
      if (nextState == 103 || nextState == 104) {
        instance = addCharToString(instance, nextChar);
      }
    }

    if (currentState == 105 || currentState == 108) fseek(file, -1, SEEK_CUR);

  }

  tokenId tkId = getTokenId(currentState, instance);

  Token tk = { tkId, instance };
  return tk;
}