AC_DEFUN(PSI_CHECK_STDIO, [
    AC_CHECK_HEADER(stdio.h)

    PSI_STRUCT(FILE)
    PSI_STRUCT(fpos_t)

    PSI_CONST(BUFSIZ, int)
    PSI_CONST(_IOFBF, int)
    PSI_CONST(_IOLBF, int)
    PSI_CONST(_IONBF, int)
    PSI_CONST(SEEK_CUR, int)
    PSI_CONST(SEEK_END, int)
    PSI_CONST(SEEK_SET, int)
    PSI_CONST(FILENAME_MAX, int)
    PSI_CONST(FOPEN_MAX, int)
    PSI_CONST(TMP_MAX, int)
    PSI_CONST(EOF, int)
    PSI_CONST(P_tmpdir, string)
    PSI_CONST(L_ctermid, int)
    PSI_CONST(L_tmpnam, int)

    PSI_DECL(void clearerr, [(FILE *stream)])
    PSI_DECL(char *ctermid, [(char *s)])
    PSI_DECL(int fclose, [(FILE *stream)])
    PSI_DECL(FILE *fdopen, [(int fd, char *mode)])
    PSI_DECL(int feof, [(FILE *stream)])
    PSI_DECL(int ferror, [(FILE *stream)])
    PSI_DECL(int fflush, [(FILE *stream)])
    PSI_DECL(int fgetc, [(FILE *stream)])
    PSI_DECL(int fgetpos, [(FILE *stream, fpos_t *pos)])
    PSI_DECL(char *fgets, [(char *buf, int len, FILE *stream)])
    PSI_DECL(int fileno, [(FILE *stream)])
    PSI_DECL(void flockfile, [(FILE *stream)])
    PSI_DECL(FILE *fmemopen, [(void *buf, size_t len, char *mode)])
    PSI_DECL(FILE *fopen, [(char *path, char *mode)])
    PSI_DECL(int fputc, [(int c, FILE *stream)])
    PSI_DECL(int fputs, [(char *s, FILE *stream)])
    PSI_DECL(size_t fread, [(void *buf, size_t len, size_t n, FILE *stream)])
    PSI_DECL(FILE *freopen, [(char *path, char *mode, FILE *stream)])
    PSI_DECL(int fseek, [(FILE *stream, long offset, int whence)])
    PSI_DECL(int fseeko, [(FILE *stream, off_t offset, int whence)])
    PSI_DECL(int fsetpos, [(FILE *stream, fpos_t *pos)])
    PSI_DECL(long ftell, [(FILE *stream)])
    PSI_DECL(off_t ftello, [(FILE *stream)])
    PSI_DECL(int ftrylockfile, [(FILE *stream)])
    PSI_DECL(void funlockfile, [(FILE *stream)])
    PSI_DECL(size_t fwrite, [(void *buf, size_t len, size_t n, FILE *stream)])
    PSI_DECL(int getc, [(FILE *stream)])
    PSI_DECL(int getchar, [(void)])
    PSI_DECL(int getc_unlocked, [(FILE *stream)])
    PSI_DECL(int getchar_unlocked, [(void)])
    PSI_DECL(ssize_t getdelim, [(char **lineptr, size_t *n, int delim, FILE *stream)])
    PSI_DECL(ssize_t getline, [(char **lineptr, size_t *n, FILE *stream)])
    PSI_DECL(char *gets, [(char *buf)])
    PSI_DECL(FILE *open_memstream, [(char **ptr, size_t *sizeloc)])
    PSI_DECL(int pclose, [(FILE *stream)])
    PSI_DECL(void perror, [(char *s)])
    PSI_DECL(FILE *popen, [(char *command, char *type)])
    PSI_DECL(int putc, [(int c, FILE *stream)])
    PSI_DECL(int putchar, [(int c)])
    PSI_DECL(int putc_unlocked, [(int c, FILE *stream)])
    PSI_DECL(int putchar_unlocked, [(int c)])
    PSI_DECL(int puts, [(char *s)])
    PSI_DECL(int remove, [(char *path)])
    PSI_DECL(int rename, [(char *old, char *new)])
    PSI_DECL(int renameat, [(int oldfd, char *oldpath, int newfd, char *newpath)])
    PSI_DECL(void rewind, [(FILE *stream)])
    PSI_DECL(void setbuf, [(FILE *stream, char *buf)])
    PSI_DECL(int setvbuf, [(FILE *stream, char *buf, int mode, size_t size)])
    PSI_DECL(char *tempnam, [(char *dir, char *prefix)])
    PSI_DECL(FILE *tmpfile, [(void)])
    PSI_DECL(char *tmpnam, [(char *s)])
    PSI_DECL(int ungetc, [(int c, FILE *stream)])

])
