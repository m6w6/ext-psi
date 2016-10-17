PSI_CHECK_NETINET_TCP() {
	PSI_CONFIG_POSIX(netinet/tcp, netinet/tcp.h)

	PSI_CONST(TCP_NODELAY, int)
}
