// system fetch, tinyfetch killer
// macos or windows support will NEVER be a thing
// cucked systems will be rejected
// Benchmark 1: ./ohmyfetch
// Time (abs ≡):        473.2 µs               [User: 370.0 µs, System: 0.0 µs]

// i am not proficient in C, please excuse any skill issues.

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <string.h>

// avoiding stdio
static void print_cpu(void) {
    int fd = open("/proc/cpuinfo", O_RDONLY);
    if (fd < 0) return;

    char buf[4096];
    ssize_t n = read(fd, buf, sizeof buf);
    close(fd);
    if (n <= 0) return;

    const char key[] = "model name";
    void *hit = memmem(buf, (size_t)n, key, sizeof key - 1);
    if (!hit) return;

    char *p = strchr((char *)hit, ':');
    if (!p) return;
    while (*++p == ' ');

    char *eol = memchr(p, '\n', (buf + n) - p);
    if (eol) *eol = '\0';

    printf("cpu     : %.64s\n", p);
}

int main(void) {
    struct utsname un;
    uname(&un);

    struct sysinfo si;
    sysinfo(&si);

    printf("os      : %s\n", un.sysname);
    printf("kernel  : %s\n", un.release);
    printf("uptime  : %dm\n", (int)(si.uptime / 60));

    unsigned long total = si.totalram >> 20;
    unsigned long free  = si.freeram  >> 20;
    printf("memory  : %lu/%lumb\n", total - free, total);

    print_cpu();

    return 0;
}
