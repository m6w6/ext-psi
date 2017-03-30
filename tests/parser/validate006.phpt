--TEST--
validate types
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 
psi_validate_string("typedef int *(*foo)(int *(*bar)(int baz));");
?>
===DONE===
--EXPECTF--
===TEST===
===DONE===
