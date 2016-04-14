--TEST--
enum
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 
var_dump(psi_validate(__DIR__."/enum001.psi"));
?>
===DONE===
--EXPECT--
===TEST===
bool(true)
===DONE===
