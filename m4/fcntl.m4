PSI_CHECK_FCNTL() {
	AC_CHECK_HEADERS(fcntl.h)

	PSI_CONST(F_DUPFD, int)
	PSI_CONST(F_DUPFD_CLOEXEC, int)
	PSI_CONST(F_GETFD, int)
	PSI_CONST(F_SETFD, int)
	PSI_CONST(F_GETFL, int)
	PSI_CONST(F_SETFL, int)
	PSI_CONST(F_GETLK, int)
	PSI_CONST(F_SETLK, int)
	PSI_CONST(F_SETLKW, int)
	PSI_CONST(F_GETOWN, int)
	PSI_CONST(F_SETOWN, int)

	PSI_CONST(FD_CLOEXEC, int)

	PSI_CONST(F_RDLCK, int)
	PSI_CONST(F_UNLCK, int)
	PSI_CONST(F_WRLCK, int)

	PSI_CONST(O_CLOEXEC, int)
	PSI_CONST(O_CREAT, int)
	PSI_CONST(O_DIRECTORY, int)
	PSI_CONST(O_EXCL, int)
	PSI_CONST(O_NOCTTY, int)
	PSI_CONST(O_NOFOLLOW, int)
	PSI_CONST(O_TRUNC, int)
	PSI_CONST(O_TTY_INIT, int)

	PSI_CONST(O_APPEND, int)
	PSI_CONST(O_DSYNC, int)
	PSI_CONST(O_NONBLOCK, int)
	PSI_CONST(O_RSYNC, int)
	PSI_CONST(O_SYNC, int)

	PSI_CONST(O_ACCMODE, int)

	PSI_CONST(O_EXEC, int)
	PSI_CONST(O_RDONLY, int)
	PSI_CONST(O_RDWR, int)
	PSI_CONST(O_SEARCH, int)
	PSI_CONST(O_WRONLY, int)

	PSI_CONST(AT_FDCWD, int)
	PSI_CONST(AT_EACCESS, int)
	PSI_CONST(AT_SYMLINK_NOFOLLOW, int)
	PSI_CONST(AT_SYMLINK_FOLLOW, int)
	PSI_CONST(AT_REMOVEDIR, int)

	PSI_CONST(POSIX_FADV_DONTNEED, int)
	PSI_CONST(POSIX_FADV_NOREUSE, int)
	PSI_CONST(POSIX_FADV_NORMAL, int)
	PSI_CONST(POSIX_FADV_RANDOM, int)
	PSI_CONST(POSIX_FADV_SEQUENTUAL, int)
	PSI_CONST(POSIX_FADV_WILLNEED, int)

	PSI_STRUCT(struct flock, [
		short l_type,
		short l_whence,
		off_t l_start,
		off_t l_len,
		pid_t l_pid]
	)

	PSI_DECL(int creat, [(const char *path, mode_t mode)])
	PSI_DECL(int fcntl, [(int fd, int cmd, mode_t mode)])
	PSI_DECL(int open, [(const char *path, int flags, mode_t mode)])
	PSI_DECL(int openat, [(int dirfd, const char *path, int flags, mode_t mode)])

	PSI_DECL(int posix_fadvise, [(int fd, off_t offset, off_t len, int advice)])
	PSI_DECL(int posix_fallocate, [(int fd, off_t offset, off_t len)])
}
