--TEST--
glob
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
PHP_OS === "Linux" or die("skip - only for Linux");
?>
--FILE--
===TEST===
<?php
chdir(__DIR__);
$glob = ["gl_offs" => 5];
var_dump(psi\glob("*.php{,t}", psi\GLOB_BRACE|psi\GLOB_DOOFFS, $glob));
var_dump($glob);
?>
===DONE===
--EXPECTF--
===TEST===
int(0)
array(4) {
  ["gl_pathc"]=>
  int(4)
  ["gl_offs"]=>
  int(5)
  ["gl_flags"]=>
  int(%d)
  ["gl_pathv"]=>
  array(9) {
    [0]=>
    string(0) ""
    [1]=>
    string(0) ""
    [2]=>
    string(0) ""
    [3]=>
    string(0) ""
    [4]=>
    string(0) ""
    [5]=>
    string(11) "glob002.php"
    [6]=>
    string(12) "glob001.phpt"
    [7]=>
    string(12) "glob002.phpt"
    [8]=>
    string(12) "glob003.phpt"
  }
}
===DONE===
