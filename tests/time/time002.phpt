--TEST--
asctime/gmtime
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
?>
--ENV--
TZ=UTC
--INI--
psi.directory = {PWD}
--FILE--
===TEST===
<?php
var_dump(psi\asctime(NULL));
var_dump(psi\asctime(psi\gmtime(1234567890)));
?>
===DONE===
--EXPECT--
===TEST===
string(25) "Sun Jan  0 00:00:00 1900
"
string(25) "Fri Feb 13 23:31:30 2009
"
===DONE===
