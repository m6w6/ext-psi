--TEST--
validate types
--FILE--
===TEST===
<?php 
psi_validate_string("typedef void foo;");
?>
===DONE===
--EXPECTF--
===TEST===
===DONE===
