<?php

$types = [
		"INT8" => "i8",
		"UINT8" => "u8",
		"INT16" => "i16", 
		"UINT16" => "u16",
		"INT32" => "i32", 
		"UINT32" => "u32",
		"INT64" => "i64", 
		"UINT64" => "u64",
];

printf("\tswitch (t1) { \\\n");
foreach ($types as $t1 => $f1) {
	$s1 = substr($f1, 1);
	$u1 = $f1{0} == "u";
	printf("\tcase PSI_T_%s: \\\n", $t1);
	printf("\t\tswitch (t2) { \\\n");
	foreach ($types as $t2 => $f2) {
		$s2 = substr($f2, 1);
		$u2 = $f2{0} == "u";
		
		if ($u1 && $u2)  {
			$fr = "u".min(64,max($s1*2,$s2*2));
		} else {
			$fr = "i".min(64,max($s1*2,$s2*2));
		}
		
		printf("\t\tcase PSI_T_%s:\tPSI_CALC_OP2(%s, %s, %s);\treturn PSI_T_%s; \\\n",
				$t2, $fr, $f1, $f2, str_replace(["u","i"], ["UINT","INT"], $fr));
	}
	printf("\t\tEMPTY_SWITCH_DEFAULT_CASE(); \\\n\t\t} \\\n\t\tbreak; \\\n");
}
printf("\tEMPTY_SWITCH_DEFAULT_CASE(); \\\n\t} \\\n");