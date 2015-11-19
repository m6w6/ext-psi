--TEST--
stat
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--FILE--
===TEST===
<?php 
var_dump(psi\stat(__FILE__, $stat), $stat);
?>
===DONE===
--EXPECTF--
===TEST===
int(0)
array(13) {
  ["st_dev"]=>
  int(%d)
  ["st_ino"]=>
  int(%d)
  ["st_mode"]=>
  int(%d)
  ["st_nlink"]=>
  int(1)
  ["st_uid"]=>
  int(%d)
  ["st_gid"]=>
  int(%d)
  ["st_rdev"]=>
  int(%d)
  ["st_size"]=>
  int(76)
  ["st_atim"]=>
  array(2) {
    ["tv_sec"]=>
    int(1%d)
    ["tv_nsec"]=>
    int(%d)
  }
  ["st_mtim"]=>
  array(2) {
    ["tv_sec"]=>
    int(1%d)
    ["tv_nsec"]=>
    int(%d)
  }
  ["st_ctim"]=>
  array(2) {
    ["tv_sec"]=>
    int(1%d)
    ["tv_nsec"]=>
    int(%d)
  }
  ["st_blksize"]=>
  int(%d)
  ["st_blocks"]=>
  int(%d)
}
===DONE===