--TEST--
validate types
--FILE--
===TEST===
<?php 

function validate($check, $psi) {
	if ($check !== psi_validate_string($psi)) {
		printf("Assertion failed!\nExpected: %s\n\n%s\n\n",
				$check ? "true" : "false", $psi);
	}
}

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

?>
===DONE===
--EXPECTF--
===TEST===
===DONE===
