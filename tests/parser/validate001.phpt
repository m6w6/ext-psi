--TEST--
validate types
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 

function validate($check, $psi) {
	$file = __DIR__."/001.psi";
	file_put_contents($file, $psi);
	if ($check !== psi_validate($file)) {
		printf("Assertion failed!\nExpected: %s\n\n%s\n\n",
				$check ? "true" : "false", $psi);
	}
}

validate(false, "typedef void foo;");
validate(true, "typedef void *bar;");
validate(false, "typedef long int;");
validate(true, "typedef long foo;");
validate(true, "typedef struct foo bar;");
validate(true, "typedef struct {int a;} foo;");
validate(false, "struct a; \ntypedef struct a a_t;");
validate(true, "struct a::(8,8); \ntypedef struct a a_t;");
validate(true, "typedef struct a a_t; \nstruct a::(8,8);");

validate(true,
<<<PSI
enum {
	A,
	B,
	C
}
PSI
);
validate(false,
<<<PSI
enum {
	A,
	B = A + 2,
	C = X
}
PSI
);

validate(true,
<<<PSI
struct a {
	int i;
}
struct b {
	long l;
}
typedef struct b b;
union v {
	struct a a;
	b b;
	struct {
		double d;
	} s;
	union {
		long l;
		double d;
	} u;
}
PSI
);

validate(true, "typedef int foo(int bar);");
validate(true, "typedef int (foo)(int bar);");
validate(true, "typedef int (*foo)(int bar);");
validate(true, "typedef int *(*foo)(int bar);");
validate(false, "typedef int *(*foo)(int *(*bar)(int baz));");
validate(true, "typedef int *(*bar)(int baz); \ntypedef int *(*foo)(bar bar);");
validate(true, "typedef int bar(int baz); \ntypedef int *(*foo)(bar bar);");

?>
===DONE===
--CLEAN--
<?php
@unlink(__DIR__."/001.psi");
?>
--EXPECTF--
===TEST===

Warning: PSI syntax error: Unexpected token ';' at pos 17 in %s001.psi on line 1

Warning: PSI syntax error: Unexpected token 'int' at pos 14 in %s001.psi on line 1

Warning: Cannot compute size of empty struct 'a' in %s001.psi on line 1

Warning: Unknown variable 'X' in numeric expression in %s001.psi on line 4

Warning: PSI syntax error: Unexpected token '(' at pos 26 in %s001.psi on line 1

Warning: PSI syntax error: Unexpected token '(' at pos 32 in %s001.psi on line 1
===DONE===
