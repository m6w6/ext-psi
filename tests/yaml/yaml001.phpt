--TEST--
yaml
--INI--
psi.directory={PWD}:{PWD}/../../psi.d
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
===DONE===
--EXPECT--
===TEST===
===DONE===
