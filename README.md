# ext-psi

[![Build Status](https://travis-ci.org/m6w6/ext-psi.svg?branch=master)](https://travis-ci.org/m6w6/ext-psi)

PSI is a PHP extension, which provides a foreign function interface through
`libffi` and/or `libjit`.

The acronym PSI may be read as:
* PHP System Interface
* POSIX Standard Interface

The latter because PSI can be configured to include declarations for most of the
[base definitions and system interfaces of POSIX.1-2008](http://pubs.opengroup.org/onlinepubs/9699919799/).

> **WARNING:**  
> This is heavy WIP. Only a small part of configuration and implementation has been completed yet.

## Features

* standard scalar types mapped to stdint types
* structs, unions, enums and typedefs
* simple numeric expressions
* string and int constants
* vararg calls

## Installing

> **WARNING:**  
> This is heavy WIP. Installation only works from a source checkout yet.

### PECL

This extension is distributed through [PECL](http://pecl.php.net) and can be
installed with [PEAR](http://pear.php.net)'s pecl command:

	pecl install psi

### PHARext

Watch out for [PECL replicates](https://replicator.pharext.org?psi)
and [pharext](https://github.com/pharext) packages attached to
[releases](https://github.com/m6w6/ext-psi/releases).

### Checkout

This extension is hosted at [Github](https://github.com/m6w6/ext-psi) with a
personal [mirror](https://git.m6w6.name/?p=m6w6/ext-psi) available.

	git clone github.com:m6w6/ext-psi

	cd ext-psi

	/path/to/phpize
	./configure --with-php-config=/path/to/php-config
	make
	sudo make install

## Configuring PSI at build time

PSI supports the following configure switches:

### --enable-psi
**Enable PHP System Interface support.**

This is only relevant for an in-tree build. Use `--enable-psi` to include
the PSI extension in the build.

### --enable-psi-posix
**Pre-define POSIX decls.**

Use `--enable-psi-posix=all` to enable all available POSIX checks.

Use `--enable-psi-posix=section,another,onemore` to enable specific modules only.

The following modules are included by default:

[stdint](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdint.h.html),
[stddef](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stddef.h.html),
[stdlib](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdlib.h.html),
[sys/types](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_types.h.html)

The following modules are available to select:

[errno](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html),
[fcntl](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/fcntl.h.html),
[glob](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/glob.h.html),
[locale](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/locale.h.html),
[ndbm](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/ndbm.h.html),
[netdb](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/netdb.h.html),
[netinet/in](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/netinet_in.h.html),
[netinet/tcp](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/netinet_tcp.h.html),
[poll](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/poll.h.html),
[signal](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/signal.h.html),
[stdio](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdio.h.html),
[sys/select](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_select.h.html),
[sys/socket](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_socket.h.html),
[sys/stat](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_stat.h.html),
[sys/time](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_time.h.html),
[sys/times](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_times.h.html),
[sys/uio](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_uio.h.html),
[sys/utsname](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_utsname.h.html),
[syslog](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/syslog.h.html),
[time](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/time.h.html),
[unistd](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/unistd.h.html),
[wchar](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/wchar.h.html),
[wctype](http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/wctype.h.html),

### --with-psi-libjit
**Path to libjit.**

> **WARNING:**  
> We currently rely on a patched libjit, because of an apparent bug in how
> libjit creates closures, which still needs to be verified, though.
> See https://github.com/m6w6/libjit for the preliminary patch.

### --with-psi-libffi
**Path to libffi.**

## Configuring PSI at runtime

### psi.engine

The backend that PSI should use as FFI, either _jit_ for `libjit` or _ffi_ for `libffi`. Defaults to "ffi".

### psi.directory

A colon separated list of directories to scan for `*.psi` files. Defaults to "psi.d".

## PSI files

### Comments

* C style multi line comments
* C++ style single line comments
* CPP directives are ignored, so the hash sign basically works as single line comment

```c
// this is a one line comment
/* followed
   by a multi
   line comment
*/
# this looks like a pre-processor directive and is ignored
```

### Typedefs

```c
typedef unsigned char xmlChar;
```

They follow the basic C-style `typedef` syntax.

```c
typedef struct str {
    char *p;
    size_t l;
} str_t;
```
You can also `typedef` unions and enums that way.

### Structs

The following example results in exactly the same interpretation as the previous:

```c
typedef struct str str_t;
struct str {
    char *p;
    size_t l;
}
```

A struct will have the size of all its elements plus padding combined and an
alignment equal to that of the largest element's alignment.

### Enums

Enums are considered to be of type `int`.

```c
enum STATUS {
 FAILURE = -1,
 SUCCESS
}
```

Enums will be registered as userland constants with the following pattern:

* `psi\STATUS\FAILURE` with value -1
* `psi\STATUS\SUCCESS` with value 0

### Unions

```c
union anyval {
    char c;
    short s;
    int i;
    long l;
    float f;
    double d;
    str_t str;
}
```

Unions will have the size and alignment of the largest element they contain.

### Lib

```c
lib "awesome";
```

These statements define what library should be `dlopen()`-ed to look up symbols from declarations.
They must only occur once in a file. When a `lib` statement is omitted, stdlib is assumed.

### Declarations

Declarations provide all information needed to make a foreign function call.

```c
extern char *strerror(int errnum);
```

You may specify a non-standard calling convention in place of `extern`, where `default` and `cdecl` have the same meaning as `extern`.

Additionally recognized calling conventions include: `mscdecl`, `stdcall` and `fastcall`.

### Constants

```c
const int num\ZERO = 0;
const string pwd\TOKEN = "4WlOjXGL";
```

Constants must have a namespaced identifiers and are registered as userland constants.

### Implementations

Implementations are the userland visible interfaces to the foreign function interface.

```php
function str\error(int $num) : string {
    let errnum = intval($num);
    return to_string(strerror);
}
```

Each implementation refers to exactly one declared foreign function referenced in its `return` statement. Each declaration, on the other hand, may have any number of implementations.

## Complete example

```c
# all declarations in this file should be looked up in libidn
lib "idn";

# IDNA errors
const int \IDNA_SUCCESS = 0;
const int \IDNA_STRINGPREP_ERROR = 1;
const int \IDNA_PUNYCODE_ERROR = 2;
const int \IDNA_CONTAINS_NON_LDH = 3;
const int \IDNA_CONTAINS_LDH = 3;
const int \IDNA_CONTAINS_MINUS = 4;
const int \IDNA_INVALID_LENGTH = 5;
const int \IDNA_NO_ACE_PREFIX = 6;
const int \IDNA_ROUNDTRIP_VERIFY_ERROR = 7;
const int \IDNA_CONTAINS_ACE_PREFIX = 8;
const int \IDNA_ICONV_ERROR = 9;
const int \IDNA_MALLOC_ERROR = 201;
const int \IDNA_DLOPEN_ERROR = 202;
# IDNA flags
const int \IDNA_ALLOW_UNASSIGNED = 1;
const int \IDNA_USE_STD3_ASCII_RULES = 2;

# nothing special about the declaration here
default int idna_to_ascii_8z(char *host, char **buffer, int flags);

function idn\utf8_to_ascii(string $host, string &$result, int $flags = 0) : int {
    # there must be a `let` statement for each
    # declared argument of the called function

    # setup a pointer to NULL
	let buffer = &NULL;

	# setup a string pointer to $host
	let host = strval($host);

	# assing the integer value of $flags
	let flags = intval($flags);

	# the function to call is referenced in
	# the return statement, along with the
	# neccessary cast how to interpred the
	# returned native value
	return to_int(idna_to_ascii_8z);

	# by-ref vars might receive output values
	# through `set` statments, which also
	# require a cast how to marshal the
	# native data as PHP value
	set $result = to_string(*buffer);

	# after the buffer has been marshaled
	# for the PHP engine, we have to free
	# the buffer to avoid a memory leak
	free free(*buffer);
	# note that in this example we omit the
	# declaration of the free() function called
	# in our `free` statement for brevity
}

default char *idna_strerror(int rc);
function idn\strerror(int $rc) : string {
	return to_string(idna_strerror);
	let rc = intval($rc);
}
```

### Userland

```php
$rc = idn\utf8_to_ascii("flöte.de", $result);
printf("<%s>\n", $result);
printf("%s\n", idn\strerror($rc));

$rc = idn\utf8_to_ascii("…asdf….de", $result, IDNA_USE_STD3_ASCII_RULES);
printf("<%s>\n", $result);
printf("%s\n", idn\strerror($rc));
```

#### Output
```
<xn--flte-6qa.de>
Success
<>
Non-digit/letter/hyphen in input
```

## ChangeLog

A comprehensive list of changes can be obtained from the
[PECL website](https://pecl.php.net/package-changelog.php?package=psi).

Known issues are listed in [BUGS](./BUGS) and future ideas can be found in [TODO](./TODO).

## License

ext-psi is licensed under the 2-Clause-BSD license, which can be found in
the accompanying [LICENSE](./LICENSE) file.

## Contributing

All forms of contribution are welcome! Please see the bundled
[CONTRIBUTING](./CONTRIBUTING.md) note for the general principles followed.

The list of past and current contributors is maintained in [THANKS](./THANKS).
