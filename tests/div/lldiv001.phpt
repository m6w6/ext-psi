--TEST--
lldiv
--INI--
psi.directory={PWD}:{PWD}/../../psi.d
display_startup_errors=0
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
function_exists("psi\\lldiv") or die("skip - need psi\\lldiv()");
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
