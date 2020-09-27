--TEST--
validate types
--FILE--
===TEST===
<?php 
psi_validate_string(
<<<PSI
enum {
	A,
	B = A + 2,
	C = X
}
PSI
);
?>
===DONE===
--EXPECTF--
===TEST===

Warning: Unknown variable 'X' in numeric expression in %s on line 4

Warning: Invalid numeric expression: 'X' in %s on line 4
===DONE===
