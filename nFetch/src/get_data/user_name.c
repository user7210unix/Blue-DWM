#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_current_username() {
  char *result = getlogin();
  if (result == NULL) {
    return NULL;
  }

  size_t len = strlen(result);
  char *username = (char *)malloc(len + 1);
  if (username == NULL) {
    return NULL;
  }

  strncpy(username, result, len);
  username[len] = '\0';

  return username;
}
