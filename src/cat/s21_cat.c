#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define S21_DEFAULT_SHIFT_ASCII_VALUE 64
#define S21_DEL_ASCII_VALUE 127

typedef struct {
  bool numberNonBlank;
  bool showEndSymbols;
  bool showNonPrinting;
  bool numberLines;
  bool squeezeBlank;
  bool showTab;
} Flags;

int getFlag(int argc, char *argv[], Flags *fl) {
  int isFlagExist = 1;
  struct option longOpts[] = {{"number-nonblank", no_argument, NULL, 'b'},
                              {"number", no_argument, NULL, 'n'},
                              {"squeeze-blank", no_argument, NULL, 's'},
                              {NULL, no_argument, NULL, 0}};
  int current = getopt_long(argc, argv, "+bevEnstT", longOpts, NULL);
  for (; current != -1;
       current = getopt_long(argc, argv, "+bevEnstT", longOpts, NULL)) {
    if (current == 'b') {
      fl->numberNonBlank = true;
      fl->numberLines = false;
    } else if (current == 'e') {
      fl->showEndSymbols = true;
      fl->showNonPrinting = true;
    } else if (current == 'v') {
      fl->showNonPrinting = true;
    } else if (current == 'E') {
      fl->showEndSymbols = true;
    } else if (current == 'n') {
      fl->numberLines = true;
    } else if (current == 's') {
      fl->squeezeBlank = true;
    } else if (current == 't') {
      fl->showTab = true;
      fl->showNonPrinting = true;
    } else if (current == 'T') {
      fl->showTab = true;
    } else {
      isFlagExist = 0;
    }
  }
  return isFlagExist;
}

bool isMeta(int char_code) { return (signed char)char_code < 0; }

void catNumberLines(int *lineNumber) { printf("%6i\t", ++(*lineNumber)); }

void catShowEndSymbols() { printf("$"); }

int catNonPrinting(int symbol) {
  int shift = S21_DEFAULT_SHIFT_ASCII_VALUE;
  if (iscntrl(symbol) && symbol != '\n' && symbol != '\t') {
    printf("^");
    if (symbol == S21_DEL_ASCII_VALUE) {
      symbol -= shift;
    } else {
      symbol += shift;
    }
  }
  return symbol;
}

int catTab(int *char_code) {
  *char_code = 'I';
  return *char_code;
}

int handleSqueezeBlank(char symbol, int *pNewLineCount) {
  int skipPrintFlag = 0;
  if (symbol == '\n') {
    (*pNewLineCount)++;
  } else {
    (*pNewLineCount) = 0;
  }
  if ((*pNewLineCount) > 1) {
    skipPrintFlag = 1;
  }
  return skipPrintFlag;
}

void readFile(FILE *file, Flags *fl) {
  int symbol = 0;
  int lineNumber = 0;
  int lineEnd = '\n';
  int newLineCount = 0;
  while ((fread(&symbol, 1, 1, file)) > 0) {
    if (lineEnd == '\n') {
      if (fl->squeezeBlank) {
        int skipPrintFlag = handleSqueezeBlank(symbol, &newLineCount);
        if (skipPrintFlag) {
          continue;
        }
      }
      if (fl->numberNonBlank) {
        if (symbol != '\n') {
          catNumberLines(&lineNumber);
        }
      } else if (fl->numberLines) {
        catNumberLines(&lineNumber);
      }
    }
    if (fl->showEndSymbols && symbol == '\n') {
      catShowEndSymbols();
    }
    if (fl->showNonPrinting) {
      symbol = catNonPrinting(symbol);
    }
    if (fl->showTab) {
      if (symbol == '\t') {
        printf("^");
        catTab(&symbol);
      }
    }
    printf("%c", symbol);
    lineEnd = symbol;
  }
}

int catFile(char *argv[], Flags *fl) {
  FILE *file;
  file = fopen(argv[optind], "r");
  int fileExist = 0;
  if (file != NULL) {
    fileExist = 1;
    readFile(file, fl);
    fclose(file);
  }
  return fileExist;
}

int main(int argc, char *argv[]) {
  Flags fl = {false, false, false, false, false, false};
  int error = getFlag(argc, argv, &fl);
  while (optind < argc && error) {
    error = catFile(argv, &fl);
    optind++;
  }
  if (error == 0) {
    fprintf(stderr, "./s21_cat: No such file or flag\n");
  }
}
