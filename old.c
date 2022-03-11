
do {
  int currentState = 0;
  // int nextState;
  int currentChar, nextChar;
  instance = "";

  while (currentState < 101) {
    currentChar = (int)buf[bufIndex++];
    nextChar = (int)buf[bufIndex];

    if (currentChar == '\n') lineNumber++;

    //skip through any comments
    if (currentChar == '#' && nextChar == '#') { //if comment opened...
      bufIndex++; //increment buffer index
      int linesSkipped = 0;

      //until comment closed...
      while (1) {
        if (currentChar == '\n') {
          lineNumber++;
          linesSkipped++;
        };
        if (currentChar == EOF) {
          printf("SCANNER ERROR: Line %d: Comment opened but not closed\n",
            lineNumber - linesSkipped);
          exit(1);
        }

        currentChar = buf[bufIndex++];
        nextChar = buf[bufIndex];

        if (currentChar == '#' && nextChar == '#') {
          currentChar = buf[++bufIndex];
          nextChar = buf[++bufIndex];
          break;
        }
      }
    }

    if (currentState == 24) {
      currentState = 124;
      break;
    }
    currentState = fsaTable[currentState][getColumn(currentChar,
      lineNumber)];

    // if (currentState < 101) {
    //   instance = addCharToString(instance, buf[bufIndex - 1]);
    // }

    // printf("%d (%d): line %d, column %d\n", currentChar, nextChar,
    //   lineNumber, getColumn(currentChar, lineNumber));

  }

  printf("%d\n", currentState);

  // if (currentState != 103 && currentState != 104 && currentState != 105 &&
  //   currentState != 106 && currentState != 108 && currentChar != EOF) {
  //   bufIndex--;
  //   printf("%d\n", currentChar);
  // }
  bufIndex--;
  // printf("%s\n", instance);

//   // if (nextChar != '#' && currentChar != EOF) {
//   //   nextState = fsaTable[currentState][getColumn(nextChar,
//   //     currentLineNumber)];
//   // } else if (currentChar != EOF) {
//   //   if (buf[bufIndex + 1] != '#') {
//   //     printf("SCANNER ERROR: Line %d: Unrecognized character \"%c\"\n",
//   //       currentLineNumber, nextChar);
//   //     exit(1);
//   //   }
//   // }

  // tk = scanner(instance, lineNumber);
} while (tk.tkId != EOF_TK);