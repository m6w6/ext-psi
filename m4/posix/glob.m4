PSI_CHECK_GLOB() {
    
    PSI_STRUCT(glob_t, [
        size_t gl_pathc,
        int gl_matchc,
        size_t gl_offs,
        int gl_flags,
        char **gl_pathv])

	PSI_FUNCTOR_TYPE(int glob_err, [(const char *epath, int eerrno)])
    PSI_DECL(int glob, [(char *path, int flags, glob_err err, glob_t *buf)])
    PSI_DECL(void globfree, [(glob_t *buf)])

    PSI_CONST(GLOB_APPEND, int)
    PSI_CONST(GLOB_BRACE, int)
    PSI_CONST(GLOB_DOOFFS, int)
    PSI_CONST(GLOB_ERR, int)
    PSI_CONST(GLOB_MARK, int)
    PSI_CONST(GLOB_NOCHECK, int)
    PSI_CONST(GLOB_NOESCAPE, int)
    PSI_CONST(GLOB_NOMAGIC, int)
    PSI_CONST(GLOB_NOSORT, int)
    PSI_CONST(GLOB_ONLYDIR, int)
    PSI_CONST(GLOB_PERIOD, int)
    PSI_CONST(GLOB_TILDE, int)
    PSI_CONST(GLOB_TILDE_CHECK, int)
    PSI_CONST(GLOB_ABORTED, int)
    PSI_CONST(GLOB_NOMATCH, int)
    PSI_CONST(GLOB_NOSPACE, int)
}
