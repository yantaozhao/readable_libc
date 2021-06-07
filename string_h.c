#include <stddef.h>   // size_t


/*
 * The  strlen()  function calculates the length of the string pointed to by s, excluding the terminating null byte ('\0')
 */
size_t strlen(const char* s)
{
    const char* start = s;
#if 1
    for (; *s; s++);
#else
    while (*s)
        s++;
#endif
    return s - start;
}


////////////////////////////////////////////////////////////


/*
 * The  strcpy() function copies the string pointed to by src, including the terminating null byte ('\0'), to the buffer pointed to by dest.
 *
 * The strncpy() function is similar, except  that  at  most  n  bytes  of  src  are  copied.
 * If the length of src is less than n, strncpy() writes additional null  bytes  to  dest  to ensure that a total of n bytes are written.
 * Warning:  If  there  is  no null byte among the first n bytes of src, the string placed in dest will not be null-terminated.
 */
char* strcpy(char* dest, const char* src)
{
    char* dst0 = dest;
    for (; (*dest = *src); src++, dest++);
    return dst0;
}


char* strncpy(char* dest, const char* src, size_t n)
{
#if 1
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';  // fill the null bytes

    return dest;
#else
    char* dst0 = dest;
    while (n > 0)
    {
        --n;
        if ((*dest++ = *src++) == '\0')
            break;
    }
    while (n-- > 0)
        *dest++ = '\0';

    return dst0;
#endif
}


////////////////////////////////////////////////////////////


/*
 * The  strcat()  function  appends  the  src  string  to  the  dest  string, overwriting the terminating null byte ('\0') at the end of dest, and then adds a  terminating  null  byte.
 * As with strcat(), the resulting string in dest is always null-terminated.
 *
 * The strncat() function is similar, except that:
 *  * it will use at most n bytes from src; and
 *  * src does not need to be null-terminated if it contains n or more bytes.
 */
char* strcat(char* dest, const char* src)
{
    strcpy(dest + strlen(dest), src);
    return dest;
}


char* strncat(char* dest, const char* src, size_t n)
{
    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)  // at most n bytes
    {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';  // +1 terminating null byte

    return dest;
}


////////////////////////////////////////////////////////////


int strcmp(const char* lhs, const char* rhs)
{
    for (; *lhs == *rhs && *lhs; lhs++, rhs++);
    return *(unsigned char*)lhs - *(unsigned char*)rhs;
}


int strncmp(const char* lhs, const char* rhs, size_t n)
{
    if (!n--)
        return 0;
    for (; n && *lhs == *rhs && *lhs; lhs++, rhs++, n--);
    return *(unsigned char*)lhs - *(unsigned char*)rhs;
}


////////////////////////////////////////////////////////////


/*
 * The  strchr() function returns a pointer to the first occurrence of the character c in the string s.
 *
 * The strrchr() function returns a pointer to the last occurrence of the character c in  the string s.
 */
char* strchr(const char* s, int c)
{
    while (*s && *s != c)
        s++;
    if (*s == c)
        return (char*)s;
    return NULL;
}


char* strrchr(const char* s, int c)
{
    const char* last = NULL;
    if (c)
    {
        while ((s = strchr(s, c)))
        {
            last = s;  // save to last
            s++; // advance 1 step
        }
    }
    else
    {
        last = strchr(s, c);
    }

    return (char*)last;
}


////////////////////////////////////////////////////////////


/*
 * The strspn() function calculates the length (in bytes) of the initial segment of s which consists entirely of bytes in accept.
 *
 * The strcspn() function calculates the length of the initial segment of  s  which  consists entirely of bytes not in reject
 */
size_t strspn(const char* s, const char* accept)
{
#if 1
    const char* s0 = s;
    const char* a;
    while (*s)
    {
        for (a = accept; *a; a++)
        {
            if (*s == *a)
                break;
        }
        if (*a == '\0')
            break;
        s++;
    }
    return s - s0;

#else
    const char* s0 = s;
    const char* p = accept;
    while (*p)
    {
        if (*p++ == *s)
        {
            ++s;
            p = accept;
        }
    }
    return s - s0;
#endif
}


size_t strcspn(const char* s, const char* reject)
{
    const char* c;
    const char* r;
    for (c = s; *c; c++)
    {
        for (r = reject; *r; r++)
        {
            if (*r == *c)
                goto done;
        }
    }
done:
    return c - s;
}


/*
 * The strpbrk() function locates the first occurrence in the string s of any of the bytes in the string breakset.
 */
char* strpbrk(const char* s, const char* breakset)
{
    s += strcspn(s, breakset);
    return *s ? (char*)s : 0;
}


/*
 * The  strstr()  function  finds  the first occurrence of the substring substr in the string s.  The terminating null bytes ('\0') are not compared.
 */
char* strstr(const char* s, const char* substr)
{
    // TODO:
}


/*
 * The strtok() function breaks a string into a sequence of zero or more nonempty tokens.
 */
char* strtok(char* s, const char* delim)
{
    static char* p;

    if (!s && !(s = p))
        return NULL;
    s += strspn(s, delim);
    if (!*s)
        return p = 0;
    p = s + strcspn(s, delim);
    if (*p)
        *p++ = 0;
    else
        p = 0;

    return s;
}


////////////////////////////////////////////////////////////


/*
 * The memchr() function scans the initial n bytes of the memory area pointed to by s for the first instance of c.
 * Both c and the bytes  of  the  memory  area  pointed  to  by  s  are interpreted as unsigned char.
 */
void* memchr(const void* s, int c, size_t n)
{
    const unsigned char* r = (const unsigned char*)s;
    unsigned char d = c;
    while (n)
    {
        if (*r == d)
        {
            return (void*)r;
        }
        ++r;
        --n;
    }
    return NULL;
}


/*
 * The  memcmp()  function  compares the first n bytes (each interpreted as unsigned char) of the memory areas lhs and rhs.
 */
int memcmp(const void* lhs, const void* rhs, size_t n)
{
    const unsigned char* l = lhs, * r = rhs;
    for (; n && *l == *r; l++, r++, n--);
    return n ? *l - *r : 0;
}


////////////////////////////////////////////////////////////


/*
 * The  memset() function fills the first n bytes of the memory area pointed to by dest with the constant byte c.
 */
void* memset(void* dest, int c, size_t n)
{
    unsigned char* s = (unsigned char*)dest;
    for (; n; n--, s++)
        *s = c;

    return dest;
}


/*
 * The memcpy() function copies n bytes from memory area src to memory area dest.
 *
 * The  memmove()  function  copies  n  bytes  from memory area src to memory area dest.  The memory areas may overlap.
 */
void* memcpy(void* dest, const void* src, size_t n)
{
    unsigned char* d = dest;
    const unsigned char* s = src;

    for (; n; n--, s++, d++)
        *d = *s;
    return dest;
}


void* memmove(void* dest, const void* src, size_t n)
{
    char* d = dest;
    const char* s = src;

    if (d == s)
        return d;

    // start from the point of src, which maybe in the overlap area.
    if (d < s)
    {
        while (n)
        {
            *d++ = *s++;
            --n;
        }
    }
    else
    {
        while (n)
        {
            --n;
            d[n] = s[n];
        }
    }

    return dest;
}
