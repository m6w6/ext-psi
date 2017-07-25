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
	if ($check !== psi_validate_string($psi)) {
		printf("Assertion failed!\nExpected: %s\n\n%s\n\n",
				$check ? "true" : "false", $psi);
	}
}

validate(true, "typedef void *bar;");
validate(true, "typedef long foo;");
validate(true, "typedef struct foo bar;");
validate(true, "typedef struct {int a;} foo;");
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

validate(true, "typedef int foo(int bar);");
validate(true, "typedef int (foo)(int bar);");
validate(true, "typedef int (*foo)(int bar);");
validate(true, "typedef int *(*foo)(int bar);");
validate(true, "typedef int *(*bar)(int baz); \ntypedef int *(*foo)(bar bar);");
validate(true, "typedef int bar(int baz); \ntypedef int *(*foo)(bar bar);");

?>
===DONE===
--EXPECTF--
===TEST===
===DONE===
