--TEST--
asctime/gmtime
--ENV--
TZ=UTC
--INI--
psi.directory = {PWD}/../../psi.d:{PWD}
--FILE--
===TEST===
<?php
try {
	var_dump(psi\asctime(NULL));
} catch (Throwable $t) {
	echo $t->getMessage(),"\n";
} 
var_dump(psi\gmtime(1));
var_dump(psi\asctime(psi\gmtime(1234567890)));
var_dump(psi\asctime_r(psi\gmtime_r(1234567890)));
?>
===DONE===
--EXPECT--
===TEST===
psi\asctime(): Argument #1 ($tm) must be of type array, null given
array(9) {
  ["tm_sec"]=>
  int(1)
  ["tm_min"]=>
  int(0)
  ["tm_hour"]=>
  int(0)
  ["tm_mday"]=>
  int(1)
  ["tm_mon"]=>
  int(0)
  ["tm_year"]=>
  int(70)
  ["tm_wday"]=>
  int(4)
  ["tm_yday"]=>
  int(0)
  ["tm_isdst"]=>
  int(0)
}
string(25) "Fri Feb 13 23:31:30 2009
"
string(25) "Fri Feb 13 23:31:30 2009
"
===DONE===
