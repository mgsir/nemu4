#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {

  va_list ap;
  char c = *fmt;

  va_start(ap,fmt);
  int print_cnt = 0;
  int num;
  char *str;

  while(c)
  {
    switch (c)
    {
    case 'd':
      num = va_arg(ap,int);
      if(num == 0) { putch('0'); ++print_cnt;}
      else{
        int num_len = 0;
        int temp_num = num;
        int arr_num[100];
        while(temp_num)
        {
          temp_num /= 10;
          arr_num[num_len] = temp_num % 10;
          ++num_len;
        }

        for(size_t i = num_len-1; i  >= 0 ;--i)
        {
          putch(arr_num[i] - '0');
          ++print_cnt;
        }
      }
      break;
    case 's':
       str = va_arg(ap,char *);
      for(size_t i = 0; i < strlen(str); ++i)
      {
        putch(str[i]);
        ++print_cnt;
      }
      break;
    default:
      putch(c);
      ++print_cnt;
    }

    c = *(++fmt);
  }

  va_end(ap);
  
  return print_cnt;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  return 0;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  char c = *fmt;

  va_start(ap,fmt);
  int print_cnt = 0;
  int num;
  char *str;

  while(c)
  {
    switch (c)
    {
    case 'd':
      num = va_arg(ap,int);
      if(num == 0) { out[print_cnt++] = '0';}
      else{
        int num_len = 0;
        int arr_num[10000];
        while(num)
        {
          num /= 10;
          arr_num[num_len] = num % 10;
          ++num_len;
        }

        for(size_t i = num_len-1; i  >= 0 ;--i)
        {
          out[print_cnt++] = arr_num[i] - '0';
        }
      }
      break;
    case 's':
      str = va_arg(ap,char *);
      for(size_t i = 0; i < strlen(str); ++i)
      {
        out[print_cnt++] = str[i];
      }
      break;
    default:
      out[print_cnt++] = c;
    }
    c = *(++fmt);
  }

  va_end(ap);
  out[print_cnt] = '\0';

  return print_cnt;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  return 0;
}

#endif
