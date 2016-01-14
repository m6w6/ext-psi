PSI_CHECK_SYS_STAT() {
	AC_CHECK_HEADERS([sys/stat.h])

	PSI_STRUCT(struct stat, [
		dev_t st_dev,
		ino_t st_ino,
		mode_t st_mode,
		nlink_t st_nlink,
		uid_t st_uid,
		gid_t st_gid,
		dev_t st_rdev,
		off_t st_size,
		blksize_t st_blksize,
		blkcnt_t st_blocks,
		time_t st_atime,
		time_t st_mtime,
		time_t st_ctime,
		struct timespec st_atim,
		struct timespec st_mtim,
		struct timespec st_ctim,
		struct timespec st_atimespec,
		struct timespec st_mtimespec,
		struct timespec st_ctimespec,
		struct timespec st_birthtimespec,
		time_t st_birthtime,
		int st_flags,
		int st_gen]
	)

	PSI_CONST(S_IFMT, int)
	PSI_CONST(S_IFBLK, int)
	PSI_CONST(S_IFCHR, int)
	PSI_CONST(S_IFIFO, int)
	PSI_CONST(S_IFREG, int)
	PSI_CONST(S_IFDIR, int)
	PSI_CONST(S_IFLNK, int)
	PSI_CONST(S_IFSOCK, int)
	PSI_CONST(S_IRWXU, int)
	PSI_CONST(S_IRUSR, int)
	PSI_CONST(S_IWUSR, int)
	PSI_CONST(S_IXUSR, int)
	PSI_CONST(S_IRWXG, int)
	PSI_CONST(S_IRGRP, int)
	PSI_CONST(S_IWGRP, int)
	PSI_CONST(S_IXGRP, int)
	PSI_CONST(S_IRWXO, int)
	PSI_CONST(S_IROTH, int)
	PSI_CONST(S_IWOTH, int)
	PSI_CONST(S_IXOTH, int)
	PSI_CONST(S_ISUID, int)
	PSI_CONST(S_ISGID, int)
	PSI_CONST(UTIME_NOW, int)
	PSI_CONST(UTIME_OMIT, int)

	PSI_MACRO(int S_ISBLK, [(mode_t m)])
	PSI_MACRO(int S_ISCHR, [(mode_t m)])
	PSI_MACRO(int S_ISDIR, [(mode_t m)])
	PSI_MACRO(int S_ISFIFO, [(mode_t m)])
	PSI_MACRO(int S_ISREG, [(mode_t m)])
	PSI_MACRO(int S_ISLNK, [(mode_t m)])
	PSI_MACRO(int S_ISSOCK, [(mode_t m)])

	PSI_MACRO(int S_TYPEISMQ, [(struct stat *s)])
	PSI_MACRO(int S_TYPEISSEM, [(struct stat *s)])
	PSI_MACRO(int S_TYPEISSHM, [(struct stat *s)])
	PSI_MACRO(int S_TYPEISTMO, [(struct stat *s)])

	PSI_DECL(int chmod, [(char *path, mode_t mode)])
	PSI_DECL(int fchmod, [(int fd, mode_t mode)])
	PSI_DECL(int fchmodat, [(int fd, char *path, mode_t mode, int flag)])
	PSI_DECL(int fstat, [(int fd, struct stat *buf)])
	PSI_DECL(int fstatat, [(int fd, char *path, struct stat *buf, int flag)])
	PSI_DECL(int futimens, [(int fd, struct timespec times@<:@2@:>@)])
	PSI_DECL(int lstat, [(char *path, struct stat *buf)])
	PSI_DECL(int mkdir, [(char *path, mode_t mode)])
	PSI_DECL(int mkdirat, [(int fd, char *path, mode_t mode)])
	PSI_DECL(int mkfifo, [(char *path, mode_t mode)])
	PSI_DECL(int mkfifoat, [(int fd, char *path, mode_t mode)])
	PSI_DECL(int mknod, [(char *path, mode_t mode, dev_t dev)])
	PSI_DECL(int mknodat, [(int fd, char *path, mode_t mode, dev_t dev)])
	PSI_DECL(int stat, [(char *path, struct stat *buf)])
	PSI_DECL(mode_t umask, [(mode_t mode)])
	PSI_DECL(int utimensat, [(int fd, char *path, struct timespec times@<:@2@:>@, int flag)])
}
