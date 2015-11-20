--TEST--
glob
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
PHP_OS === "Darwin" or die("skip - only for OSX");
?>
--FILE--
===TEST===
<?php
chdir(__DIR__);
$glob = ["gl_offs" => 3];
var_dump(psi\glob("*.php{,t}", psi\GLOB_BRACE|psi\GLOB_DOOFFS, $glob));
var_dump($glob);
?>
===DONE===
--EXPECTF--
===TEST===
int(0)
array(5) {
  ["gl_matchc"]=>
  int(4)
  ["gl_pathc"]=>
  int(4)
  ["gl_offs"]=>
  int(3)
  ["gl_flags"]=>
  int(386)
  ["gl_pathv"]=>
  array(7) {
    [0]=>
    string(0) ""
    [1]=>
    string(0) ""
    [2]=>
    string(0) ""
    [3]=>
    string(11) "glob003.php"
    [4]=>
    string(12) "glob001.phpt"
    [5]=>
    string(12) "glob002.phpt"
    [6]=>
    string(12) "glob003.phpt"
  }
}
===DONE===
