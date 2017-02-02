PSI_CHECK_LOCALE() {
	PSI_STRUCT(struct lconv, [
		char    *currency_symbol,
		char    *decimal_point,
		char     frac_digits,
		char    *grouping,
		char    *int_curr_symbol,
		char     int_frac_digits,
		char     int_n_cs_precedes,
		char     int_n_sep_by_space,
		char     int_n_sign_posn,
		char     int_p_cs_precedes,
		char     int_p_sep_by_space,
		char     int_p_sign_posn,
		char    *mon_decimal_point,
		char    *mon_grouping,
		char    *mon_thousands_sep,
		char    *negative_sign,
		char     n_cs_precedes,
		char     n_sep_by_space,
		char     n_sign_posn,
		char    *positive_sign,
		char     p_cs_precedes,
		char     p_sep_by_space,
		char     p_sign_posn,
		char    *thousands_sep])

	PSI_CONST(LC_ALL, int)
	PSI_CONST(LC_COLLATE, int)
	PSI_CONST(LC_CTYPE, int)
	PSI_CONST(LC_MESSAGES, int)
	PSI_CONST(LC_MONETARY, int)
	PSI_CONST(LC_NUMERIC, int)
	PSI_CONST(LC_TIME, int)

	PSI_CONST(LC_COLLATE_MASK, int)
	PSI_CONST(LC_CTYPE_MASK, int)
	PSI_CONST(LC_MESSAGES_MASK, int)
	PSI_CONST(LC_MONETARY_MASK, int)
	PSI_CONST(LC_NUMERIC_MASK, int)
	PSI_CONST(LC_TIME_MASK, int)
	PSI_CONST(LC_ALL_MASK, int)

	PSI_MACRO(locale_t LC_GLOBAL_LOCALE)

	PSI_OPAQUE_TYPE(locale_t)

	PSI_DECL(locale_t duplocale, [(locale_t loc)])
	PSI_DECL(void freelocale, [(locale_t loc)])
	PSI_DECL(struct lconv *localeconv, [(void)])
	PSI_DECL(locale_t newlocale, [(int mask, const char *locale, locale_t base)])
	PSI_DECL(char *setlocale, [(int category, const char *locale)])
	PSI_DECL(locale_t uselocale, [(locale_t loc)])
}
