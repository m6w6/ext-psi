--TEST--
getopt
--INI--
psi.directory={PWD}:{PWD}/../../psi.d
--SKIPIF--
<?php
extension_loaded("psi") or die("skip - need ext/psi");
PHP_OS === "Darwin" or die("skip - only for OSX");
function_exists("psi\\getopt") or die("skip - need psi\\getopt()");
?>
--ENV--
POSIXLY_CORRECT=
--FILE--
===TEST===
<?php

$args = [
	"progname", "huh", "-v", "-x", 1, "-s", "foo", "--", "-gotcha", "--bar", "baz"
];

$opts = "v::x:s:";

for ($i = 0; $i<3; ++$i) {
	psi\opterr(0);
	psi\optind\set(1);

	while (($opt = chr(psi\getopt($args, $opts)))) {
		switch ($opt) {
		case "v":
			printf("got v\n");
			break;
		case "x":
		case "s":
			printf("got %s: %s\n", $opt, psi\optarg());
			break;
		default:
			printf("error '%s'\n", $opt);
		case chr(-1):
			break 2;
		}
	}

	$pos = psi\optind\get();
	while ($pos < count($args)) {
		printf("arg: %s\n", $args[$pos++]);
	}
	psi\optreset();
}
var_dump($args);

?>
===DONE===
--EXPECT--
===TEST===
got v
got x: 1
got s: foo
arg: huh
arg: -gotcha
arg: --bar
arg: baz
got v
got x: 1
got s: foo
arg: huh
arg: -gotcha
arg: --bar
arg: baz
got v
got x: 1
got s: foo
arg: huh
arg: -gotcha
arg: --bar
arg: baz
array(11) {
  [0]=>
  string(8) "progname"
  [1]=>
  string(2) "-v"
  [2]=>
  string(2) "-x"
  [3]=>
  string(1) "1"
  [4]=>
  string(2) "-s"
  [5]=>
  string(3) "foo"
  [6]=>
  string(2) "--"
  [7]=>
  string(3) "huh"
  [8]=>
  string(7) "-gotcha"
  [9]=>
  string(5) "--bar"
  [10]=>
  string(3) "baz"
}
===DONE===
