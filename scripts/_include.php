<?php
ob_start(function($s) {
	return preg_replace("/(?<=[^ \t])[ \t]+\$/m", "", $s);
});

$types = [
		"INT8" => "i8",
		"UINT8" => "u8",
		"INT16" => "i16",
		"UINT16" => "u16",
		"INT32" => "i32",
		"UINT32" => "u32",
		"INT64" => "i64",
		"UINT64" => "u64",
		"INT128" => "i128",
		"UINT128" => "u128",
		"FLOAT" => "fval",
		"DOUBLE" => "dval",
		"LONG_DOUBLE" => "ldval",
];

function t_is_int($t) {
	switch ($t{0}) {
		case "U":
		case "I":
			return true;
		default:
			return false;
	}
}

function t_is_special($t) {
	switch ($t) {
		case "INT128":
		case "UINT128":
		case "LONG_DOUBLE":
			return true;
		default:
			return false;
	}
}

?>
/*******************************************************************************
 Copyright (c) 2016, Michael Wallner <mike@php.net>.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#include "php_psi_stdinc.h"
#include <assert.h>

#include "token.h"