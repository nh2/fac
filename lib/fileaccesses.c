#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bigbrother.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s prog args\n", argv[0]);
    exit(1);
  }

  listset *written_to_files = 0;
  listset *read_from_files = 0;
  listset *read_from_directories = 0;
  listset *deleted_files = 0;

  char **args = (char **)malloc(argc*sizeof(char*));
  memcpy(args, argv+1, (argc-1) * sizeof(char*));
  args[argc-1] = NULL;
  bigbrother_process(".", args, &read_from_directories,
                     &read_from_files, &written_to_files, &deleted_files);
  free(args);

  listset *s = read_from_directories;
  while (s != NULL) {
    fprintf(stderr, "l: %s\n", s->path);
    s = s->next;
  }

  s = read_from_files;
  while (s != NULL) {
    fprintf(stderr, "r: %s\n", s->path);
    s = s->next;
  }

  s = written_to_files;
  while (s != NULL) {
    fprintf(stderr, "w: %s\n", s->path);
    s = s->next;
  }

  s = deleted_files;
  while (s != NULL) {
    fprintf(stderr, "d: %s\n", s->path);
    s = s->next;
  }

  free_listset(read_from_directories);
  free_listset(read_from_files);
  free_listset(written_to_files);
  free_listset(deleted_files);
  return 0;
}
