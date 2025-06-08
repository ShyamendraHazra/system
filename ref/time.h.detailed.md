# Complete C time.h Library Documentation

## Table of Contents
1. [Data Types and Structures](#data-types-and-structures)
2. [Macros and Constants](#macros-and-constants)
3. [Basic Time Functions](#basic-time-functions)
4. [Time Conversion Functions](#time-conversion-functions)
5. [Time Formatting Functions](#time-formatting-functions)
6. [Thread-Safe Functions](#thread-safe-functions)
7. [High-Resolution Time Functions](#high-resolution-time-functions)
8. [Clock Functions](#clock-functions)
9. [Timer Functions](#timer-functions)
10. [Parsing Functions](#parsing-functions)
11. [Utility Functions](#utility-functions)
12. [Complete Example Program](#complete-example-program)

---

## Data Types and Structures

### `time_t`
```c
typedef long time_t;  // Usually long int, represents seconds since epoch
```

### `clock_t`
```c
typedef long clock_t; // Usually long int, represents processor time
```

### `clockid_t`
```c
typedef int clockid_t; // Clock identifier type (POSIX)
```

### `timer_t`
```c
typedef void* timer_t; // Timer identifier type (POSIX)
```

### `struct tm`
```c
struct tm {
    int tm_sec;   // seconds (0-60, 60 for leap second)
    int tm_min;   // minutes (0-59)
    int tm_hour;  // hours (0-23)
    int tm_mday;  // day of month (1-31)
    int tm_mon;   // month (0-11, 0=January)
    int tm_year;  // year since 1900
    int tm_wday;  // day of week (0-6, 0=Sunday)
    int tm_yday;  // day of year (0-365)
    int tm_isdst; // daylight saving time flag
};
```

### `struct timespec` (C11/POSIX)
```c
struct timespec {
    time_t tv_sec;  // seconds
    long tv_nsec;   // nanoseconds
};
```

### `struct itimerspec` (POSIX)
```c
struct itimerspec {
    struct timespec it_interval; // timer period
    struct timespec it_value;    // timer expiration
};
```

---

## Macros and Constants

### Basic Constants
```c
#define CLOCKS_PER_SEC 1000000  // Number of clock ticks per second
#define NULL ((void*)0)         // Null pointer constant
```

### Time Base Constants (C11)
```c
#define TIME_UTC 1              // UTC time base for timespec_get
```

### Clock IDs (POSIX)
```c
#define CLOCK_REALTIME           0  // System-wide realtime clock
#define CLOCK_MONOTONIC          1  // Clock that cannot be set
#define CLOCK_PROCESS_CPUTIME_ID 2  // High-resolution per-process timer
#define CLOCK_THREAD_CPUTIME_ID  3  // Thread-specific CPU-time clock
```

---

## Basic Time Functions

### 1. `clock()`
**Prototype:** `clock_t clock(void);`
**Description:** Returns processor time used by the program
**Return:** Number of clock ticks, or -1 on error

```c
#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();
    
    // Some computation
    for(int i = 0; i < 1000000; i++);
    
    clock_t end = clock();
    
    printf("clock() start: %ld\n", start);
    printf("clock() end: %ld\n", end);
    printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
    printf("CPU time used: %f seconds\n", 
           ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}
```

### 2. `time()`
**Prototype:** `time_t time(time_t *timer);`
**Description:** Returns current calendar time
**Return:** Seconds since epoch (Jan 1, 1970), or -1 on error

```c
#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time;
    time_t result = time(&current_time);
    
    printf("time() return value: %ld\n", result);
    printf("time() via parameter: %ld\n", current_time);
    
    // Alternative usage
    time_t direct_time = time(NULL);
    printf("time(NULL): %ld\n", direct_time);
    return 0;
}
```

### 3. `difftime()`
**Prototype:** `double difftime(time_t time1, time_t time0);`
**Description:** Calculates difference between two times
**Return:** Difference in seconds as double

```c
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    time_t start = time(NULL);
    sleep(3);
    time_t end = time(NULL);
    
    double diff = difftime(end, start);
    printf("difftime() result: %f seconds\n", diff);
    printf("difftime() as integer: %.0f seconds\n", diff);
    return 0;
}
```

---

## Time Conversion Functions

### 4. `gmtime()`
**Prototype:** `struct tm *gmtime(const time_t *timer);`
**Description:** Converts time_t to struct tm in UTC
**Return:** Pointer to struct tm, or NULL on error

```c
#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time = time(NULL);
    struct tm *utc_time = gmtime(&current_time);
    
    if (utc_time != NULL) {
        printf("gmtime() result:\n");
        printf("  Year: %d\n", utc_time->tm_year + 1900);
        printf("  Month: %d\n", utc_time->tm_mon + 1);
        printf("  Day: %d\n", utc_time->tm_mday);
        printf("  Hour: %d\n", utc_time->tm_hour);
        printf("  Minute: %d\n", utc_time->tm_min);
        printf("  Second: %d\n", utc_time->tm_sec);
        printf("  Day of week: %d\n", utc_time->tm_wday);
        printf("  Day of year: %d\n", utc_time->tm_yday);
        printf("  DST flag: %d\n", utc_time->tm_isdst);
    } else {
        printf("gmtime() returned NULL\n");
    }
    return 0;
}
```

### 5. `localtime()`
**Prototype:** `struct tm *localtime(const time_t *timer);`
**Description:** Converts time_t to struct tm in local time
**Return:** Pointer to struct tm, or NULL on error

```c
#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    
    if (local_time != NULL) {
        printf("localtime() result:\n");
        printf("  Year: %d\n", local_time->tm_year + 1900);
        printf("  Month: %d\n", local_time->tm_mon + 1);
        printf("  Day: %d\n", local_time->tm_mday);
        printf("  Hour: %d\n", local_time->tm_hour);
        printf("  Minute: %d\n", local_time->tm_min);
        printf("  Second: %d\n", local_time->tm_sec);
        printf("  Day of week: %d\n", local_time->tm_wday);
        printf("  Day of year: %d\n", local_time->tm_yday);
        printf("  DST flag: %d\n", local_time->tm_isdst);
    } else {
        printf("localtime() returned NULL\n");
    }
    return 0;
}
```

### 6. `mktime()`
**Prototype:** `time_t mktime(struct tm *timeptr);`
**Description:** Converts struct tm to time_t
**Return:** time_t value, or -1 on error

```c
#include <stdio.h>
#include <time.h>

int main() {
    struct tm custom_time = {0};
    custom_time.tm_year = 2024 - 1900;
    custom_time.tm_mon = 11;
    custom_time.tm_mday = 25;
    custom_time.tm_hour = 12;
    custom_time.tm_min = 30;
    custom_time.tm_sec = 45;
    custom_time.tm_isdst = -1;
    
    time_t result = mktime(&custom_time);
    
    printf("mktime() input: %d-%02d-%02d %02d:%02d:%02d\n",
           2024, 12, 25, 12, 30, 45);
    
    if (result != -1) {
        printf("mktime() result: %ld\n", result);
        printf("Normalized day of week: %d\n", custom_time.tm_wday);
        printf("Normalized day of year: %d\n", custom_time.tm_yday);
    } else {
        printf("mktime() returned -1 (error)\n");
    }
    return 0;
}
```

---

## Time Formatting Functions

### 7. `asctime()`
**Prototype:** `char *asctime(const struct tm *timeptr);`
**Description:** Converts struct tm to string representation
**Return:** Pointer to static string, or NULL on error

```c
#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    
    char *time_string = asctime(local_time);
    
    if (time_string != NULL) {
        printf("asctime() result: %s", time_string);
        printf("asctime() string length: %lu\n", strlen(time_string));
    } else {
        printf("asctime() returned NULL\n");
    }
    return 0;
}
```

### 8. `ctime()`
**Prototype:** `char *ctime(const time_t *timer);`
**Description:** Converts time_t to string representation
**Return:** Pointer to static string, or NULL on error

```c
#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
    time_t current_time = time(NULL);
    char *time_string = ctime(&current_time);
    
    if (time_string != NULL) {
        printf("ctime() result: %s", time_string);
        printf("ctime() without newline: %.24s\n", time_string);
        printf("ctime() string length: %lu\n", strlen(time_string));
    } else {
        printf("ctime() returned NULL\n");
    }
    return 0;
}
```

### 9. `strftime()`
**Prototype:** `size_t strftime(char *s, size_t maxsize, const char *format, const struct tm *timeptr);`
**Description:** Formats time according to format specifiers
**Return:** Number of characters written (excluding null terminator), or 0 on error

```c
#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    char buffer[200];
    
    size_t result1 = strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_time);
    printf("strftime() ISO: %s (returned: %zu)\n", buffer, result1);
    
    size_t result2 = strftime(buffer, sizeof(buffer), "%A, %B %d, %Y", local_time);
    printf("strftime() long: %s (returned: %zu)\n", buffer, result2);
    
    size_t result3 = strftime(buffer, sizeof(buffer), "%I:%M %p", local_time);
    printf("strftime() 12-hour: %s (returned: %zu)\n", buffer, result3);
    
    // Test with small buffer
    char small_buffer[5];
    size_t result4 = strftime(small_buffer, sizeof(small_buffer), "%Y-%m-%d", local_time);
    printf("strftime() small buffer result: %zu\n", result4);
    
    return 0;
}
```

---

## Thread-Safe Functions

### 10. `gmtime_r()` (POSIX)
**Prototype:** `struct tm *gmtime_r(const time_t *timer, struct tm *result);`
**Description:** Thread-safe version of gmtime()
**Return:** Pointer to result on success, NULL on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time = time(NULL);
    struct tm result;
    struct tm *utc_time = gmtime_r(&current_time, &result);
    
    if (utc_time != NULL) {
        printf("gmtime_r() success:\n");
        printf("  Year: %d\n", result.tm_year + 1900);
        printf("  Month: %d\n", result.tm_mon + 1);
        printf("  Day: %d\n", result.tm_mday);
        printf("  Hour: %d\n", result.tm_hour);
        printf("  Returned pointer == &result: %s\n", 
               (utc_time == &result) ? "true" : "false");
    } else {
        printf("gmtime_r() returned NULL\n");
    }
    return 0;
}
```

### 11. `localtime_r()` (POSIX)
**Prototype:** `struct tm *localtime_r(const time_t *timer, struct tm *result);`
**Description:** Thread-safe version of localtime()
**Return:** Pointer to result on success, NULL on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>

int main() {
    time_t current_time = time(NULL);
    struct tm result;
    struct tm *local_time = localtime_r(&current_time, &result);
    
    if (local_time != NULL) {
        printf("localtime_r() success:\n");
        printf("  Year: %d\n", result.tm_year + 1900);
        printf("  Month: %d\n", result.tm_mon + 1);
        printf("  Day: %d\n", result.tm_mday);
        printf("  Hour: %d\n", result.tm_hour);
        printf("  Returned pointer == &result: %s\n", 
               (local_time == &result) ? "true" : "false");
    } else {
        printf("localtime_r() returned NULL\n");
    }
    return 0;
}
```

### 12. `asctime_r()` (POSIX)
**Prototype:** `char *asctime_r(const struct tm *timeptr, char *buf);`
**Description:** Thread-safe version of asctime()
**Return:** Pointer to buf on success, NULL on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
    time_t current_time = time(NULL);
    struct tm local_time;
    localtime_r(&current_time, &local_time);
    
    char buffer[26];  // asctime format is exactly 26 characters
    char *result = asctime_r(&local_time, buffer);
    
    if (result != NULL) {
        printf("asctime_r() result: %s", buffer);
        printf("asctime_r() length: %lu\n", strlen(buffer));
        printf("Returned pointer == buffer: %s\n", 
               (result == buffer) ? "true" : "false");
    } else {
        printf("asctime_r() returned NULL\n");
    }
    return 0;
}
```

### 13. `ctime_r()` (POSIX)
**Prototype:** `char *ctime_r(const time_t *timer, char *buf);`
**Description:** Thread-safe version of ctime()
**Return:** Pointer to buf on success, NULL on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
    time_t current_time = time(NULL);
    char buffer[26];
    char *result = ctime_r(&current_time, buffer);
    
    if (result != NULL) {
        printf("ctime_r() result: %s", buffer);
        printf("ctime_r() length: %lu\n", strlen(buffer));
        printf("Returned pointer == buffer: %s\n", 
               (result == buffer) ? "true" : "false");
    } else {
        printf("ctime_r() returned NULL\n");
    }
    return 0;
}
```

---

## High-Resolution Time Functions

### 14. `timespec_get()` (C11)
**Prototype:** `int timespec_get(struct timespec *ts, int base);`
**Description:** Gets current time with nanosecond precision
**Return:** base value on success, 0 on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>

int main() {
    struct timespec ts;
    int result = timespec_get(&ts, TIME_UTC);
    
    printf("timespec_get() return value: %d\n", result);
    if (result == TIME_UTC) {
        printf("timespec_get() success:\n");
        printf("  Seconds: %ld\n", ts.tv_sec);
        printf("  Nanoseconds: %ld\n", ts.tv_nsec);
        printf("  Total time: %ld.%09ld seconds\n", ts.tv_sec, ts.tv_nsec);
    } else {
        printf("timespec_get() failed\n");
    }
    return 0;
}
```

---

## Clock Functions

### 15. `clock_getres()` (POSIX)
**Prototype:** `int clock_getres(clockid_t clk_id, struct timespec *res);`
**Description:** Gets resolution of specified clock
**Return:** 0 on success, -1 on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>

int main() {
    struct timespec res;
    
    int result1 = clock_getres(CLOCK_REALTIME, &res);
    printf("clock_getres(CLOCK_REALTIME) return: %d\n", result1);
    if (result1 == 0) {
        printf("  Resolution: %ld.%09ld seconds\n", res.tv_sec, res.tv_nsec);
    }
    
    int result2 = clock_getres(CLOCK_MONOTONIC, &res);
    printf("clock_getres(CLOCK_MONOTONIC) return: %d\n", result2);
    if (result2 == 0) {
        printf("  Resolution: %ld.%09ld seconds\n", res.tv_sec, res.tv_nsec);
    }
    
    return 0;
}
```

### 16. `clock_gettime()` (POSIX)
**Prototype:** `int clock_gettime(clockid_t clk_id, struct timespec *tp);`
**Description:** Gets time of specified clock
**Return:** 0 on success, -1 on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>

int main() {
    struct timespec tp;
    
    int result1 = clock_gettime(CLOCK_REALTIME, &tp);
    printf("clock_gettime(CLOCK_REALTIME) return: %d\n", result1);
    if (result1 == 0) {
        printf("  Time: %ld.%09ld seconds since epoch\n", tp.tv_sec, tp.tv_nsec);
    }
    
    int result2 = clock_gettime(CLOCK_MONOTONIC, &tp);
    printf("clock_gettime(CLOCK_MONOTONIC) return: %d\n", result2);
    if (result2 == 0) {
        printf("  Time: %ld.%09ld seconds since boot\n", tp.tv_sec, tp.tv_nsec);
    }
    
    return 0;
}
```

### 17. `clock_settime()` (POSIX)
**Prototype:** `int clock_settime(clockid_t clk_id, const struct timespec *tp);`
**Description:** Sets time of specified clock
**Return:** 0 on success, -1 on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>

int main() {
    struct timespec tp;
    tp.tv_sec = time(NULL);
    tp.tv_nsec = 0;
    
    // Note: This usually requires root privileges
    int result = clock_settime(CLOCK_REALTIME, &tp);
    printf("clock_settime() return: %d\n", result);
    if (result == 0) {
        printf("  Successfully set system time\n");
    } else {
        printf("  Failed to set system time (may need root privileges)\n");
        perror("  Error");
    }
    
    return 0;
}
```

### 18. `clock_nanosleep()` (POSIX)
**Prototype:** `int clock_nanosleep(clockid_t clk_id, int flags, const struct timespec *request, struct timespec *remain);`
**Description:** Sleep for specified time on given clock
**Return:** 0 on success, error number on failure

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>

int main() {
    struct timespec req, rem;
    req.tv_sec = 1;
    req.tv_nsec = 500000000;  // 1.5 seconds
    
    printf("Sleeping for 1.5 seconds...\n");
    int result = clock_nanosleep(CLOCK_REALTIME, 0, &req, &rem);
    
    printf("clock_nanosleep() return: %d\n", result);
    if (result == 0) {
        printf("  Sleep completed successfully\n");
    } else {
        printf("  Sleep interrupted, remaining: %ld.%09ld seconds\n", 
               rem.tv_sec, rem.tv_nsec);
    }
    
    return 0;
}
```

---

## Timer Functions

### 19. `timer_create()` (POSIX)
**Prototype:** `int timer_create(clockid_t clk_id, struct sigevent *sevp, timer_t *timerid);`
**Description:** Creates a per-process timer
**Return:** 0 on success, -1 on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>
#include <signal.h>

int main() {
    timer_t timerid;
    
    int result = timer_create(CLOCK_REALTIME, NULL, &timerid);
    printf("timer_create() return: %d\n", result);
    if (result == 0) {
        printf("  Timer created successfully\n");
        printf("  Timer ID: %p\n", (void*)timerid);
        
        // Clean up
        timer_delete(timerid);
    } else {
        printf("  Timer creation failed\n");
        perror("  Error");
    }
    
    return 0;
}
```

### 20. `timer_delete()` (POSIX)
**Prototype:** `int timer_delete(timer_t timerid);`
**Description:** Deletes a per-process timer
**Return:** 0 on success, -1 on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>

int main() {
    timer_t timerid;
    
    if (timer_create(CLOCK_REALTIME, NULL, &timerid) == 0) {
        printf("Timer created: %p\n", (void*)timerid);
        
        int result = timer_delete(timerid);
        printf("timer_delete() return: %d\n", result);
        if (result == 0) {
            printf("  Timer deleted successfully\n");
        } else {
            printf("  Timer deletion failed\n");
            perror("  Error");
        }
    }
    
    return 0;
}
```

### 21. `timer_settime()` (POSIX)
**Prototype:** `int timer_settime(timer_t timerid, int flags, const struct itimerspec *new_value, struct itimerspec *old_value);`
**Description:** Arms/disarms per-process timer
**Return:** 0 on success, -1 on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>

int main() {
    timer_t timerid;
    struct itimerspec its, old_its;
    
    if (timer_create(CLOCK_REALTIME, NULL, &timerid) == 0) {
        // Set timer for 2 seconds from now, no repeat
        its.it_value.tv_sec = 2;
        its.it_value.tv_nsec = 0;
        its.it_interval.tv_sec = 0;
        its.it_interval.tv_nsec = 0;
        
        int result = timer_settime(timerid, 0, &its, &old_its);
        printf("timer_settime() return: %d\n", result);
        if (result == 0) {
            printf("  Timer armed for 2 seconds\n");
            printf("  Old timer value: %ld.%09ld seconds\n", 
                   old_its.it_value.tv_sec, old_its.it_value.tv_nsec);
        } else {
            printf("  Timer arming failed\n");
            perror("  Error");
        }
        
        timer_delete(timerid);
    }
    
    return 0;
}
```

### 22. `timer_gettime()` (POSIX)
**Prototype:** `int timer_gettime(timer_t timerid, struct itimerspec *curr_value);`
**Description:** Fetches state of per-process timer
**Return:** 0 on success, -1 on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
    timer_t timerid;
    struct itimerspec its, curr;
    
    if (timer_create(CLOCK_REALTIME, NULL, &timerid) == 0) {
        // Set timer for 5 seconds
        its.it_value.tv_sec = 5;
        its.it_value.tv_nsec = 0;
        its.it_interval.tv_sec = 0;
        its.it_interval.tv_nsec = 0;
        
        timer_settime(timerid, 0, &its, NULL);
        
        sleep(2);  // Wait 2 seconds
        
        int result = timer_gettime(timerid, &curr);
        printf("timer_gettime() return: %d\n", result);
        if (result == 0) {
            printf("  Time remaining: %ld.%09ld seconds\n", 
                   curr.it_value.tv_sec, curr.it_value.tv_nsec);
            printf("  Interval: %ld.%09ld seconds\n", 
                   curr.it_interval.tv_sec, curr.it_interval.tv_nsec);
        } else {
            printf("  Getting timer state failed\n");
            perror("  Error");
        }
        
        timer_delete(timerid);
    }
    
    return 0;
}
```

### 23. `timer_getoverrun()` (POSIX)
**Prototype:** `int timer_getoverrun(timer_t timerid);`
**Description:** Gets overrun count for a per-process timer
**Return:** Overrun count on success, -1 on error

```c
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <time.h>

int main() {
    timer_t timerid;
    
    if (timer_create(CLOCK_REALTIME, NULL, &timerid) == 0) {
        int result = timer_getoverrun(timerid);
        printf("timer_getoverrun() return: %d\n", result);
        if (result >= 0) {
            printf("  Timer overrun count: %d\n", result);
        } else {
            printf("  Getting overrun count failed\n");
            perror("  Error");
        }
        
        timer_delete(timerid);
    }
    
    return 0;
}
```

---

## Parsing Functions

### 24. `strptime()` (POSIX)
**Prototype:** `char *strptime(const char *s, const char *format, struct tm *tm);`
**Description:** Parses time string according to format
**Return:** Pointer to first character not processed, or NULL on error

```c
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
    struct tm tm_struct = {0};
    const char *time_str = "2024-12-25 14:30:45";
    
    char *result = strptime(time_str, "%Y-%m-%d %H:%M:%S", &tm_struct);
