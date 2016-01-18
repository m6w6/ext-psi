PSI_CHECK_NETINET_IN() {
	AC_CHECK_HEADERS(netinet/in.h)

	PSI_TYPE(in_port_t, uint)
	PSI_TYPE(in_addr_t, uint)

	PSI_STRUCT(struct in_addr, [
		in_addr_t s_addr]
	)

	PSI_STRUCT(struct sockaddr_in, [
		sa_family_t sin_family,
		in_port_t sin_port,
		struct in_addr sin_addr]
	)

	PSI_STRUCT(struct in6_addr, [
		uint8_t s6_addr@<:@16@:>@]
	)
	PSI_STRUCT(struct sockaddr_in6, [
		sa_family_t sin6_family,
		in_port_t sin6_port,
		uint32_t sin6_flowinfo,
		struct in6_addr sin6_addr,
		uint32_t sin6_scope_id]
	)

	PSI_STRUCT(struct ipv6_mreq, [
		struct in6_addr ipv6mr_multiaddr,
		unsigned ipv6mr_interface]
	)

	PSI_CONST(IPPROTO_IP, int)
	PSI_CONST(IPPROTO_IPV6, int)
	PSI_CONST(IPPROTO_ICMP, int)
	PSI_CONST(IPPROTO_RAW, int)
	PSI_CONST(IPPROTO_TCP, int)
	PSI_CONST(IPPROTO_UDP, int)

	PSI_CONST(INADDR_ANY, int)
	PSI_CONST(INADDR_BROADCAST, int)
	PSI_CONST(INET6_ADDRSTRLEN, int)

	PSI_CONST(IPV6_JOIN_GROUP, int)
	PSI_CONST(IPV6_LEAVE_GROUP, int)
	PSI_CONST(IPV6_MULTICAST_HOPS, int)
	PSI_CONST(IPV6_MULTICAST_IF, int)
	PSI_CONST(IPV6_MULTICAST_LOOP, int)
	PSI_CONST(IPV6_UNICAST_HOPS, int)
	PSI_CONST(IPV6_V6ONLY, int)

	PSI_MACRO(int IN6_IS_ADDR_UNSPECIFIED, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_LOOPBACK, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_MULTICAST, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_LINKLOCAL, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_SITELOCAL, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_V4MAPPED, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_V4COMPAT, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_MC_NODELOCAL, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_MC_LINKLOCAL, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_MC_SITELOCAL, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_MC_ORGLOCAL, [(const struct in6_addr *a)])
	PSI_MACRO(int IN6_IS_ADDR_MC_GLOBAL, [(const struct in6_addr *a)])

	PSI_EXTVAR(struct in6_addr in6addr_loopback)
}
