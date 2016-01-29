PSI_CHECK_SYS_TIME() {
	PSI_CONFIG_POSIX(sys/time, sys/time.h)

	PSI_CONST(ITIMER_REAL, int)
	PSI_CONST(ITIMER_VIRTUAL, int)
	PSI_CONST(ITIMER_PROF, int)

	PSI_STRUCT(struct timeval, [
		time_t tv_sec,
		suseconds_t tv_usec]
	)
	PSI_STRUCT(struct itimerval, [
		struct timeval it_interval,
		struct timeval it_value]
	)
	PSI_STRUCT(struct timezone, [
		int tz_minuteswest,
		int tz_dsttime]
	)

	PSI_DECL(int getitimer, [(int which, struct itimerval *value)])
	PSI_DECL(int setitimer, [(int which, struct itimerval *value, struct itimerval *ovalue)])
	PSI_DECL(int gettimeofday, [(struct timeval *tp, struct timezone *tz)])
	PSI_DECL(int utimes, [(char *path, struct timeval times@<:@2@:>@)])
	PSI_DECL(int utimensat, [(int fd, char *path, struct timespec times@<:@2@:>@)])
}
