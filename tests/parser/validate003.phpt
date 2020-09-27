--TEST--
validate types
--FILE--
===TEST===
<?php 

psi_validate_string("typedef long int;");
?>
===DONE===
--EXPECTF--
===TEST===

Warning: PSI syntax error, unexpected ;, expecting %s at col 17 in %s on line 1

Warning: PSI preceding token 'typedef' at col 1 in <stdin> on line 1

Warning: PSI preceding token 'long' at col 9 in <stdin> on line 1

Warning: PSI preceding token 'int' at col 14 in <stdin> on line 1

Warning: PSI offending token ';' at col 17 in <stdin> on line 1
===DONE===
