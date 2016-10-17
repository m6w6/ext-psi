PSI_CHECK_NDBM() {
	PSI_CONFIG_POSIX(ndbm, ndbm.h)
	
	PHP_CHECK_FUNC_LIB(dbm_open, gdbm_compat)
	
	PSI_STRUCT(datum, [
		void *dptr,
		int dsize]
	)
	
	PSI_OPAQUE_TYPE(DBM)
	
	PSI_CONST(DBM_INSERT, int)
	PSI_CONST(DBM_REPLACE, int)
	
	PSI_DECL(void dbm_clearerr, [(DBM *db)])
	PSI_DECL(void dbm_close, [(DBM *db)])
	PSI_DECL(int dbm_delete, [(DBM *db, datum key)])
	PSI_DECL(int dbm_error, [(DBM *db)])
	PSI_DECL(datum dbm_fetch, [(DBM *db, datum key)])
	PSI_DECL(datum dbm_firstkey, [(DBM *db)])
	PSI_DECL(datum dbm_nextkey, [(DBM *db)])
	PSI_DECL(DBM *dbm_open, [(char *file, int open_flags, mode_t file_mode)])
	PSI_DECL(int dbm_store, [(DBM *db, datum key, datum content, int store_mode)])
}