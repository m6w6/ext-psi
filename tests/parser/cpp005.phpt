--TEST--
CPP expansion
--INI--
psi.directory={PWD}/cpp005
--FILE--
===TEST===
<?php 
?>
===DONE===
--EXPECTF--
Warning: PSI syntax error, unexpected NUMBER, expecting ) or "," at col 11 in %stests/parser/cpp005/expansion.psi on line 2

Warning: PSI preceding token 'bar' at col 1 in %stests/parser/cpp005/expansion.psi on line 2

Warning: PSI preceding token 'foo' at col 1 in %stests/parser/cpp005/expansion.psi on line 2

Warning: PSI preceding token '(' at col 10 in %stests/parser/cpp005/expansion.psi on line 2

Warning: PSI offending token '2' at col 11 in %stests/parser/cpp005/expansion.psi on line 2

Warning: PSI following token ')' at col 12 in %stests/parser/cpp005/expansion.psi on line 2
===TEST===
===DONE===
