--TEST--
glob err
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
is_dir("/etc/sudoers.d") and !is_readable("/etc/sudoers.d") or die("skip - only for Linux with unreadable sudoers.d");
?>
--FILE--
===TEST===
<?php
var_dump(psi\GLOB_ABORTED == psi\glob("/etc/sudoers.d/*", psi\GLOB_ERR, $glob, function($epath, $eerrno) {
	printf("%s: %s\n", psi\strerror($eerrno), $epath);
}));
var_dump($glob);

var_dump(psi\GLOB_ABORTED == psi\glob("/etc/sudoers.d/*", 0, $glob, function($epath, $eerrno) {
	printf("%s: %s\n", psi\strerror($eerrno), $epath);
	return 1;
}));
var_dump($glob);

var_dump(psi\GLOB_ABORTED == psi\glob("/etc/sudoers.d/*", 0, $glob, function($epath, $eerrno) {
	printf("%s: %s\n", psi\strerror($eerrno), $epath);
	return 0;
}));
var_dump($glob);
?>
===DONE===
--EXPECTF--
===TEST===
Permission denied: /etc/sudoers.d
bool(true)
array(4) {
  ["gl_pathc"]=>
  int(0)
  ["gl_offs"]=>
  int(0)
  ["gl_flags"]=>
  int(%d)
  ["gl_pathv"]=>
  array(0) {
  }
}
Permission denied: /etc/sudoers.d
bool(true)
array(4) {
  ["gl_pathc"]=>
  int(0)
  ["gl_offs"]=>
  int(0)
  ["gl_flags"]=>
  int(%d)
  ["gl_pathv"]=>
  array(0) {
  }
}
Permission denied: /etc/sudoers.d
bool(false)
array(4) {
  ["gl_pathc"]=>
  int(0)
  ["gl_offs"]=>
  int(0)
  ["gl_flags"]=>
  int(%d)
  ["gl_pathv"]=>
  array(0) {
  }
}
===DONE===
