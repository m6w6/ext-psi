--TEST--
validate types
--FILE--
===TEST===
<?php 
psi_validate_string("struct a; \ntypedef struct a a_t;");
?>
===DONE===
--EXPECTF--
===TEST===
===DONE===
