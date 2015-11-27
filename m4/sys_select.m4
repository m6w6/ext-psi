AC_DEFUN(PSI_CHECK_SYS_SELECT, [
	AC_CHECK_HEADERS(sys/select.h)
	
	PSI_STRUCT(fd_set, [])
	
	PSI_CONST(FD_SETSIZE, int)
	
	PSI_MACRO(void FD_CLEAR, [(int fd, fd_set *s)])
	PSI_MACRO(void FD_COPY, [(fd_set *s1, fd_set *s2)])
	PSI_MACRO(void FD_CLR, [(int fd, fd_set *s)])
	PSI_MACRO(void FD_SET, [(int fd, fd_set *s)])
	PSI_MACRO(int FD_ISSET, [(int fd, fd_set *s)])
	PSI_MACRO(void FD_ZERO, [(fd_set *s)])
	
	PSI_DECL(int select, [(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout)])
	dnl PSI_DECL(int pselect, [(int nfds, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout, sigset_t *sigmask)])
])