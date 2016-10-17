PSI_CHECK_TIME() {
	PSI_CONFIG_POSIX(time, time.h)

	PSI_CONST(CLOCKS_PER_SEC, int)
	PSI_CONST(CLOCK_MONOTONIC, int)
	PSI_CONST(CLOCK_PROCESS_CPUTIME_ID, int)
	PSI_CONST(CLOCK_REALTIME, int)
	PSI_CONST(CLOCK_THREAD_CPUTIME_ID, int)
	PSI_CONST(TIMER_ABSTIME, int)

	PSI_STRUCT(struct tm, [
		int tm_sec,
		int tm_min,
		int tm_hour,
		int tm_mday,
		int tm_mon,
		int tm_year,
		int tm_wday,
		int tm_yday,
		int tm_isdst]
	)
	PSI_STRUCT(struct timespec, [
		time_t tv_sec,
		long tv_nsec]
	)
	PSI_STRUCT(struct itimerspec, [
		struct timespec it_interval,
		struct timespec it_value]
	)

	PSI_DECL(char *asctime, [(struct tm *tm)])
	PSI_DECL(char *asctime_r, [(struct tm *tm, char *buf)])
	PSI_DECL(clock_t clock, [()])
	PSI_DECL(int clock_getcpuclockid, [(pid_t pid, clockid_t *clock_id)])
	PSI_DECL(int clock_getres, [(clockid_t clk_id, struct timespec *res)])
	PSI_DECL(int clock_gettime, [(clockid_t clk_id, struct timespec *tp)])
	PSI_DECL(int clock_nanosleep, [(clockid_t clk_id, int flags, struct timespec *rqtp, struct timespec *rmtp)])
	PSI_DECL(int clock_settime, [(clockid_t clk_id, struct timespec *tp)])
	PSI_DECL(char *ctime, [(time_t *t)])
	PSI_DECL(char *ctime_r, [(time_t *t, char *buf)])
	PSI_DECL(double difftime, [(time_t time1, time_t time0)])
	PSI_DECL(struct tm *getdate, [(char *string)])
	PSI_DECL(struct tm *gmtime, [(time_t *t)])
	PSI_DECL(struct tm *gmtime_r, [(time_t *t, struct tm *buf)])
	PSI_DECL(struct tm *localtime, [(time_t *t)])
	PSI_DECL(struct tm *localtime_r, [(time_t *t, struct tm *buf)])
	PSI_DECL(time_t mktime, [(struct tm *tm)])
	PSI_DECL(int nanosleep, [(struct timespec *rqts, struct timespec *rmts)])
	PSI_DECL(size_t strftime, [(char *s, size_t max, char *fmt, struct tm *tm)])
	dnl PSI_DECL(size_t strftime_l, [(char *s, size_t max, char *fmt, struct tm *tm, locale_t l)])
	PSI_DECL(char *strptime, [(char *s, char *fmt, struct tm *tm)])
	PSI_DECL(time_t time, [(time_t *t)])
	dnl PSI_DECL(int timer_create, [(clockid_t clk_id, struct sigevent *se, timer_t *t)])
	PSI_DECL(int timer_delete, [(timer_t t)])
	PSI_DECL(int timer_getoverrun, [(timer_t t)])
	PSI_DECL(int timer_gettime, [(timer_t t, struct itimerspec *ts)])
	PSI_DECL(int timer_settime, [(timer_t t, int flags, struct itimerspec *value, struct itimerspec *ovalue)])
	PSI_DECL(void tzset, [()])

	PSI_EXTVAR(int daylight)
	PSI_EXTVAR(long timezone)
	PSI_EXTVAR(char **tzname)
}
