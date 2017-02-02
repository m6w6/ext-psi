PSI_CHECK_SYS_UTSNAME() {

	PSI_STRUCT(struct utsname, [
		char sysname@<:@0@:>@,
		char nodename@<:@0@:>@,
		char release@<:@0@:>@,
		char version@<:@0@:>@,
		char machine@<:@0@:>@,
		char domainname@<:@0@:>@
	])

	PSI_DECL(int uname, [(struct utsname *name)])
}
