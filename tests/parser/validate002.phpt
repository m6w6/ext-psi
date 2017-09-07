--TEST--
validate types
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 
psi_validate_string("typedef void foo;");
?>
===DONE===
--EXPECTF--
===TEST===
===DONE===
