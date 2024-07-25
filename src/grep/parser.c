#include "parser.h"

const struct option grepLongOptions[] = {
    {"regexp", required_argument, 0, 'e'},
    {"ignore-case", no_argument, 0, 'i'},
    {"invert-match", no_argument, 0, 'v'},
    {"count", no_argument, 0, 'c'},
    {"files-with-matches", no_argument, 0, 'l'},
    {"line-number", no_argument, 0, 'n'},
    {"no-filename", no_argument, 0, 'h'},
    {"no-messages", no_argument, 0, 's'},
    {"file", required_argument, 0, 'f'},
    {"only-matching", no_argument, 0, 'o'},
    {NULL, 0, NULL, 0}};

int parseFlags(int argc, char *argv[], GrepConfig *grepConfig) {
  Flags *flags = grepConfig->flags;
  ErrorCode errorCode = ErrorCode_noError;

  int currentFlag = 0;
  int index = 0;

  flags->compileFlag = REG_EXTENDED;

  while ((currentFlag = getopt_long(argc, argv, "e:ivclnhsf:o", grepLongOptions,
                                    NULL)) != -1 &&
         !errorCode) {
    index++;
    if (currentFlag == 'e') {
      flags->regexp = true;
      push(grepConfig->patternArray, optarg);
    } else if (currentFlag == 'i') {
      flags->ignoreCase = true;
      flags->compileFlag |= REG_ICASE;
    } else if (currentFlag == 'v') {
      flags->invertMatch = true;
    } else if (currentFlag == 'c') {
      flags->countOfMatching = true;
    } else if (currentFlag == 'l') {
      flags->matchingFiles = true;
    } else if (currentFlag == 'n') {
      flags->numberMatchingLines = true;
    } else if (currentFlag == 'h') {
      flags->matchingWithoutFileName = true;
    } else if (currentFlag == 's') {
      flags->suppressErrorMessages = true;
    } else if (currentFlag == 'f') {
      flags->regexesFromFiles = true;
      errorCode = getPatternsFromFile(grepConfig, optarg);
    } else if (currentFlag == 'o') {
      flags->printOnlyMatchedParts = true;
    } else {
      errorCode = ErrorCode_unknownFlag;
    }
  }
  if (flags->ignoreCase) {
    flags->compileFlag |= REG_ICASE;
  }

  return errorCode;
}