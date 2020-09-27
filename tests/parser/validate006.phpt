--TEST--
validate types
--FILE--
===TEST===
<?php 
psi_validate_string("typedef int *(*foo)(int *(*bar)(int baz));");
?>
===DONE===
--EXPECTF--
===TEST===
===DONE===
