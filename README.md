# Process Level Redundancy (PLR)
An Implementation of Software Transient Fault Tolerance (Detection & Recovery) through Process Level Redundancy (PLR)

More complete description TBD

## Limitations
* Only supports 3 redundant processes right now. 2 process (i.e. detection w/o recovery) mode will be forthcoming.
* Only supports single-threaded programs.
* Probably doesn't work right on programs that spawn children (i.e. fork()).
* Programs which make system calls directly (using 'int 0x80' or 'syscall') rather than passing through glibc will likely work incorrectly, or at best have incomplete protection. This is because syscalls are intercepted at the glibc level using LD_PRELOAD rather than hooking them in the kernel.
* Signals are not currently forwarded from the figurehead to the redundant processes.
* Redundant processes receiving signals at different times can lead to nondeterminism and issues, especially if a signal interrupts a syscall.

## Todo List
* Figure out how to emulate syscalls like read() or write()
  * For read(), should all processes call read() or just one and replicate the return value? For write(), only the latter option will work.
  * However, how will side effects of kernel data - like updating the file offset - be applied to all processes if syscall only called on one? Do the other processes have to lseek() instead of read()/write()?
* Use "inside PLR code" per-process flag to determine whether to inject faults
* Add better logging functionality to PLR. Use env var to set logging level.
* STDIN & STDOUT redirection between figurehead to/from redundant processes
* Clean up fault cases like multiple faulted processes to exit PLR gracefully

## Known Issues
