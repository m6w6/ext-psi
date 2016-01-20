--TEST--
lldiv
--INI--
psi.directory={PWD}:{PWD}/../../psi.d
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php
var_dump(psi\lldiv(1000,10));
?>
===DONE===
--EXPECT--
===TEST===
array(2) {
  ["quot"]=>
  int(100)
  ["rem"]=>
  int(0)
}
===DONE===
