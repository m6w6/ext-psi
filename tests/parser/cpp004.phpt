--TEST--
CPP builtins
--SKIPIF--
<?php 
extension_loaded("psi") or die("skip - need ext/psi");
?>
--INI--
psi.directory={PWD}/cpp004
--ENV--
LC_TIME=C
--FILE--
===TEST===
<?php 
var_dump(CPP_TEST0, CPP_TEST1, CPP_TEST2, CPP_TEST3, CPP_TEST4, CPP_TEST5);
var_dump(base_file, include_level, timestamp, file, line, date, time);
?>
===DONE===
--EXPECTF--
===TEST===
int(0)
int(1)
int(2)
int(3003)
int(4004)
int(5005)
string(%d) "%s/tests/parser/cpp004/builtins.psi"
int(2)
string(24) "%s %s %w%d %d:%d:%d %d"
string(54) "/%s/tests/parser/cpp004/include_level.h"
int(3)
string(11) "%s %d %d"
string(8) "%d:%d:%d"
===DONE===
