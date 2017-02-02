PSI_CHECK_SYS_TIMES() {

	PSI_STRUCT(struct tms, [
		clock_t tms_utime,
		clock_t tms_stime,
		clock_t tms_cutime,
		clock_t tms_cstime]
	)

	PSI_DECL(clock_t times, [(struct tms *buf)])
}
