--TEST--
iconv abstraction
--INI--
psi.directory={PWD}/../../psi.d:{PWD}
--FILE--
===TEST===
<?php 

class iconv_stream {
	private $cd;
	
	function __construct($from, $to) {
		if (!$this->cd = psi\iconv_open($to, $from)) {
			throw new Exception(psi\strerror(psi\errno()));
		}
	}
	
	function __destruct() {
		psi\iconv_close($this->cd);
	}
	
	function update(string $data) : string {
		if (0 > psi\iconv($this->cd, $data, $result)) {
			throw new Exception(psi\strerror(psi\errno()));
		}
		return $result;
	}
}

$ic = new iconv_stream("utf8", "latin1");

foreach (["föö", "bää", "baßß"] as $str) {
	var_dump(array_map("ord", str_split($ic->update($str))));
}

$bc = new iconv_stream("latin1", "utf8");
foreach (["föö", "bää", "baßß"] as $str) {
	var_dump($bc->update($ic->update($str)));
}

?>
===DONE===
--EXPECT--
===TEST===
array(3) {
  [0]=>
  int(102)
  [1]=>
  int(246)
  [2]=>
  int(246)
}
array(3) {
  [0]=>
  int(98)
  [1]=>
  int(228)
  [2]=>
  int(228)
}
array(4) {
  [0]=>
  int(98)
  [1]=>
  int(97)
  [2]=>
  int(223)
  [3]=>
  int(223)
}
string(5) "föö"
string(5) "bää"
string(6) "baßß"
===DONE===
