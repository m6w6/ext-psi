--TEST--
tzname
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
date.timezone=CET
--ENV--
TZ=CET
--FILE--
===TEST===
<?php
var_dump(psi\tzset(), psi\tzname());
?>
===DONE===
--EXPECTF--
===TEST===
NULL
array(2) {
  [0]=>
  string(3) "CET"
  [1]=>
  string(4) "CEST"
}
===DONE===
