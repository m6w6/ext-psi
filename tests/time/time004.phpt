--TEST--
times
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 
var_dump(psi\times($times), $times);
?>
===DONE===
--EXPECTF--
===TEST===
int(%d)
array(4) {
  ["tms_utime"]=>
  int(%d)
  ["tms_stime"]=>
  int(%d)
  ["tms_cutime"]=>
  int(%d)
  ["tms_cstime"]=>
  int(%d)
}
===DONE===
