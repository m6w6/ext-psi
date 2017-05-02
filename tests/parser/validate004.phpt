--TEST--
validate types
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 
psi_validate_string("struct a; \ntypedef struct a a_t;");
?>
===DONE===
--EXPECTF--
===TEST===
===DONE===
