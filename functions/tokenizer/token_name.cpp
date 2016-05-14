#define	T_INCLUDE	257
#define	T_INCLUDE_ONCE	258
#define	T_EVAL	259
#define	T_REQUIRE	260
#define	T_REQUIRE_ONCE	261
#define	T_LOGICAL_OR	262
#define	T_LOGICAL_XOR	263
#define	T_LOGICAL_AND	264
#define	T_PRINT	265
#define	T_PLUS_EQUAL	266
#define	T_MINUS_EQUAL	267
#define	T_MUL_EQUAL	268
#define	T_DIV_EQUAL	269
#define	T_CONCAT_EQUAL	270
#define	T_MOD_EQUAL	271
#define	T_AND_EQUAL	272
#define	T_OR_EQUAL	273
#define	T_XOR_EQUAL	274
#define	T_SL_EQUAL	275
#define	T_SR_EQUAL	276
#define	T_BOOLEAN_OR	277
#define	T_BOOLEAN_AND	278
#define	T_IS_EQUAL	279
#define	T_IS_NOT_EQUAL	280
#define	T_IS_IDENTICAL	281
#define	T_IS_NOT_IDENTICAL	282
#define	T_IS_SMALLER_OR_EQUAL	283
#define	T_IS_GREATER_OR_EQUAL	284
#define	T_SL	285
#define	T_SR	286
#define	T_INC	287
#define	T_DEC	288
#define	T_INT_CAST	289
#define	T_DOUBLE_CAST	290
#define	T_STRING_CAST	291
#define	T_ARRAY_CAST	292
#define	T_OBJECT_CAST	293
#define	T_BOOL_CAST	294
#define	T_UNSET_CAST	295
#define	T_NEW	296
#define	T_EXIT	297
#define	T_IF	298
#define	T_ELSEIF	299
#define	T_ELSE	300
#define	T_ENDIF	301
#define	T_LNUMBER	302
#define	T_DNUMBER	303
#define	T_STRING	304
#define	T_STRING_VARNAME	305
#define	T_VARIABLE	306
#define	T_NUM_STRING	307
#define	T_INLINE_HTML	308
#define	T_CHARACTER	309
#define	T_BAD_CHARACTER	310
#define	T_ENCAPSED_AND_WHITESPACE	311
#define	T_CONSTANT_ENCAPSED_STRING	312
#define	T_ECHO	313
#define	T_DO	314
#define	T_WHILE	315
#define	T_ENDWHILE	316
#define	T_FOR	317
#define	T_ENDFOR	318
#define	T_FOREACH	319
#define	T_ENDFOREACH	320
#define	T_DECLARE	321
#define	T_ENDDECLARE	322
#define	T_AS	323
#define	T_SWITCH	324
#define	T_ENDSWITCH	325
#define	T_CASE	326
#define	T_DEFAULT	327
#define	T_BREAK	328
#define	T_CONTINUE	329
#define	T_OLD_FUNCTION	330
#define	T_FUNCTION	331
#define	T_CONST	332
#define	T_RETURN	333
#define	T_USE	334
#define	T_GLOBAL	335
#define	T_STATIC	336
#define	T_VAR	337
#define	T_UNSET	338
#define	T_ISSET	339
#define	T_EMPTY	340
#define	T_CLASS	341
#define	T_EXTENDS	342
#define	T_OBJECT_OPERATOR	343
#define	T_DOUBLE_ARROW	344
#define	T_LIST	345
#define	T_ARRAY	346
#define	T_CLASS_C	347
#define	T_FUNC_C	348
#define	T_LINE	349
#define	T_FILE	350
#define	T_COMMENT	351
#define	T_ML_COMMENT	352
#define	T_OPEN_TAG	353
#define	T_OPEN_TAG_WITH_ECHO	354
#define	T_CLOSE_TAG	355
#define	T_WHITESPACE	356
#define	T_START_HEREDOC	357
#define	T_END_HEREDOC	358
#define	T_DOLLAR_OPEN_CURLY_BRACES	359
#define	T_CURLY_OPEN	360
#define	T_PAAMAYIM_NEKUDOTAYIM	361
php_var token_name(php_var token)
{
	switch ((int)token) {
		case T_INCLUDE: return "T_INCLUDE";
		case T_INCLUDE_ONCE: return "T_INCLUDE_ONCE";
		case T_EVAL: return "T_EVAL";
		case T_REQUIRE: return "T_REQUIRE";
		case T_REQUIRE_ONCE: return "T_REQUIRE_ONCE";
		case T_LOGICAL_OR: return "T_LOGICAL_OR";
		case T_LOGICAL_XOR: return "T_LOGICAL_XOR";
		case T_LOGICAL_AND: return "T_LOGICAL_AND";
		case T_PRINT: return "T_PRINT";
		case T_PLUS_EQUAL: return "T_PLUS_EQUAL";
		case T_MINUS_EQUAL: return "T_MINUS_EQUAL";
		case T_MUL_EQUAL: return "T_MUL_EQUAL";
		case T_DIV_EQUAL: return "T_DIV_EQUAL";
		case T_CONCAT_EQUAL: return "T_CONCAT_EQUAL";
		case T_MOD_EQUAL: return "T_MOD_EQUAL";
		case T_AND_EQUAL: return "T_AND_EQUAL";
		case T_OR_EQUAL: return "T_OR_EQUAL";
		case T_XOR_EQUAL: return "T_XOR_EQUAL";
		case T_SL_EQUAL: return "T_SL_EQUAL";
		case T_SR_EQUAL: return "T_SR_EQUAL";
		case T_BOOLEAN_OR: return "T_BOOLEAN_OR";
		case T_BOOLEAN_AND: return "T_BOOLEAN_AND";
		case T_IS_EQUAL: return "T_IS_EQUAL";
		case T_IS_NOT_EQUAL: return "T_IS_NOT_EQUAL";
		case T_IS_IDENTICAL: return "T_IS_IDENTICAL";
		case T_IS_NOT_IDENTICAL: return "T_IS_NOT_IDENTICAL";
		case T_IS_SMALLER_OR_EQUAL: return "T_IS_SMALLER_OR_EQUAL";
		case T_IS_GREATER_OR_EQUAL: return "T_IS_GREATER_OR_EQUAL";
		case T_SL: return "T_SL";
		case T_SR: return "T_SR";
		case T_INC: return "T_INC";
		case T_DEC: return "T_DEC";
		case T_INT_CAST: return "T_INT_CAST";
		case T_DOUBLE_CAST: return "T_DOUBLE_CAST";
		case T_STRING_CAST: return "T_STRING_CAST";
		case T_ARRAY_CAST: return "T_ARRAY_CAST";
		case T_OBJECT_CAST: return "T_OBJECT_CAST";
		case T_BOOL_CAST: return "T_BOOL_CAST";
		case T_UNSET_CAST: return "T_UNSET_CAST";
		case T_NEW: return "T_NEW";
		case T_EXIT: return "T_EXIT";
		case T_IF: return "T_IF";
		case T_ELSEIF: return "T_ELSEIF";
		case T_ELSE: return "T_ELSE";
		case T_ENDIF: return "T_ENDIF";
		case T_LNUMBER: return "T_LNUMBER";
		case T_DNUMBER: return "T_DNUMBER";
		case T_STRING: return "T_STRING";
		case T_STRING_VARNAME: return "T_STRING_VARNAME";
		case T_VARIABLE: return "T_VARIABLE";
		case T_NUM_STRING: return "T_NUM_STRING";
		case T_INLINE_HTML: return "T_INLINE_HTML";
		case T_CHARACTER: return "T_CHARACTER";
		case T_BAD_CHARACTER: return "T_BAD_CHARACTER";
		case T_ENCAPSED_AND_WHITESPACE: return "T_ENCAPSED_AND_WHITESPACE";
		case T_CONSTANT_ENCAPSED_STRING: return "T_CONSTANT_ENCAPSED_STRING";
		case T_ECHO: return "T_ECHO";
		case T_DO: return "T_DO";
		case T_WHILE: return "T_WHILE";
		case T_ENDWHILE: return "T_ENDWHILE";
		case T_FOR: return "T_FOR";
		case T_ENDFOR: return "T_ENDFOR";
		case T_FOREACH: return "T_FOREACH";
		case T_ENDFOREACH: return "T_ENDFOREACH";
		case T_DECLARE: return "T_DECLARE";
		case T_ENDDECLARE: return "T_ENDDECLARE";
		case T_AS: return "T_AS";
		case T_SWITCH: return "T_SWITCH";
		case T_ENDSWITCH: return "T_ENDSWITCH";
		case T_CASE: return "T_CASE";
		case T_DEFAULT: return "T_DEFAULT";
		case T_BREAK: return "T_BREAK";
		case T_CONTINUE: return "T_CONTINUE";
		case T_OLD_FUNCTION: return "T_OLD_FUNCTION";
		case T_FUNCTION: return "T_FUNCTION";
		case T_CONST: return "T_CONST";
		case T_RETURN: return "T_RETURN";
		case T_USE: return "T_USE";
		case T_GLOBAL: return "T_GLOBAL";
		case T_STATIC: return "T_STATIC";
		case T_VAR: return "T_VAR";
		case T_UNSET: return "T_UNSET";
		case T_ISSET: return "T_ISSET";
		case T_EMPTY: return "T_EMPTY";
		case T_CLASS: return "T_CLASS";
		case T_EXTENDS: return "T_EXTENDS";
		case T_OBJECT_OPERATOR: return "T_OBJECT_OPERATOR";
		case T_DOUBLE_ARROW: return "T_DOUBLE_ARROW";
		case T_LIST: return "T_LIST";
		case T_ARRAY: return "T_ARRAY";
		case T_CLASS_C: return "T_CLASS_C";
		case T_FUNC_C: return "T_FUNC_C";
		case T_LINE: return "T_LINE";
		case T_FILE: return "T_FILE";
		case T_COMMENT: return "T_COMMENT";
		case T_ML_COMMENT: return "T_ML_COMMENT";
		case T_OPEN_TAG: return "T_OPEN_TAG";
		case T_OPEN_TAG_WITH_ECHO: return "T_OPEN_TAG_WITH_ECHO";
		case T_CLOSE_TAG: return "T_CLOSE_TAG";
		case T_WHITESPACE: return "T_WHITESPACE";
		case T_START_HEREDOC: return "T_START_HEREDOC";
		case T_END_HEREDOC: return "T_END_HEREDOC";
		case T_DOLLAR_OPEN_CURLY_BRACES: return "T_DOLLAR_OPEN_CURLY_BRACES";
		case T_CURLY_OPEN: return "T_CURLY_OPEN";
		case T_PAAMAYIM_NEKUDOTAYIM: return "T_DOUBLE_COLON";
	}
	return "UNKNOWN";
}