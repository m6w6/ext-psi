--TEST--
enum
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 
var_dump(psi_validate_string(<<<PSI
enum a {
 A,
 B,
 C
}

enum b {
	FAILURE = -1,
	SUCCESS = 0
}

enum c {
 no = -1,
 maybe = SUCCESS,
 yes,
 sure = yes
}
PSI
));
?>
===DONE===
--EXPECT--
===TEST===
bool(true)
===DONE===
