#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifndef COLOR_H
#define COLOR_H

#define NOBOLD 0
#define BOLD 1

// Reset all colors (foreground, background and bold)
#define COLOR_NORMAL "\e[m"

// Bold text
#define COLOR_BOLD "\e[1m"

// Font colors
#define COLOR_BLACK "\e[30m"
#define COLOR_RED "\e[31m"
#define COLOR_GREEN "\e[32m"
#define COLOR_YELLOW "\e[33m"
#define COLOR_BLUE "\e[34m"
#define COLOR_MAGENTA "\e[35m"
#define COLOR_CYAN "\e[36m"
#define COLOR_WHITE "\e[37m"

// Background colors
#define COLOR_BG_BLACK "\e[40m"
#define COLOR_BG_RED "\e[41m"
#define COLOR_BG_GREEN "\e[42m"
#define COLOR_BG_YELLOW "\e[43m"
#define COLOR_BG_BLUE "\e[44m"
#define COLOR_BG_MAGENTA "\e[45m"
#define COLOR_BG_CYAN "\e[46m"
#define COLOR_BG_WHITE "\e[47m"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Available colors.
 * http://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
typedef enum {
  NORMAL = -1,
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
} color_t;

/*
 * Write a colord text to stdout.
 * @param fontcolor The font color. Use NORMAL to use default color.
 * @param bgcolor The background color. Use NORMAL to use default background color.
 * @param bold An non-zero value to change the text to bold, 0 otherwise.
 * @param format Output format.
 * @return The number of characters printed (including the colors caracters and excluding the null byte used to end output to strings.
 * See the printf(3) manpage for more information.
 */
int cprintf(color_t fontcolor, color_t bgcolor, int bold, const char* format, ...);

/*
 * Write a colord text to the stream.
 * @param stream The stream.
 * @param fontcolor The font color. Use NORMAL to use default color.
 * @param bgcolor The background color. Use NORMAL to use default background color.
 * @param bold An non-zero value to change the text to bold, 0 otherwise.
 * @param format Output format.
 * @return The number of characters printed (including the colors caracters and excluding the null byte used to end output to strings.
 * See the printf(3) manpage for more information.
 */
int cfprintf(FILE* stream, color_t fontcolor, color_t bgcolor, int bold, const char* format, ...);

#ifdef __cplusplus
}
#endif

static char* getcolor(color_t c, int bgcolor) {
  int size = 6 * sizeof(char);
  char* str = malloc(size);
  memset(str, 0, size);
  if (c != NORMAL)
    snprintf(str, size, (bgcolor ? "\e[4%dm" : "\e[3%dm"), (int)c);
  return str;
}

static int cprintstream(color_t fontcolor, color_t bgcolor, int bold, FILE* stream, const char* format, va_list ap) {
  char *strcolor, *strbgcolor;
  int nbcharprinted;
  // Set (= print) colors. If the color is NORMAL, an empty string is printed.
  strcolor = getcolor(fontcolor, 0); // Get font color
  strbgcolor = getcolor(bgcolor, 1); // Get background color
  fprintf(stream, "%s%s", strcolor, strbgcolor);
  free(strcolor);
  free(strbgcolor);
  if (bold)
    printf(COLOR_BOLD);
  // Print string
  nbcharprinted = vfprintf(stream, format, ap);
  // Reset colors
  printf(COLOR_NORMAL);
  return nbcharprinted;
}

/*
 * cprintf does not call cfprintf because you cannot pass a variable number of argument.
 * So it invokes cprintstream which has a va_list argument.
 */
int cprintf(color_t fontcolor, color_t bgcolor, int bold, const char* format, ...) {
  va_list arglist;
  int nbcharprinted;
  va_start(arglist, format);
  nbcharprinted = cprintstream(fontcolor, bgcolor, bold, stdout, format, arglist);
  va_end(arglist);
  return nbcharprinted;
}

int cfprintf(FILE* stream, color_t fontcolor, color_t bgcolor, int bold, const char* format, ...) {
  va_list arglist;
  int nbcharprinted;
  va_start(arglist, format);
  nbcharprinted = cprintstream(fontcolor, bgcolor, bold, stream, format, arglist);
  va_end(arglist);
  return nbcharprinted;
}

#endif // COLOR_H