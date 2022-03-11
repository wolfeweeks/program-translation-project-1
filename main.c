#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "scanner.h"

#define SIZE 1000

char* tokenNames[] = {
  "Identifier",
  "Start Keyword",
  "Repeat Keyword",
  "Until Keyword",
  "Whole Keyword",
  "Label Keyword",
  "Quit Keyword",
  "Listen Keyword",
  "Yell Keyword",
  "Main Keyword",
  "Portal Keyword",
  "If Keyword",
  "Then Keyword",
  "Pick Keyword",
  "Declare Keyword",
  "Assign Keyword",
  "Proc Keyword",
  "= Operator",
  "<= Operator",
  ">= Operator",
  "== Operator",
  "!= Operator",
  ": Operator",
  ":= Operator",
  "+ Operator",
  "- Operator",
  "* Operator",
  "/ Operator",
  "% Operator",
  ". Delimiter",
  "( Delimiter",
  ") Delimiter",
  ", Delimiter",
  "{ Delimiter",
  "} Delimiter",
  "; Delimiter",
  "[ Delimiter",
  "] Delimiter",
  "Number",
  "End of File",
};

int main(int argc, char* argv[]) {
  if (argc != 2) // if incorrect number of args entered
  {
    printf("Error: Incorrect invocation\n");
    printf("\tUsage: ./scanner file\n");
    exit(1);
  } else {
    char* fileName = argv[1];

    printf("%s\n", fileName);
    // open file
    FILE* file = NULL;
    file = fopen(fileName, "r");
    if (file) // if file exists...
    {
      // check if file is empty, and exit if it is
      fseek(file, 0, SEEK_END);
      long size = ftell(file);
      if (size == 0) {
        printf("File is empty.\n");
        exit(1);
      }

      rewind(file); // if file isn't empty, rewind the file reading index

      Token tk;
      int lineNumber = 1;
      char* instance = "";

      //************************************************************************

      do {
        tk = scanner(file, lineNumber);
        printf("Token: %s | Instance: %s\n", tokenNames[tk.tkId], tk.tkInstance);
        sleep(2);
      } while (tk.tkId != EOF_TK);

      fclose(file);
    } else {
      printf("Error: File doesn't exist\n");
      exit(1);
    }
  }

  return 0;
}