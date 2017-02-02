PSI_CHECK_POLL() {

	PSI_STRUCT(struct pollfd, [
		int fd,
		short events,
		short revents]
	)

	PSI_TYPE(nfds_t, uint)

	PSI_CONST(POLLIN, int)
	PSI_CONST(POLLRDNORM, int)
	PSI_CONST(POLLRDBAND, int)
	PSI_CONST(POLLPRI, int)
	PSI_CONST(POLLOUT, int)
	PSI_CONST(POLLWRNORM, int)
	PSI_CONST(POLLRWBAND, int)
	PSI_CONST(POLLERR, int)
	PSI_CONST(POLLHUP, int)
	PSI_CONST(POLLNVAL, int)

	PSI_DECL(int poll, [(struct pollfd *fds, nfds_t nfds, int timeout)])
}
