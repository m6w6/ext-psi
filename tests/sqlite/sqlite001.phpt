--TEST--
sqlite3
--INI--
psi.directory={PWD}:{PWD}/../../psi.d
--SKIPIF--
<?php
extension_loaded("psi") or printf("%s\n", "skip - need ext/psi");
function_exists("sqlite3\\open") or printf("%s\n", "skip - need libsqlite3");
?>
--FILE--
===TEST===
<?php

var_dump(sqlite3\version());

copy(__DIR__."/sqlite001.db", __DIR__."/sqlite001.tmp");

$rc = sqlite3\open(__DIR__."/sqlite001.tmp", $db);
if ($rc) {
	printf("%s\n", sqlite3\errstr($rc));
}

function callback($context, int $argc, array $argv, array $cols) {
	$context->row = $context->row ?? 0;

	for ($i = 0; $i < $argc; ++$i) {
		printf("%d: %s = %s\n", $context->row, $cols[$i], $argv[$i] ?? "<NULL>");
	}
	printf("\n");
	++$context->row;
}

$rc = sqlite3\exec($db, "SELECT * FROM test", "callback", new stdClass, $error);
if ($rc) {
	printf("%s: '%s'\n", sqlite3\errstr($rc), $error);
}

$rc = sqlite3\exec($db, "INSERT INTO test VALUES (3,'three')", "callback", new stdClass, $error);
if ($rc) {
	printf("%s: '%s'\n", sqlite3\errstr($rc), $error);
}

$rc = sqlite3\exec($db, "SELECT * FROM test", "callback", new stdClass, $error);
if ($rc) {
	printf("%s: '%s'\n", sqlite3\errstr($rc), $error);
}

$rc = sqlite3\exec($db, "SELECT *", "callback", new stdClass, $error);
if ($rc) {
	printf("%s: '%s'\n", sqlite3\errstr($rc), $error);
}

sqlite3\close($db);

$rc = sqlite3\exec($db, "SELECT *", "callback", new stdClass, $error);
if ($rc) {
	printf("%s: '%s'\n", sqlite3\errstr($rc), $error);
}

?>
===DONE===
--EXPECTF--
===TEST===
string(%d) "3.%d.%s"
0: id = 1
0: data = one

1: id = 2
1: data = two

0: id = 1
0: data = one

1: id = 2
1: data = two

2: id = 3
2: data = three

SQL logic error or missing database: 'no tables specified'
library routine called out of sequence: ''
===DONE===
--CLEAN--
<?php
@unlink(__DIR__."/sqlite001.tmp");
?>
