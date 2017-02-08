PSI_CHECK_ARPA_INET() {
	PSI_DECL(uint32_t htonl, [(uint32_t l)])
	PSI_DECL(uint16_t htons, [(uint16_t s)])
	PSI_DECL(uint32_t ntohl, [(uint32_t l)])
	PSI_DECL(uint16_t ntohs, [(uint16_t s)])
	
	PSI_DECL(in_addr_t inet_addr, [(const char *cp)])
	PSI_DECL(char *inet_ntoa, [(struct in_addr in)])
	PSI_DECL(const char *inet_ntop, [(int af, const void *src, char *dst, socklen_t size)])
	PSI_DECL(int inet_pton, [(int af, const char *src, void *dst)])
}