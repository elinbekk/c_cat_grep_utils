#include "dynamic_memory_functions.h"

GrepConfig *initGrepConfig() {
  GrepConfig *grepConfig = (GrepConfig *)calloc(1, sizeof(GrepConfig));
  PatternArray *patternArray = (PatternArray *)calloc(1, sizeof(PatternArray));
  Flags *flags = (Flags *)calloc(1, sizeof(Flags));

  grepConfig->fileStartIndex = 0;

  patternArray->patterns = (char **)calloc(INIT_COUNT, sizeof(char *));
  patternArray->count = 0;
  patternArray->allocatedMemory = 0;

  if (patternArray->patterns) {
    patternArray->allocatedMemory = INIT_COUNT;
  } else {
    fprintf(stderr, "memory allocation error!\n");
  }
  grepConfig->patternArray = patternArray;
  grepConfig->flags = flags;
  return grepConfig;
}

void destroyGrepConfig(GrepConfig *grepConfig) {
  for (int i = 0; i < grepConfig->patternArray->allocatedMemory; ++i)
    free(grepConfig->patternArray->patterns[i]);
  free(grepConfig->patternArray->patterns);
  free(grepConfig->patternArray);
  free(grepConfig->flags);
  free(grepConfig);
}

void reallocPatternArray(PatternArray *patternArray) {
  char **reservePatterns = NULL;
  reservePatterns =
      realloc(patternArray->patterns,
              (patternArray->allocatedMemory + APPEND_COUNT) * sizeof(char *));
  if (reservePatterns) {
    for (int i = patternArray->allocatedMemory;
         i < patternArray->allocatedMemory + APPEND_COUNT; ++i)
      reservePatterns[i] = 0;
    patternArray->patterns = reservePatterns;
    patternArray->allocatedMemory =
        patternArray->allocatedMemory + APPEND_COUNT;
  } else {
    fprintf(stderr, "memory reallocation error!\n");
  }
}

void push(PatternArray *patternArray, char *pattern) {
  if (strcmp(pattern, "\0") == 0) {
    pattern = ".";
  }
  size_t length = strlen(pattern);
  char *tempString = calloc(length, sizeof(char) + 1);
  strncpy(tempString, pattern, length);

  if (patternArray->count >= patternArray->allocatedMemory)
    reallocPatternArray(patternArray);
  patternArray->patterns[patternArray->count] = tempString;
  patternArray->count++;
}

int getPatternsFromFile(GrepConfig *grepConfig, char *fileName) {
  int errorCode = ErrorCode_noError;
  FILE *filePtr = fopen(fileName, "r");
  if (filePtr == NULL) {
    errorCode = ErrorCode_failOpenPatternFile;
  } else {
    char *buffer = NULL;
    do {
      char line[MAX_SIZE] = {'\0'};
      buffer = fgets(line, MAX_SIZE - 1, filePtr);
      if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
      }
      if (buffer) {
        push(grepConfig->patternArray, line);
      }
    } while (buffer);
    fclose(filePtr);
  }
  return errorCode;
}
