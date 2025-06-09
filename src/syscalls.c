#include <sys/stat.h>
#include <sys/times.h>
#include <errno.h>
#undef errno
extern int errno;

#include "usart.h"


register char * stack_ptr asm("sp");
void *_sbrk(int inc) {
  extern char __bss_end__; /* Defined by linker*/
  static char *heap_end;
  char *prev_heap_end;

  if (heap_end == 0) {
    heap_end = &__bss_end__;
  }

  prev_heap_end = heap_end;

  if (heap_end + inc > stack_ptr) {
    while (1) {
      // TODO add interrupt
    }
  }

  heap_end += inc;
  return (void*) prev_heap_end;

}

void _exit(int exit_code) {
  while (1) {
    // TODO add interrupt
    // NOTE empty while loop is considered undefined behavior
  }
}

int _close(int file) {
  return -1; // file close/open always fails
}

char *__env[1] = { 0 };
char **environ = __env;

int _execve(char *name, char **argv, char **env) {
  errno = ENOMEM;
  return -1;
}

int _fork(void) {
  errno = EAGAIN;
  return -1;
}

int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _getpid(void) {
  return 1; // only 1 process: 1
}

int _isatty(int file) {
  return 1; // file is always connected to terminal
}

int _kill(int pid, int sig) {
  errno = EINVAL; // invalid, no pid
  return -1;
}

int _link(char *old, char *new) {
  errno = EMLINK;
  return -1;
}

int _unlink(char *name) {
  errno = ENOENT;
  return -1;
}

int _lseek(int file, int ptr, int dir) {
  return 0; // no file seeking
}

int _open(const char *name, int flags, int mode) {
  return -1; // no file opening
}

int _read(int file, char *ptr, int len) {
  return 0; // no file reading
}

int _write(int file, char *ptr, int len) {
  (void) file;
  for (uint32_t i = 0; i < len; i++) {
    usart_write(USART2, *ptr++);
  }
  return len;
}

int _wait(int *status) {
  errno = ECHILD;
  return -1;
}

int _times(struct tms *buf) {
  return -1;
}

int _stat(char *file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

