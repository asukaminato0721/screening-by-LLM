#include "parse.h"
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PARAMS 10
#define MAX_PARAM_LENGTH 100
// "http://example.com/xxx&id=1234&data_type=article&user=john"
int parse_query_string(char *url, struct query_parameter **out) {
  if (url == NULL || out == NULL) {
    return -EINVAL; // Invalid argument
  }
  char *token = strtok(url, "?&");
  if (token == NULL) {
    return 0; // No query parameters found
  }
  // Split the URL by '&'
  size_t count = 0;
  char **segments = malloc(sizeof(char *));
  if (segments == NULL) {
    return -ENOMEM; // Out of memory
  }

  while (token != NULL) {
    segments = realloc(segments, (count + 1) * sizeof(char *));
    if (segments == NULL) {
      return -ENOMEM; // Out of memory
    }
    segments[count++] = token;
    token = strtok(NULL, "&");
  }
  for (size_t i = 0; i < count; i++) {
    printf("L34: %s\n", segments[i]);
  }
  // Create query_parameter objects
  struct query_parameter *params =
      malloc(count * sizeof(struct query_parameter));
  if (params == NULL) {
    free(segments);
    return -ENOMEM; // Out of memory
  }
  count--;
  segments++;
  for (size_t i = 0; i < count; i++) {
    char *segment = segments[i];
    char *key = strtok(segment, "=");
    char *value = strtok(NULL, "=");

    params[i].name = key;
    params[i].value = value;
  }
  segments--;
  free(segments);
  *out = params;
  return count;
}
