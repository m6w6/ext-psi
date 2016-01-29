PSI_CHECK_NETDB() {
	PSI_CONFIG_POSIX(netdb, netdb.h)

	PSI_STRUCT(struct hostent, [
		char *h_name,
		char **h_aliases,
		int h_addrtype,
		int h_length,
		char **h_addr_list]
	)

	PSI_STRUCT(struct netent, [
		char *n_name,
		char **n_aliases,
		int n_addrtype,
		uint32_t n_net]
	)

	PSI_STRUCT(struct protoent, [
		char *p_name,
		char **p_aliases,
		int p_proto]
	)

	PSI_STRUCT(struct servent, [
		char *s_name,
		char **s_aliases,
		int s_port,
		char *s_proto]
	)

	PSI_CONST(IPPORT_RESERVED, int)

	PSI_STRUCT(struct addrinfo, [
		int ai_flags,
		int ai_family,
		int ai_socktype,
		int ai_protocol,
		socklen_t ai_addrlen,
		struct sockaddr *ai_addr,
		char *ai_canonname,
		struct addrinfo *ai_next]
	)

	PSI_CONST(AI_PASSIVE, int)
	PSI_CONST(AI_CANONNAME, int)
	PSI_CONST(AI_NUMERICHOST, int)
	PSI_CONST(AI_NUMERICSERV, int)
	PSI_CONST(AI_V4MAPPED, int)
	PSI_CONST(AI_ALL, int)
	PSI_CONST(AI_ADDRCONFIG, int)

	PSI_CONST(NI_NOFQDN, int)
	PSI_CONST(NI_NUMERICHOST, int)
	PSI_CONST(NI_NAMEREQD, int)
	PSI_CONST(NI_NUMERICSERV, int)
	PSI_CONST(NI_NUMERICSCOPE, int)
	PSI_CONST(NI_DGRAM, int)

	PSI_CONST(NI_MAXHOST, int)
	PSI_CONST(NI_MAXSERV, int)

	PSI_CONST(EAI_AGAIN, int)
	PSI_CONST(EAI_BADFLAGS, int)
	PSI_CONST(EAI_FAIL, int)
	PSI_CONST(EAI_FAMILY, int)
	PSI_CONST(EAI_MEMORY, int)
	PSI_CONST(EAI_NONAME, int)
	PSI_CONST(EAI_SERVICE, int)
	PSI_CONST(EAI_SOCKTYPE, int)
	PSI_CONST(EAI_SYSTEM, int)
	PSI_CONST(EAI_OVERFLOW, int)

	PSI_DECL(void endhostent, [(void)])
	PSI_DECL(void endnetent, [(void)])
	PSI_DECL(void endprotoent, [(void)])
	PSI_DECL(void endservent, [(void)])
	PSI_DECL(void freeaddrinfo, [(struct addrinfo *res)])
	PSI_DECL(char *gai_strerror, [(int errcode)])
	PSI_DECL(int getaddrinfo, [(char *node, char *service, struct addrinfo *hints, struct addrinfo **res)])
	PSI_DECL(struct hostent *gethostent, [(void)])
	PSI_DECL(int getnameinfo, [(struct sockaddr *sa, socklen_t salen, char *host, socklen_t hostlen, char *serv, socklen_t servlen, int flags)])
	PSI_DECL(struct netent *getnetbyaddr, [(uint32_t net, int type)])
	PSI_DECL(struct netent *getnetbyname, [(char *name)])
	PSI_DECL(struct netent *getnetent, [(void)])
	PSI_DECL(struct protoent *getprotobyname, [(char *name)])
	PSI_DECL(struct protoent *getprotobynumber, [(int proto)])
	PSI_DECL(struct protoent *getprotoent, [(void)])
	PSI_DECL(struct servent *getservbyname, [(char *name, char *proto)])
	PSI_DECL(struct servent *getservbyport, [(int port, char *proto)])
	PSI_DECL(struct servent *getservent, [(void)])
	PSI_DECL(void sethostent, [(int stayopen)])
	PSI_DECL(void setnetent, [(int stayopen)])
	PSI_DECL(void setprotoent, [(int stayopen)])
	PSI_DECL(void setservent, [(int stayopen)])
}
