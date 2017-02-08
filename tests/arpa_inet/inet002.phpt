--TEST--
inet_addr/inet_ntoa
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--FILE--
===TEST===
<?php
var_dump(psi\inet_ntoa(["s_addr" => psi\inet_addr("217.0.0.1")]));
?>
===DONE===
--EXPECT--
===TEST===
string(9) "217.0.0.1"
===DONE===
