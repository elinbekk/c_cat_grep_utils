#include <stdio.h>

#include "dynamic_memory_functions.h"
#include "parser.h"

int getNoMatchNumber(FILE *file, regex_t *pReg) {
  int length = LENGTH;
  char *line = malloc(length * sizeof(char));
  regmatch_t match;
  int count = 0;
  while (fgets(line, length - 1, file) != NULL) {
    if (regexec(pReg, line, 1, &match, 0)) {
      count++;
    }
  }
  free(line);
  return count;
}
void processCombinationLC(int count, char *filename, int fileCount) {
  if (count > 0 && fileCount > 1) {
    printf("%s:1\n%s\n", filename, filename);
  } else if (count > 0) {
    printf("1\n%s\n", filename);
  } else if (fileCount > 1) {
    printf("%s:0\n", filename);
  } else {
    printf("0\n");
  }
}

void printNoMatching(FILE *file, char *filename, regex_t *preg, int fileCount,
                     Flags *flags) {
  int length = LENGTH;
  regmatch_t match;
  char *line = malloc(length * sizeof(char));
  char last;
  int number = 0;
  if (flags->countOfMatching) {
    int count = getNoMatchNumber(file, preg);
    if (fileCount > 1) {
      printf("%s:", filename);
    }
    printf("%d\n", count);
  } else if (flags->matchingFiles) {
    printf("%s\n", filename);
  } else {
    while (fgets(line, length - 1, file) != NULL) {
      ++number;
      if (regexec(preg, line, 1, &match, 0)) {
        if (fileCount > 1 && !flags->matchingWithoutFileName) {
          printf("%s:", filename);
        }
        if (flags->numberMatchingLines) {
          printf("%d:", number);
        }
        printf("%s", line);
        last = line[strlen(line) - 1];
      }
    }
    if ((fileCount > 1 && regexec(preg, line, 1, &match, 0)) ||
        (fileCount == 1 && last != '\n')) {
      printf("\n");
    }
  }
  free(line);
}

void numberMatchLines(FILE *file, char *filename, regex_t *pReg, int fileCount,
                      Flags *flags) {
  int length = LENGTH;
  regmatch_t match;
  char *line = malloc(length * sizeof(char));
  int number = 0;
  char last;
  while (fgets(line, length - 1, file) != NULL) {
    ++number;
    if (!regexec(pReg, line, 1, &match, 0)) {
      if (fileCount > 1 && !flags->matchingWithoutFileName) {
        printf("%s:", filename);
      }
      printf("%d:%s", number, line);
      last = line[strlen(line) - 1];
    }
  }
  if ((fileCount > 1 && !regexec(pReg, line, 1, &match, 0)) ||
      (fileCount == 1 && last != '\n' && !regexec(pReg, line, 1, &match, 0))) {
    printf("\n");
  }
  free(line);
}

void getMatchCount(FILE *file, char *filename, regex_t *pReg, int fileCount,
                   Flags *flags) {
  int length = LENGTH;
  char *line = malloc(length * sizeof(char));
  regmatch_t match;
  int count = 0;
  while (fgets(line, length - 1, file) != NULL) {
    if (!regexec(pReg, line, 1, &match, 0)) {
      count++;
    }
  }
  if (!flags->matchingFiles) {
    if (fileCount == 1) {
      printf("%d\n", count);
    } else {
      printf("%s:%d\n", filename, count);
    }
  } else if (!flags->matchingWithoutFileName && !flags->matchingFiles) {
    printf("%d\n", count);
  } else if (flags->matchingFiles) {
    processCombinationLC(count, filename, fileCount);
  }
  free(line);
}

void printFileNames(FILE *file, char *filename, regex_t *pReg) {
  int length = LENGTH;
  char *line = malloc(length * sizeof(char));
  regmatch_t match;
  while (fgets(line, length - 1, file) != NULL) {
    if (!regexec(pReg, line, 1, &match, 0)) {
      printf("%s\n", filename);
      break;
    }
  }
  free(line);
}

void printOnlyMatching(FILE *file, char *filename, regex_t *pReg, int fileCount,
                       Flags *flags) {
  int length = LENGTH;
  char *line = malloc(length * sizeof(char));
  regmatch_t match = {0};
  int number = 0;
  while (fgets(line, length - 1, file) != NULL) {
    ++number;
    if (!regexec(pReg, line, 1, &match, 0)) {
      char *pLine = line + match.rm_eo;
      if (fileCount == 1) {
        if (flags->numberMatchingLines) {
          printf("%d:", number);
        }
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
               (line + match.rm_so));
      } else {
        if (!flags->matchingWithoutFileName) {
          printf("%s:", filename);
        }
        if (flags->numberMatchingLines) {
          printf("%d:", number);
        }
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
               (line + match.rm_so));
      }
      while (!regexec(pReg, pLine, 1, &match, 0)) {
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
               (pLine + match.rm_so));
        pLine += match.rm_eo;
      }
    }
  }
  free(line);
}

void printWithoutFilename(FILE *file, regex_t *pReg) {
  int length = LENGTH;
  regmatch_t match;
  char *line = malloc(length * sizeof(char));
  while (fgets(line, length - 1, file) != NULL) {
    if (!regexec(pReg, line, 1, &match, 0)) {
      printf("%s", line);
    }
  }
  free(line);
}

void printMatchingString(FILE *file, char *filename, regex_t *pReg,
                         int fileCount, Flags *flags) {
  int length = LENGTH;
  regmatch_t match;
  char *line = malloc(length * sizeof(char));
  char last;
  while (fgets(line, length - 1, file) != NULL) {
    if (!regexec(pReg, line, 1, &match, 0)) {
      if (fileCount > 1 && !flags->matchingWithoutFileName) {
        printf("%s:", filename);
      }
      printf("%s", line);
      last = line[strlen(line) - 1];
    }
  }
  if ((fileCount > 1 && !regexec(pReg, line, 1, &match, 0)) ||
      (fileCount == 1 && last != '\n')) {
    printf("\n");
  }
  free(line);
}

void processFile(FILE *file, char *filename, Flags *flags,
                 regex_t *regularExpression, int fileCount) {
  if (flags->invertMatch) {
    printNoMatching(file, filename, regularExpression, fileCount, flags);
  } else if (flags->countOfMatching) {
    getMatchCount(file, filename, regularExpression, fileCount, flags);
  } else if (flags->matchingFiles) {
    printFileNames(file, filename, regularExpression);
  } else if (flags->printOnlyMatchedParts) {
    printOnlyMatching(file, filename, regularExpression, fileCount, flags);
  } else if (flags->numberMatchingLines) {
    numberMatchLines(file, filename, regularExpression, fileCount, flags);
  } else if (flags->matchingWithoutFileName) {
    printWithoutFilename(file, regularExpression);
  } else {
    printMatchingString(file, filename, regularExpression, fileCount, flags);
  }
}

int compileRegularExpression(GrepConfig *grepConfig,
                             regex_t *regularExpression) {
  PatternArray *patternArray = grepConfig->patternArray;
  Flags *flags = grepConfig->flags;
  ErrorCode errorCode = ErrorCode_noError;
  int usedSpace = 0;
  char pattern[MAX_SIZE] = {'\0'};
  if (patternArray->count > 0) {
    strncat(pattern, patternArray->patterns[0], (MAX_SIZE - 1) - usedSpace);
    usedSpace += (int)strlen(patternArray->patterns[0]);
  }
  for (int i = 1; i < patternArray->count; ++i) {
    strncat(pattern, "|", (MAX_SIZE - 1) - usedSpace);
    usedSpace += (int)strlen("|");
    strncat(pattern, patternArray->patterns[i], (MAX_SIZE - 1) - usedSpace);
    usedSpace += (int)strlen(patternArray->patterns[i]);
  }
  int compileError = regcomp(regularExpression, pattern, flags->compileFlag);
  if (compileError) {
    errorCode = ErrorCode_failCompileRegularExpression;
  }
  return errorCode;
}

int getFileCount(PatternArray *patternArray, int argc, char *argv[]) {
  int fileCount = 0;
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "-f") == 0) {
      i++;
    } else if (*argv[i] == '-') {
    } else {
      fileCount++;
    }
  }
  if (patternArray->count == 0) {
    fileCount--;
  }
  return fileCount;
}

int getImplicitPattern(PatternArray *patternArray, int argc, char *argv[]) {
  int foundImplicitPatternFlag = 0;
  int foundIndex = -1;
  for (int i = 1; i < argc && !foundImplicitPatternFlag; ++i) {
    if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "-f") == 0) {
      ++i;
    } else if (*argv[i] == '-') {
    } else {
      push(patternArray, argv[i]);
      foundImplicitPatternFlag = 1;
      foundIndex = i;
    }
  }
  return foundIndex;
}

int grepFile(int argc, char *argv[], GrepConfig *grepConfig) {
  PatternArray *patternArray = grepConfig->patternArray;
  ErrorCode errorCode = ErrorCode_noError;
  Flags *flags = grepConfig->flags;
  int fileCount = 0;
  regex_t regularExpression = {0};
  int implicitPatternIndex = -1;
  fileCount = getFileCount(patternArray, argc, argv);

  if (patternArray->count == 0) {
    implicitPatternIndex = getImplicitPattern(patternArray, argc, argv);
  }
  errorCode = compileRegularExpression(grepConfig, &regularExpression);
  for (int i = 1; i < argc && !errorCode; ++i) {
    if (i == implicitPatternIndex) {
      continue;
    }
    if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "-f") == 0) {
      ++i;
    } else if (*argv[i] == '-') {
    } else {
      FILE *filePtr = fopen(argv[i], "r");
      if (filePtr != NULL) {
        processFile(filePtr, argv[i], flags, &regularExpression, fileCount);
        fclose(filePtr);
      } else if (!flags->suppressErrorMessages) {
        errorCode = ErrorCode_failOpenFile;
      }
      if (errorCode == ErrorCode_failOpenFile) {
        fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
      }
      errorCode = ErrorCode_noError;
    }
  }
  regfree(&regularExpression);
  return errorCode;
}

int main(int argc, char *argv[]) {
  GrepConfig *grepConfig = NULL;
  int errorCode = ErrorCode_noError;
  grepConfig = initGrepConfig();
  errorCode = parseFlags(argc, argv, grepConfig);
  if (!errorCode) {
    grepFile(argc, argv, grepConfig);
  }
  destroyGrepConfig(grepConfig);
}