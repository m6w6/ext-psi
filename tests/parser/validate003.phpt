--TEST--
validate types
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 

psi_validate_string("typedef long int;");
?>
===DONE===
--EXPECTF--
===TEST===

Warning: PSI syntax error, unexpected ;, expecting %s at col 17 in %s on line 1
===DONE===
