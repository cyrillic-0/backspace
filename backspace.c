#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*str_predicate)(const char * s, const char c, size_t i);

int total(const char * s, const char c, size_t i) {
  if (s[i] == c) return -1; else return 1;
}

int not_equal(const char * s, const char c, size_t i __attribute__((unused))) {
  return *s != c;
}

size_t strcount(const char * s, const char c, str_predicate pred) {
  for (int i = 0, ret = 0; ; i++) {
    if (!s[i]) return ret;
    ret += pred(s, c, i);
  }
}

char * strpchr(const char * s, const char c, str_predicate pred) {
  for (char * ret = (char *)s; *ret != '\0'; ret++) {
    if (pred(ret, c, 0)) return ret;
  }
  return NULL;
}

//returned string should be allocated by the user and will be freed.
char *strclr(const char *s)
{
  char * trnc = strpchr(s, '#', not_equal); // truncated string
  if (!trnc) return "";
  if (!strcount(trnc, '#', total)) return "";
  char * ret = malloc(strlen(trnc));
  for (int i = 0, j = 0; trnc[i] != '\0'; i++) {
    if (trnc[i] != '#') ret[j++] = trnc[i];
    else ret[--j] = '\0';
  }
  return ret;
}

int main(int argc, char ** argv) {
	if (argc > 1) printf("%s\n", strclr(argv[1]));
	else return 1;
	return 0;
}
