// ******************************************************************
//  QtMips emulator https://github.com/cvut/QtMips support filees
//
//  qtmips_unistd.h  - definition of the QtMips syscall numbers
//
//  (C) Copyright 2019 - 2020 by Pavel Pisa
//      e-mail:   pisa@cmp.felk.cvut.cz
//      homepage: http://cmp.felk.cvut.cz/~pisa
//      license:  any combination of GPL, LGPL, MPL or BSD licenses
//
// ******************************************************************

#ifndef QTMIPS_UNISTD_H
#define QTMIPS_UNISTD_H

// Linux kernel compatible system calls subset

#define __NR_exit     4001	// void exit(int status)
#define __NR_read     4003	// ssize_t read(int fd, void *buf, size_t count)
#define __NR_write    4004	// ssize_t write(int fd, const void *buf, size_t count)
#define __NR_close    4006	// int close(int fd)
#define __NR_open     4005	// int open(const char *pathname, int flags, mode_t mode)
#define __NR_brk      4045	// void * brk(void *addr)
#define __NR_truncate 4092	// int ftruncate(int fd, off_t length)
#define __NR_readv    4145	// ssize_t readv(int fd, const struct iovec *iov, int iovcnt)
#define __NR_writev   4146	// ssize_t writev(int fd, const struct iovec *iov, int iovcnt)
#define __NR_set_thread_area 4283 // int set_thread_area(unsigned long addr)

#endif /*QTMIPS_UNISTD_H*/
