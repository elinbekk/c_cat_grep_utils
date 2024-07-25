#ifndef STRUCTS_H
#define STRUCTS_H

#include <getopt.h>
#include <stdbool.h>

typedef enum {
  ErrorCode_noError = 0,
  ErrorCode_unknownFlag = 1 << 0,
  ErrorCode_failOpenFile = 1 << 2,
  ErrorCode_failOpenPatternFile = 1 << 3,
  ErrorCode_failCompileRegularExpression = 1 << 4,
} ErrorCode;

typedef struct {
  char **patterns;
  int count;
  int allocatedMemory;
} PatternArray;

typedef struct {
  int compileFlag;
  bool regexp;
  bool ignoreCase;
  bool invertMatch;
  bool countOfMatching;
  bool matchingFiles;
  bool numberMatchingLines;
  bool matchingWithoutFileName;
  bool suppressErrorMessages;
  bool regexesFromFiles;
  bool printOnlyMatchedParts;
} Flags;

typedef struct {
  Flags *flags;
  PatternArray *patternArray;
  int fileStartIndex;
} GrepConfig;

#endif