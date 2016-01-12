AC_DEFUN(PSI_CHECK_SYS_SOCKET, [
	AC_CHECK_HEADERS(sys/socket.h)
	
	PSI_TYPE(socklen_t, int)
	PSI_TYPE(sa_family_t, uint)
	
	PSI_STRUCT(struct sockaddr, [
		sa_family_t sa_family,
		char sa_data@<:@0@:>@]
	)
	PSI_STRUCT(struct sockaddr_storage, [
		sa_family_t ss_family]
	)
	PSI_STRUCT(struct msghdr, [
		void *msg_name,
		socklen_t msg_namelen,
		struct iovec *msg_iov,
		int msg_iovlen,
		void *msg_control,
		socklen_t msg_controllen,
		int msg_flags]
	)
	PSI_STRUCT(struct cmsghdr, [
		socklen_t cmsg_len,
		int cmsg_level,
		int cmsg_type]
	)
	PSI_STRUCT(struct linger, [
		int l_onoff,
		int l_linger]
	)
	
	PSI_CONST(AF_INET, int)
	PSI_CONST(AF_INET6, int)
    PSI_CONST(AF_UNIX, int)
    PSI_CONST(AF_UNSPEC, int)
    PSI_CONST(MSG_CTRUNC, int)
    PSI_CONST(MSG_DONTROUTE, int)
    PSI_CONST(MSG_EOR, int)
    PSI_CONST(MSG_NOSIGNAL, int)
    PSI_CONST(MSG_OOB, int)
    PSI_CONST(MSG_PEEK, int)
    PSI_CONST(MSG_TRUNC, int)
    PSI_CONST(MSG_WAITALL, int)
    PSI_CONST(SCM_RIGHTS, int)
    PSI_CONST(SHUT_RD, int)
    PSI_CONST(SHUT_RDWR, int)
    PSI_CONST(SHUT_WR, int)
    PSI_CONST(SOCK_DGRAM, int)
    PSI_CONST(SOCK_RAW, int)
    PSI_CONST(SOCK_SEQPACKET, int)
    PSI_CONST(SOCK_STREAM, int)
    PSI_CONST(SOL_SOCKET, int)
    PSI_CONST(SO_ACCEPTCONN, int)
    PSI_CONST(SO_BROADCAST, int)
    PSI_CONST(SO_DEBUG, int)
    PSI_CONST(SO_DONTROUTE, int)
    PSI_CONST(SO_ERROR, int)
    PSI_CONST(SO_KEEPALIVE, int)
    PSI_CONST(SO_LINGER, int)
    PSI_CONST(SO_OOBINLINE, int)
    PSI_CONST(SO_RCVBUF, int)
    PSI_CONST(SO_RCVLOWAT, int)
    PSI_CONST(SO_RCVTIMEO, int)
    PSI_CONST(SO_REUSEADDR, int)
    PSI_CONST(SO_SNDBUF, int)
    PSI_CONST(SO_SNDLOWAT, int)
    PSI_CONST(SO_SNDTIMEO, int)
    PSI_CONST(SO_TYPE, int)
    
    PSI_MACRO(unsigned char *CMSG_DATA, [(struct cmsghdr *m)])
	PSI_MACRO(struct cmsghdr *CMSG_NXTHDR, [(struct msghdr *m, struct cmsghdr *c)])
	PSI_MACRO(struct cmsghdr *CMSG_FIRSTHDR, [(struct msghdr *m)])
	
	PSI_DECL(int accept, [(int socket, struct sockaddr *address, socklen_t *address_len)])
	PSI_DECL(int bind, [(int socket, struct sockaddr *address, socklen_t address_len)])
	PSI_DECL(int connect, [(int socket, struct sockaddr *address, socklen_t address_len)])
	PSI_DECL(int getpeername, [(int socket, struct sockaddr *address, socklen_t *address_len)])
	PSI_DECL(int getsockname, [(int socket, struct sockaddr *address, socklen_t *address_len)])
	PSI_DECL(int getsockopt, [(int socket, int level, int option_name, void *option_value, socklen_t *option_len)])
	PSI_DECL(int listen, [(int socket, int backlog)])
	PSI_DECL(int recv, [(int socket, void *buffer, size_t length, int flags)])
	PSI_DECL(int recvfrom, [(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len)])
	PSI_DECL(int recvmsg, [(int socket, struct msghdr *message, int flags)])
	PSI_DECL(int send, [(int socket, void *buffer, size_t length, int flags)])
	PSI_DECL(int sendmsg, [(int socket, struct msghdr *message, int flags)])
	PSI_DECL(int sendto, [(int socket, void *message, size_t length, int flags, struct sockaddr *dest_addr, socklen_t dest_len)])
	PSI_DECL(int setsockopt, [(int socket, int level, int option_name, void *option_value, socklen_t option_len)])
	PSI_DECL(int shutdown, [(int socket, int how)])
	PSI_DECL(int sockatmark, [(int socket)])
	PSI_DECL(int socket, [(int domain, int type, int protocol)])
	PSI_DECL(int socketpair, [(int domain, int type, int protocol, int socket_vector@<:@2@:>@)])
	
])