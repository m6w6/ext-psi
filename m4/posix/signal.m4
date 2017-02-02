PSI_CHECK_SIGNAL() {
	
	PSI_PTHREAD
	
	PSI_CONST(SIG_DFL, int)
	PSI_CONST(SIG_ERR, int)
	PSI_CONST(SIG_HOLD, int)
	PSI_CONST(SIG_IGN, int)
	
	PSI_CONST(SIGEV_NONE, int)
	PSI_CONST(SIGEV_SIGNAL, int)
	PSI_CONST(SIGEV_THREAD, int)
	
	PSI_MACRO(int SIGRTMIN)
	PSI_MACRO(int SIGRTMAX)
	PSI_MACRO(int RTSIG_MAX)
	
	PSI_CONST(SIGABRT, int)
	PSI_CONST(SIGALRM, int)
	PSI_CONST(SIGBUS, int)
	PSI_CONST(SIGCHLD, int)
	PSI_CONST(SIGCONT, int)
	PSI_CONST(SIGFPE, int)
	PSI_CONST(SIGHUP, int)
	PSI_CONST(SIGILL, int)
	PSI_CONST(SIGINT, int)
	PSI_CONST(SIGKILL, int)
	PSI_CONST(SIGPIPE, int)
	PSI_CONST(SIGQUIT, int)
	PSI_CONST(SIGSEGV, int)
	PSI_CONST(SIGSTOP, int)
	PSI_CONST(SIGTERM, int)
	PSI_CONST(SIGTSTP, int)
	PSI_CONST(SIGTTIN, int)
	PSI_CONST(SIGTTOU, int)
	PSI_CONST(SIGUSR1, int)
	PSI_CONST(SIGUSR2, int)
	PSI_CONST(SIGPOLL, int)
	PSI_CONST(SIGPROF, int)
	PSI_CONST(SIGSYS, int)
	PSI_CONST(SIGTRAP, int)
	PSI_CONST(SIGURG, int)
	PSI_CONST(SIGVTALRM, int)
	PSI_CONST(SIGXCPU, int)
	PSI_CONST(SIGXFSZ, int)

	PSI_MACRO(int SIG_BLOCK)
	PSI_MACRO(int SIG_UNBLOCK)
	PSI_MACRO(int SIG_SETMASK)
	
	PSI_CONST(SA_NOCLDSTOP, int)
	PSI_CONST(SA_ONSTACK, int)
	PSI_CONST(SA_RESETHAND, int)
	PSI_CONST(SA_RESTART, int)
	PSI_CONST(SA_SIGINFO, int)
	PSI_CONST(SA_NOCLDWAIT, int)
	PSI_CONST(SA_NODEFER, int)
	PSI_CONST(SS_ONSTACK, int)
	PSI_CONST(SS_DISABLE, int)
	PSI_CONST(MINSIGSTKSZ, int)
	PSI_CONST(SIGSTKSZ, int)

	PSI_CONST(ILL_ILLOPC, int)
	PSI_CONST(ILL_ILLOPN, int)
	PSI_CONST(ILL_ILLADR, int)
	PSI_CONST(ILL_ILLTRP, int)
	PSI_CONST(ILL_PRVOPC, int)
	PSI_CONST(ILL_PRVREG, int)
	PSI_CONST(ILL_COPROC, int)
	PSI_CONST(ILL_BADSTK, int)
	PSI_CONST(FPE_INTDIV, int)
	PSI_CONST(FPE_INTOVF, int)
	PSI_CONST(FPE_FLTDIV, int)
	PSI_CONST(FPE_FLTOVF, int)
	PSI_CONST(FPE_FLTUND, int)
	PSI_CONST(FPE_FLTRES, int)
	PSI_CONST(FPE_FLTINV, int)
	PSI_CONST(FPE_FLTSUB, int)
	PSI_CONST(SEGV_MAPERR, int)
	PSI_CONST(SEGV_ACCERR, int)
	PSI_CONST(BUS_ADRALN, int)
	PSI_CONST(BUS_ADRERR, int)
	PSI_CONST(BUS_OBJERR, int)
	PSI_CONST(TRAP_BRKPT, int)
	PSI_CONST(TRAP_TRACE, int)
	PSI_CONST(CLD_EXITED, int)
	PSI_CONST(CLD_KILLED, int)
	PSI_CONST(CLD_DUMPED, int)
	PSI_CONST(CLD_TRAPPED, int)
	PSI_CONST(CLD_STOPPED, int)
	PSI_CONST(CLD_CONTINUED, int)
	PSI_CONST(POLL_IN, int)
	PSI_CONST(POLL_OUT, int)
	PSI_CONST(POLL_MSG, int)
	PSI_CONST(POLL_ERR, int)
	PSI_CONST(POLL_PRI, int)
	PSI_CONST(POLL_HUP, int)
	PSI_CONST(SI_USER, int)
	PSI_CONST(SI_QUEUE, int)
	PSI_CONST(SI_TIMER, int)
	PSI_CONST(SI_ASYNCIO, int)
	PSI_CONST(SI_MESGQ, int)

	PSI_TYPE(sig_atomic_t, int)
	PSI_OPAQUE_TYPE(sigset_t)
	PSI_OPAQUE_TYPE(mcontext_t)
	
	PSI_UNION(union sigval, [
		int sival_int,
		void *sival_ptr]
	)
	
	PSI_STRUCT(struct sigevent, [
		int sigev_notify,
		int sigev_signo,
		union sigval sigev_value]
	)
	
	PSI_STRUCT(stack_t, [
		void *ss_sp,
		size_t ss_size,
		int ss_flags]
	)
	
	PSI_FUNCTOR_TYPE(void sighandler_t, [(int signo)])
	PSI_FUNCTOR_TYPE(void sigaction_t, [(int signo, siginfo_t *info, ucontext_t *context)])
	
	PSI_STRUCT(struct sigaction, [
		sighandler_t sa_handler,
		sigset_t sa_mask,
		int sa_flags,
		sigaction_t sa_sigaction]
	)
	
	PSI_STRUCT(ucontext_t, [
		ucontext_t *uc_link,
		sigset_t uc_sigmask,
		stack_t uc_stack,
		mcontext_t uc_mcontext]
	)
	
	PSI_STRUCT(siginfo_t, [
		int si_signo,
		int si_code,
		int si_errno,
		pid_t si_pid,
		uid_t si_uid,
		void *si_addr,
		int si_status,
		long si_band,
		union sigval si_value]
	)
	
	PSI_DECL(int kill, [(pid_t pid, int sig)])
	PSI_DECL(int killpg, [(pid_t pgrp, int sig)])
	PSI_DECL(void psiginfo, [(const siginfo_t *pinfo, const char *s)])
	PSI_DECL(void psignal, [(int sig, const char *s)])
	
	PSI_SH_TEST_POSIX_ENABLED(pthread, [
		PSI_DECL(int pthread_kill, [(pthread_t thread, int sig)])
		PSI_DECL(int pthread_sigmask, [(int how, const sigset_t *set, sigset_t *oldset)])
	])
	
	PSI_DECL(int raise, [(int sig)])
	PSI_DECL(int sigaction, [(int sig, struct sigaction *act, struct sigaction *oact)])
	PSI_DECL(int sigaddset, [(sigset_t * set, int signum)])
	PSI_DECL(int sigaltstack, [(const stack_t *ss, stack_t *oss)])
	PSI_DECL(int sigdelset, [(sigset_t *set, int signum)])
	PSI_DECL(int sigemptyset, [(sigset_t *set)])
	PSI_DECL(int sigfillset, [(sigset_t *set)])
	PSI_DECL(int sighold, [(int sig)])
	PSI_DECL(int sigignore, [(int sig)])
	PSI_DECL(int siginterrupt, [(int sig, int flag)])
	PSI_DECL(int sigismember, [(const sigset_t *set, int signum)])
	PSI_DECL(sighandler_t signal, [(int sig, sighandler_t func)])
	PSI_DECL(int sigpause, [(int sig)])
	PSI_DECL(int sigpending, [(sigset_t *set)])
	PSI_DECL(int sigprocmask, [(int how, const sigset_t *set, sigset_t *oset)])
	PSI_DECL(int sigqueue, [(pid_t pid, int sig, const union sigval value)])
	PSI_DECL(int sigrelse, [(int sig)])
	PSI_DECL(sighandler_t sigset, [(int sig, sighandler_t disp)])
	PSI_DECL(int sigsuspend, [(const sigset_t *sigmask)])
	PSI_DECL(int sigtimedwait, [(const sigset_t *set, siginfo_t *info, const struct timespec *timeout)])
	PSI_DECL(int sigwait, [(const sigset_t *set, int *sig)])
	PSI_DECL(int sigwaitinfo, [(const sigset_t *set, siginfo_t *info)])
}