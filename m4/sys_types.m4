PSI_CHECK_SYS_TYPES() {
	AC_CHECK_HEADERS(sys/types.h)

	PSI_TYPE(blkcnt_t, int)
	PSI_TYPE(blksize_t, int)
	PSI_TYPE(clock_t, int)
	PSI_TYPE(clockid_t, int)
	PSI_TYPE(dev_t, int)
	PSI_TYPE(fsblkcnt_t, uint)
	PSI_TYPE(fsfilcnt_t, uint)
	PSI_TYPE(gid_t, int)
	PSI_TYPE(id_t, int)
	PSI_TYPE(ino_t, uint)
	PSI_TYPE(key_t, int)
	PSI_TYPE(mode_t, int)
	PSI_TYPE(nlink_t, int)
	PSI_TYPE(off_t, int)
	PSI_TYPE(pid_t, int)
	PSI_TYPE(ssize_t, int)
	PSI_TYPE(suseconds_t, int)
	PSI_TYPE(time_t, int)
	PSI_TYPE(timer_t, int)
	PSI_TYPE(uid_t, int)
}
