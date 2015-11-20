--TEST--
gettimeofday
--INI--
psi.directory = {PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
?>
--ENV--
TZ=UTC
--FILE--
===TEST===
<?php

var_dump($ar = gettimeofday());

var_dump(psi\gettimeofday());
var_dump(psi\gettimeofday($tv), $tv);
var_dump(psi\gettimeofday($tv, $tz), $tv, $tz);

var_dump(abs($ar["sec"] - $tv["tv_sec"]) <= 1);

?>
===DONE===
--EXPECTF--
===TEST===
array(4) {
  ["sec"]=>
  int(1%d)
  ["usec"]=>
  int(%d)
  ["minuteswest"]=>
  int(%i)
  ["dsttime"]=>
  int(%i)
}
int(0)
int(0)
array(2) {
  ["tv_sec"]=>
  int(1%d)
  ["tv_usec"]=>
  int(%d)
}
int(0)
array(2) {
  ["tv_sec"]=>
  int(1%d)
  ["tv_usec"]=>
  int(%d)
}
array(2) {
  ["tz_minuteswest"]=>
  int(%i)
  ["tz_dsttime"]=>
  int(%i)
}
bool(true)
===DONE===
