#ifndef LIBC_FUNC_H
#define LIBC_FUNC_H
#ifdef __cplusplus
extern "C" {
#endif

void *get_libc_func(const char *funcName, void **offset);

// This handy trick of using a macro to acquire the libc function pointer
// for use with LD_PRELOAD is based on code from libumockdev-preload.c at 
// https://github.com/martinpitt/umockdev/
#define libc_func(name, rettype, ...)			            \
    static rettype (*_ ## name) (__VA_ARGS__) = NULL;	\
    static void *_off_ ## name = NULL;        \
    if (_ ## name == NULL)				                    \
        _ ## name = get_libc_func(#name, &_off_ ## name);

#ifdef __cplusplus
}
#endif
#endif