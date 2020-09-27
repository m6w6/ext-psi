--TEST--
pipe
--INI--
psi.directory={PWD}
--FILE--
===TEST===
<?php 

var_dump(pipe($pipes));
$r = fopen("php://fd/".$pipes[0], "r");
$w = fopen("php://fd/".$pipes[1], "w");

fputs($w, "Hello World!\n");
var_dump(fgets($r));

?>
===DONE===
--EXPECT--
===TEST===
int(0)
string(13) "Hello World!
"
===DONE===