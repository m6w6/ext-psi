--TEST--
nanosleep
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
?>
--ENV--
TZ=UTC
--INI--
psi.directory = {PWD}/../../psi.d:{PWD}
--FILE--
===TEST===
<?php
var_dump(psi\gettimeofday($tv1), $tv1);
var_dump(psi\nanosleep(["tv_nsec" => 10000000], $rm), $rm);
var_dump(psi\gettimeofday($tv2), $tv2);
var_dump($tv2["tv_usec"]-$tv1["tv_usec"]);
?>
===DONE===
--EXPECTF--
===TEST===
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
  int(0)
  ["tv_nsec"]=>
  int(0)
}
int(0)
array(2) {
  ["tv_sec"]=>
  int(%d)
  ["tv_usec"]=>
  int(%d)
}
int(%r\d\d\d\d\d%r)
===DONE===
