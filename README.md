# ext-psi

[![Join the chat at https://gitter.im/m6w6/ext-psi](https://badges.gitter.im/m6w6/ext-psi.svg)](https://gitter.im/m6w6/ext-psi?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Build Status](https://travis-ci.org/m6w6/ext-psi.svg?branch=master)](https://travis-ci.org/m6w6/ext-psi)

PSI is a PHP extension, which provides a foreign function interface through
`libffi` and/or `libjit`.

The acronym PSI may be read as:
* PHP System Interface

> **WARNING:**  
> This is heavy WIP.

## Features

* structs, unions, enums and typedefs
* numeric and boolean expressions
* scalar constants
* vararg calls

## Installing

> **WARNING:**  
> This is heavy WIP. Installation only works from a source checkout 
> with php-src@master on x86_64-linux yet.
> Sort of works on x64_64-darwin, too, roughly.

### PECL

> Not implemented yet.

This extension is distributed through [PECL](http://pecl.php.net) and can be
installed with [PEAR](http://pear.php.net)'s pecl command:

	pecl install psi

### PHARext

> Not implemented yet.

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

### psi.blacklist.decls

A comma separated list of C function declarations to ignore.

### psi.blacklist.vars

A comma separated list of C variable declarations to ignore.

## PSI files

PSI files are augmented C header files. So, everything usually found in C
headers including comments, preprocessor directives, typedefs, structs, 
unions, enums, function and variable declarations should work.

That means, that you can just include C headers in the usual way:

```c
#include <stdlib.h>
```

### Dynamic Libraries

PSI needs to know which library it should `dlopen` unless the declared functions
are provided by the standard C library. Therefore the PSI preprocessor
understands a special pragma:

```c
#pragma lib "crypt"
```

### Constants

```c
const int num\ZERO = 0;
const string pwd\TOKEN = "4WlOjXGL";
```

Constants must have namespaced identifiers and are registered as userland constants.

C enums and preprocessor macros with numerical or string expressions are
automatically discovered and registered as constants.

### Implementations

Implementations are the userland visible interfaces to the foreign function interface.

```php
function str\error(int $num) : string {
    let errnum = intval($num);
    return strerror(errnum) as to_string(strerror);
}
```

Each implementation refers to exactly one declared foreign function referenced in its `return` statement. Each native function, on the other hand, may have any number of implementations.

## Complete example

```c
#ifdef __linux__
/* needed for setkey() in stdlib.h */
# pragma lib "crypt"
#endif

/* for free() */
#include <stdlib.h>
 
#pragma lib "idn"
#include <idna.h>

function idn\utf8_to_ascii(string $host, string &$result, int $flags = 0) : int {
    // there must be a `let` statement for each
    // declared argument of the called function

    // setup a pointer to NULL
	let buffer = &NULL;

	// setup a string pointer to $host
	let host = strval($host);

	// assing the integer value of $flags
	let flags = intval($flags);

	// the function to call is referenced in
	// the return statement, along with the
	// necessary cast how to interpret the
	// returned native value
	return idna_to_ascii_8z(host, buffer, flags) 
	           as to_int(idna_to_ascii_8z);

	// by-ref vars might receive output values
	// through `set` statments, which also
	// require a cast how to marshal the
	// native data as PHP value
	set $result = to_string(*buffer);

	// after the buffer has been marshaled
	// for the PHP engine, we have to free
	// the buffer to avoid a memory leak
	free free(*buffer);
	// note that in this example we omit the
	// declaration of the free() function called
	// in our `free` statement for brevity
}

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

## License

ext-psi is licensed under the 2-Clause-BSD license, which can be found in
the accompanying [LICENSE](./LICENSE) file.

## Contributing

All forms of contribution are welcome! Please see the bundled
[CONTRIBUTING](./CONTRIBUTING.md) note for the general principles followed.

The list of past and current contributors is maintained in [THANKS](./THANKS).
