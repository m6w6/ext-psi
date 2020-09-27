--TEST--
inet_ntop/inet_pton
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--FILE--
===TEST===
<?php
var_dump(psi\inet_pton(psi\AF_INET, "127.1.1.1", $res));
var_dump(psi\inet_ntop(psi\AF_INET, $res));
?>
===DONE===
--EXPECT--
===TEST===
int(1)
string(9) "127.1.1.1"
===DONE===
