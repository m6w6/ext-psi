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

static inline int psi_calc_oper(token_t op1, token_t op2)
{
	if (PSI_T_LPAREN == op2) {
		return -1;
	} else if (PSI_T_LPAREN == op1) {
		return 1;
	} else if (op1 == op2) {
		return 0;
	} else if (!op1 || op1 == PSI_T_NUMBER) {
		return 1;
	} else if (!op2 || op2 == PSI_T_NUMBER) {
		return -1;
	}

	switch (op1) {
	case PSI_T_NOT:
		switch (op2) {
		case PSI_T_NOT:
			return 0;
		case PSI_T_TILDE:
			return 0;
		case PSI_T_CAST:
			return 0;
		case PSI_T_ASTERISK:
			return -1;
		case PSI_T_SLASH:
			return -1;
		case PSI_T_MODULO:
			return -1;
		case PSI_T_PLUS:
			return -1;
		case PSI_T_MINUS:
			return -1;
		case PSI_T_LSHIFT:
			return -1;
		case PSI_T_RSHIFT:
			return -1;
		case PSI_T_LCHEVR:
			return -1;
		case PSI_T_CMP_LE:
			return -1;
		case PSI_T_RCHEVR:
			return -1;
		case PSI_T_CMP_GE:
			return -1;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_TILDE:
		switch (op2) {
		case PSI_T_NOT:
			return 0;
		case PSI_T_TILDE:
			return 0;
		case PSI_T_CAST:
			return 0;
		case PSI_T_ASTERISK:
			return -1;
		case PSI_T_SLASH:
			return -1;
		case PSI_T_MODULO:
			return -1;
		case PSI_T_PLUS:
			return -1;
		case PSI_T_MINUS:
			return -1;
		case PSI_T_LSHIFT:
			return -1;
		case PSI_T_RSHIFT:
			return -1;
		case PSI_T_LCHEVR:
			return -1;
		case PSI_T_CMP_LE:
			return -1;
		case PSI_T_RCHEVR:
			return -1;
		case PSI_T_CMP_GE:
			return -1;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_CAST:
		switch (op2) {
		case PSI_T_NOT:
			return 0;
		case PSI_T_TILDE:
			return 0;
		case PSI_T_CAST:
			return 0;
		case PSI_T_ASTERISK:
			return -1;
		case PSI_T_SLASH:
			return -1;
		case PSI_T_MODULO:
			return -1;
		case PSI_T_PLUS:
			return -1;
		case PSI_T_MINUS:
			return -1;
		case PSI_T_LSHIFT:
			return -1;
		case PSI_T_RSHIFT:
			return -1;
		case PSI_T_LCHEVR:
			return -1;
		case PSI_T_CMP_LE:
			return -1;
		case PSI_T_RCHEVR:
			return -1;
		case PSI_T_CMP_GE:
			return -1;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_ASTERISK:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 0;
		case PSI_T_SLASH:
			return 0;
		case PSI_T_MODULO:
			return 0;
		case PSI_T_PLUS:
			return -1;
		case PSI_T_MINUS:
			return -1;
		case PSI_T_LSHIFT:
			return -1;
		case PSI_T_RSHIFT:
			return -1;
		case PSI_T_LCHEVR:
			return -1;
		case PSI_T_CMP_LE:
			return -1;
		case PSI_T_RCHEVR:
			return -1;
		case PSI_T_CMP_GE:
			return -1;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_SLASH:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 0;
		case PSI_T_SLASH:
			return 0;
		case PSI_T_MODULO:
			return 0;
		case PSI_T_PLUS:
			return -1;
		case PSI_T_MINUS:
			return -1;
		case PSI_T_LSHIFT:
			return -1;
		case PSI_T_RSHIFT:
			return -1;
		case PSI_T_LCHEVR:
			return -1;
		case PSI_T_CMP_LE:
			return -1;
		case PSI_T_RCHEVR:
			return -1;
		case PSI_T_CMP_GE:
			return -1;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_MODULO:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 0;
		case PSI_T_SLASH:
			return 0;
		case PSI_T_MODULO:
			return 0;
		case PSI_T_PLUS:
			return -1;
		case PSI_T_MINUS:
			return -1;
		case PSI_T_LSHIFT:
			return -1;
		case PSI_T_RSHIFT:
			return -1;
		case PSI_T_LCHEVR:
			return -1;
		case PSI_T_CMP_LE:
			return -1;
		case PSI_T_RCHEVR:
			return -1;
		case PSI_T_CMP_GE:
			return -1;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_PLUS:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 0;
		case PSI_T_MINUS:
			return 0;
		case PSI_T_LSHIFT:
			return -1;
		case PSI_T_RSHIFT:
			return -1;
		case PSI_T_LCHEVR:
			return -1;
		case PSI_T_CMP_LE:
			return -1;
		case PSI_T_RCHEVR:
			return -1;
		case PSI_T_CMP_GE:
			return -1;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_MINUS:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 0;
		case PSI_T_MINUS:
			return 0;
		case PSI_T_LSHIFT:
			return -1;
		case PSI_T_RSHIFT:
			return -1;
		case PSI_T_LCHEVR:
			return -1;
		case PSI_T_CMP_LE:
			return -1;
		case PSI_T_RCHEVR:
			return -1;
		case PSI_T_CMP_GE:
			return -1;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_LSHIFT:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 0;
		case PSI_T_RSHIFT:
			return 0;
		case PSI_T_LCHEVR:
			return -1;
		case PSI_T_CMP_LE:
			return -1;
		case PSI_T_RCHEVR:
			return -1;
		case PSI_T_CMP_GE:
			return -1;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_RSHIFT:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 0;
		case PSI_T_RSHIFT:
			return 0;
		case PSI_T_LCHEVR:
			return -1;
		case PSI_T_CMP_LE:
			return -1;
		case PSI_T_RCHEVR:
			return -1;
		case PSI_T_CMP_GE:
			return -1;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_LCHEVR:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 0;
		case PSI_T_CMP_LE:
			return 0;
		case PSI_T_RCHEVR:
			return 0;
		case PSI_T_CMP_GE:
			return 0;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_CMP_LE:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 0;
		case PSI_T_CMP_LE:
			return 0;
		case PSI_T_RCHEVR:
			return 0;
		case PSI_T_CMP_GE:
			return 0;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_RCHEVR:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 0;
		case PSI_T_CMP_LE:
			return 0;
		case PSI_T_RCHEVR:
			return 0;
		case PSI_T_CMP_GE:
			return 0;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_CMP_GE:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 0;
		case PSI_T_CMP_LE:
			return 0;
		case PSI_T_RCHEVR:
			return 0;
		case PSI_T_CMP_GE:
			return 0;
		case PSI_T_AMPERSAND:
			return -1;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_AMPERSAND:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 1;
		case PSI_T_CMP_LE:
			return 1;
		case PSI_T_RCHEVR:
			return 1;
		case PSI_T_CMP_GE:
			return 1;
		case PSI_T_AMPERSAND:
			return 0;
		case PSI_T_CMP_EQ:
			return -1;
		case PSI_T_CMP_NE:
			return -1;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_CMP_EQ:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 1;
		case PSI_T_CMP_LE:
			return 1;
		case PSI_T_RCHEVR:
			return 1;
		case PSI_T_CMP_GE:
			return 1;
		case PSI_T_AMPERSAND:
			return 1;
		case PSI_T_CMP_EQ:
			return 0;
		case PSI_T_CMP_NE:
			return 0;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_CMP_NE:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 1;
		case PSI_T_CMP_LE:
			return 1;
		case PSI_T_RCHEVR:
			return 1;
		case PSI_T_CMP_GE:
			return 1;
		case PSI_T_AMPERSAND:
			return 1;
		case PSI_T_CMP_EQ:
			return 0;
		case PSI_T_CMP_NE:
			return 0;
		case PSI_T_CARET:
			return -1;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_CARET:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 1;
		case PSI_T_CMP_LE:
			return 1;
		case PSI_T_RCHEVR:
			return 1;
		case PSI_T_CMP_GE:
			return 1;
		case PSI_T_AMPERSAND:
			return 1;
		case PSI_T_CMP_EQ:
			return 1;
		case PSI_T_CMP_NE:
			return 1;
		case PSI_T_CARET:
			return 0;
		case PSI_T_PIPE:
			return -1;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_PIPE:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 1;
		case PSI_T_CMP_LE:
			return 1;
		case PSI_T_RCHEVR:
			return 1;
		case PSI_T_CMP_GE:
			return 1;
		case PSI_T_AMPERSAND:
			return 1;
		case PSI_T_CMP_EQ:
			return 1;
		case PSI_T_CMP_NE:
			return 1;
		case PSI_T_CARET:
			return 1;
		case PSI_T_PIPE:
			return 0;
		case PSI_T_AND:
			return -1;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_AND:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 1;
		case PSI_T_CMP_LE:
			return 1;
		case PSI_T_RCHEVR:
			return 1;
		case PSI_T_CMP_GE:
			return 1;
		case PSI_T_AMPERSAND:
			return 1;
		case PSI_T_CMP_EQ:
			return 1;
		case PSI_T_CMP_NE:
			return 1;
		case PSI_T_CARET:
			return 1;
		case PSI_T_PIPE:
			return 1;
		case PSI_T_AND:
			return 0;
		case PSI_T_OR:
			return -1;
		default:
			assert(0);
			break;
		}
		break;

	case PSI_T_OR:
		switch (op2) {
		case PSI_T_NOT:
			return 1;
		case PSI_T_TILDE:
			return 1;
		case PSI_T_CAST:
			return 1;
		case PSI_T_ASTERISK:
			return 1;
		case PSI_T_SLASH:
			return 1;
		case PSI_T_MODULO:
			return 1;
		case PSI_T_PLUS:
			return 1;
		case PSI_T_MINUS:
			return 1;
		case PSI_T_LSHIFT:
			return 1;
		case PSI_T_RSHIFT:
			return 1;
		case PSI_T_LCHEVR:
			return 1;
		case PSI_T_CMP_LE:
			return 1;
		case PSI_T_RCHEVR:
			return 1;
		case PSI_T_CMP_GE:
			return 1;
		case PSI_T_AMPERSAND:
			return 1;
		case PSI_T_CMP_EQ:
			return 1;
		case PSI_T_CMP_NE:
			return 1;
		case PSI_T_CARET:
			return 1;
		case PSI_T_PIPE:
			return 1;
		case PSI_T_AND:
			return 1;
		case PSI_T_OR:
			return 0;
		default:
			assert(0);
			break;
		}
		break;

	default:
		assert(0);
		break;
	}
	return 0;
}
