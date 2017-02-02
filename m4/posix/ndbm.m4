PSI_CHECK_NDBM() {

	PSI_STRUCT(datum, [
		void *dptr,
		int dsize]
	)

	PSI_OPAQUE_TYPE(DBM)

	PSI_CONST(DBM_INSERT, int)
	PSI_CONST(DBM_REPLACE, int)

	PSI_DECL(void dbm_clearerr, [(DBM *db)], [], [-lqdbm -lgdbm_compat])
	PSI_DECL(void dbm_close, [(DBM *db)], [], [-lqdbm -lgdbm_compat])
	PSI_DECL(int dbm_delete, [(DBM *db, datum key)], [], [-lqdbm -lgdbm_compat])
	PSI_DECL(int dbm_error, [(DBM *db)], [], [-lqdbm -lgdbm_compat])
	PSI_DECL(datum dbm_fetch, [(DBM *db, datum key)], [], [-lqdbm -lgdbm_compat])
	PSI_DECL(datum dbm_firstkey, [(DBM *db)], [], [-lqdbm -lgdbm_compat])
	PSI_DECL(datum dbm_nextkey, [(DBM *db)], [], [-lqdbm -lgdbm_compat])
	PSI_DECL(DBM *dbm_open, [(char *file, int open_flags, mode_t file_mode)], [], [-lqdbm -lgdbm_compat])
	PSI_DECL(int dbm_store, [(DBM *db, datum key, datum content, int store_mode)], [], [-lqdbm -lgdbm_compat])

	# See http://www.gnu.org.ua/software/gdbm/manual/html_section/gdbm_19.html
	if expr X"$LIBS" : "X.*-lgdbm_compat" >/dev/null; then
		LIBS="-lgdbm $LIBS"
	fi
}