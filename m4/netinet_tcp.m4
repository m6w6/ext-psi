PSI_CHECK_NETINET_TCP() {
	AC_CHECK_HEADERS(netinet/tcp.h)

	PSI_CONST(TCP_NODELAY, int)
}