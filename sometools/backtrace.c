#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <ucontext.h>
#include <signal.h>
static void *getMcontextEip(ucontext_t *uc) {
#if defined(__FreeBSD__)
    return (void*) uc->uc_mcontext.mc_eip;
#elif defined(__dietlibc__)
    return (void*) uc->uc_mcontext.eip;
#elif defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_6)
  #if __x86_64__
    return (void*) uc->uc_mcontext->__ss.__rip;
  #elif __i386__
    return (void*) uc->uc_mcontext->__ss.__eip;
  #else
    return (void*) uc->uc_mcontext->__ss.__srr0;
  #endif
#elif defined(__APPLE__) && defined(MAC_OS_X_VERSION_10_6)
  #if defined(_STRUCT_X86_THREAD_STATE64) && !defined(__i386__)
    return (void*) uc->uc_mcontext->__ss.__rip;
  #else
    return (void*) uc->uc_mcontext->__ss.__eip;
  #endif
#elif defined(__i386__)
    return (void*) uc->uc_mcontext.gregs[14]; /* Linux 32 */
#elif defined(__X86_64__) || defined(__x86_64__)
    return (void*) uc->uc_mcontext.gregs[16]; /* Linux 64 */
#elif defined(__ia64__) /* Linux IA64 */
    return (void*) uc->uc_mcontext.sc_ip;
#else
    return NULL;
#endif
}
static void sigsegvHandler(int sig, siginfo_t *info, void *secret)
{
	ucontext_t *uc = (ucontext_t*)secret;
	void *trace[100];
	char **messages = NULL;
	int i, trace_size = 0;
	trace_size = backtrace(trace, 100);
	if (getMcontextEip(uc) != NULL) {
	trace[1] = getMcontextEip(uc);
	}
	messages = backtrace_symbols(trace, trace_size);
	for (i=1; i<trace_size; ++i)
		printf("%s\n", messages[i]);
}
void setupSignalHandlers(void) {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
    act.sa_sigaction = sigsegvHandler;
    sigaction(SIGSEGV, &act, NULL);
	sigaction(SIGBUS, &act, NULL);                                        
	sigaction(SIGFPE, &act, NULL);
	sigaction(SIGILL, &act, NULL);
}
void foo(void)
{
	kill(getpid(),SIGSEGV);
}
int main(int argc,char *argv[])
{
	setupSignalHandlers() ;
	foo();
	return 0;
}
