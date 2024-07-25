#ifndef DYNAMIC_MEMORY_FUNCTIONS_H
#define DYNAMIC_MEMORY_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "structs.h"

GrepConfig *initGrepConfig();
void destroyGrepConfig(GrepConfig *grepConfig);
void reallocPatternArray(PatternArray *patternArray);
void push(PatternArray *patternArray, char *pattern);
int getPatternsFromFile(GrepConfig *grepConfig, char *fileName);

#endif