# Simple Bash Utils

Development of Bash text utilities: cat, grep.

In this project I develop basic Bash utilities for working with C language text. 
These utilities (cat and grep) are commonly used in the Linux terminal. 


## Cat util
- Support of -b -e -n -s -t flags (including GNU versions)
- The source, header, and build files placed in the src/cat/ directory
- The resulting executable file must be placed in the directory src/cat/ and named s21_cat

`cat [OPTION] [FILE]...`

### cat options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $  |
| 3 | -n (GNU: --number) | number all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeeze multiple adjacent blank lines |
| 5 | -t implies -v (GNU: -T the same, but without implying -v) | but also display tabs as ^I  |

## Grep util

`grep [options] template [file_name]`

- Support of the following flags: `-e`, `-i`, `-v`, `-c`, `-l`, `-n`, `-h`, `-s`, `-f`, `-o`,
  including their _pair_ combinations (e.g. `-iv`, `-in`)
- <regex.h>  library  used for regular expressions
- The source, header and make files placed in the src/grep/ directory
- The resulting executable file placed in the directory src/grep/ and named s21_grep

### grep options

| No. | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | pattern |
| 2 | -i | Ignore uppercase vs. lowercase.  |
| 3 | -v | Invert match. |
| 4 | -c | Output count of matching lines only. |
| 5 | -l | Output matching files only.  |
| 6 | -n | Precede each matching line with a line number. |
| 7 | -h | Output matching lines without preceding them by file names. |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Take regexes from a file. |
| 10 | -o | Output the matched parts of a matching line. |





