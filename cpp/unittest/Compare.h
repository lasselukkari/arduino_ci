#pragma once
#include <avr/pgmspace.h>
#include <WString.h>

template  < typename A, typename B > struct Compare
{
  inline static int between(const A &a,const B &b)
  {
    if (a<b) return -1;
    if (b<a) return  1;
    return 0;
  }
  inline static bool equal(const A &a,const B &b)       { return (!(a < b)) && (!(b < a)); }
  inline static bool notEqual(const A &a,const B &b)    { return (a<b) || (b<a); }
  inline static bool less(const A &a,const B &b)        { return a<b; }
  inline static bool more(const A &a,const B &b)        { return b<a; }
  inline static bool lessOrEqual(const A &a,const B &b) { return !(b<a); }
  inline static bool moreOrEqual(const A &a,const B &b) { return !(a<b); }
};

// helpers for macros
inline static int arduinoCICompareBetween(const String &a,const __FlashStringHelper * const &b)
{
  uint8_t a_buf[4],b_buf[4];
  uint16_t i=0;

  for (;;) {
    uint8_t j=(i%4);
    if (j == 0) {
        a.getBytes(a_buf,4,i);
        memcpy_P(b_buf,((const char *)b)+i,4);
    }
    if (a_buf[j] < b_buf[j]) return -1;
    if (a_buf[j] > b_buf[j]) return  1;
    if (a_buf[j] == 0) return 0;
    ++i;
  }
}

inline static int arduinoCICompareBetween(const __FlashStringHelper * const &a,const __FlashStringHelper * const &b)
{
  uint8_t a_buf[4],b_buf[4];
  uint16_t i=0;

  for (;;) {
    uint8_t j=(i%4);
    if (j == 0) {
        memcpy_P(a_buf,((const char *)a)+i,4);
        memcpy_P(b_buf,((const char *)b)+i,4);
    }
    if (a_buf[j] < b_buf[j]) return -1;
    if (a_buf[j] > b_buf[j]) return  1;
    if (a_buf[j] == 0) return 0;
    ++i;
  }
}


// this macro works for all the string-based comparisons
// but just in case, https://stackoverflow.com/a/13842784/2063546
#define comparisonTemplateMacro(T1, T1m, T2, T2m, betweenImpl, ...)                                   \
  template  < __VA_ARGS__ > struct Compare<T1 T1m, T2 T2m>;                                           \
  template  < __VA_ARGS__ > struct Compare<T1 T1m, T2 T2m>                                            \
  {                                                                                                   \
    inline static int  between(    T1 const (&a)T1m, T2 const (&b)T2m) { return betweenImpl; }        \
    inline static bool equal(      T1 const (&a)T1m, T2 const (&b)T2m) { return between(a, b) == 0; } \
    inline static bool notEqual(   T1 const (&a)T1m, T2 const (&b)T2m) { return between(a, b) != 0; } \
    inline static bool less(       T1 const (&a)T1m, T2 const (&b)T2m) { return between(a, b) < 0; }  \
    inline static bool more(       T1 const (&a)T1m, T2 const (&b)T2m) { return between(a, b) > 0; }  \
    inline static bool lessOrEqual(T1 const (&a)T1m, T2 const (&b)T2m) { return between(a, b) <= 0; } \
    inline static bool moreOrEqual(T1 const (&a)T1m, T2 const (&b)T2m) { return between(a, b) >= 0; } \
  };

comparisonTemplateMacro(String, , String, ,                                            a.compareTo(b))
comparisonTemplateMacro(String, , const char *, ,                                      a.compareTo(b))
#if defined(F)
comparisonTemplateMacro(String, , const __FlashStringHelper *,  ,                      arduinoCICompareBetween(a, b))
comparisonTemplateMacro(const char *,,  const __FlashStringHelper *, ,                 strcmp_P(a,(const char *)b))
comparisonTemplateMacro(const __FlashStringHelper *, , String, ,                       -arduinoCICompareBetween(b, a))
comparisonTemplateMacro(const __FlashStringHelper *, , const char *, ,                 -strcmp_P(b,(const char *)a))
comparisonTemplateMacro(const __FlashStringHelper *, , const __FlashStringHelper *, ,  arduinoCICompareBetween(a, b))
comparisonTemplateMacro(const __FlashStringHelper *, , char *, ,                       -strcmp_P(b,(const char *)a))
comparisonTemplateMacro(char *, , const __FlashStringHelper *, ,                       strcmp_P(a,(const char *)b))
comparisonTemplateMacro(const __FlashStringHelper *, , char, [M],                      -strcmp_P(b,(const char *)a), size_t M)
comparisonTemplateMacro(char, [N], const __FlashStringHelper *, ,                      strcmp_P(a,(const char *)b), size_t N)
#endif
comparisonTemplateMacro(String, , char *, ,                                            a.compareTo(b))
comparisonTemplateMacro(const char *, , String, ,                                      -b.compareTo(a))
comparisonTemplateMacro(const char *, , const char *, ,                                strcmp(a,b))
comparisonTemplateMacro(const char *, , char *, ,                                      strcmp(a,b))
comparisonTemplateMacro(char *, , String, ,                                            -b.compareTo(a))
comparisonTemplateMacro(char *, , const char *, ,                                      strcmp(a,b))
comparisonTemplateMacro(char *, , char *, ,                                            strcmp(a,b))
comparisonTemplateMacro(String, , char, [M],                                           a.compareTo(b), size_t M)
comparisonTemplateMacro(const char *, , char, [M],                                     strcmp(a,b), size_t M)
comparisonTemplateMacro(char *, , char, [M],                                           strcmp(a,b), size_t M)
comparisonTemplateMacro(char, [N], String, ,                                           -b.compareTo(a), size_t N)
comparisonTemplateMacro(char, [N], const char *, ,                                     strcmp(a,b), size_t N)
comparisonTemplateMacro(char, [N], char *, ,                                           strcmp(a,b), size_t N)
comparisonTemplateMacro(char, [N], char, [M],                                          strcmp(a,b), size_t N, size_t M)

comparisonTemplateMacro(A, , std::nullptr_t, ,                                         a ? 1 : 0, typename A)
comparisonTemplateMacro(std::nullptr_t, , B, ,                                         b ? -1 : 0, typename B)

// super general comparisons
template <typename A, typename B> int  compareBetween(    const A &a, const B &b) { return Compare<A, B>::between(    a, b); }
template <typename A, typename B> bool compareEqual(      const A &a, const B &b) { return Compare<A, B>::equal(      a, b); }
template <typename A, typename B> bool compareNotEqual(   const A &a, const B &b) { return Compare<A, B>::notEqual(   a, b); }
template <typename A, typename B> bool compareLess(       const A &a, const B &b) { return Compare<A, B>::less(       a, b); }
template <typename A, typename B> bool compareMore(       const A &a, const B &b) { return Compare<A, B>::more(       a, b); }
template <typename A, typename B> bool compareLessOrEqual(const A &a, const B &b) { return Compare<A, B>::lessOrEqual(a, b); }
template <typename A, typename B> bool compareMoreOrEqual(const A &a, const B &b) { return Compare<A, B>::moreOrEqual(a, b); }
