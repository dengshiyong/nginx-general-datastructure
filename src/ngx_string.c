#include "ngx_core.h"

u_char * ngx_cpystrn(u_char *dst,u_char *src,size_t n){
    if (n == 0){
        return dst;
    }

    while (--n){
        *dst = *src;
        if (*dst == '\0'){
            return dst;
        }
        dst++;
        src++;
    }

    *dst = '\0';

    return dst;
}

/*
 * supported formats:
 *    %[0][width][x][X]O        off_t
 *    %[0][width]T              time_t
 *    %[0][width][u][x|X]z      ssize_t/size_t
 *    %[0][width][u][x|X]d      int/u_int
 *    %[0][width][u][x|X]l      long
 *    %[0][width|m][u][x|X]i    ngx_int_t/ngx_uint_t
 *    %[0][width][u][x|X]D      int32_t/uint32_t
 *    %[0][width][u][x|X]L      int64_t/uint64_t
 *    %[0][width|m][u][x|X]A    ngx_atomic_int_t/ngx_atomic_uint_t
 *    %[0][width][.width]f      double, max valid number fits to %18.15f
 *    %P                        ngx_pid_t
 *    %M                        ngx_msec_t
 *    %r                        rlim_t
 *    %p                        void *
 *    %V                        ngx_str_t *
 *    %v                        ngx_variable_value_t *
 *    %s                        null-terminated string
 *    %*s                       length and string
 *    %Z                        '\0'
 *    %N                        '\n'
 *    %c                        char
 *    %%                        %
 *
 *  reserved:
 *    %t                        ptrdiff_t
 *    %S                        null-terminated wchar string
 *    %C                        wchar
 */

u_char * ngx_cdecl
ngx_sprintf(u_char *buf,const char *fmt,...){
    u_char *p;
    va_list args;
    va_start (args,fmt);
    p = ngx_vslprintf(buf,(void *)-1,fmt,args);
    va_end (args);

    return p;
}

u_char * ngx_cdecl  ngx_slprintf(u_char *buf,u_char *last,const char *fmt,...){
    u_char *p;
    va_list args;
    va_start(args,fmt);
    p = ngx_vslprintf(buf,last,fmt,args);
    va_end (args);
    return p;
}

u_char * ngx_vslprintf(u_char *buf,u_char * last,const char *fmt,va_list args){
   u_char *p,zero;
   int d;
   double f;
   size_t len,slen;
   int64_t i64;
   u_int64_t ui64,frac;
   ngx_msec_t ms;
   ngx_uint_t width,sign,hex,max_width,frac_width,scale,n;
   ngx_str_t *v;
   ngx_variable_value_t **vv;

   while(*fmt && buf < last){

       /*"buf < last" means that we could copy at least one character:
        * the plain character,"%%","%c",and minus without the checking
        */
       if(*fmt == '%'){
           i64 = 0;
           ui64 = 0;

           zero = (u_char)((*++fmt == '0')?'0':' ');
           width = 0;
           sign = 1;
           hex = 0;
           max_width = 0;
           frac_width = 0;
           slen = (size_t)-1;

           while (*fmt  >= '0' && *fmt <= '9') {
               width = width * 10 + *fmt++ - '0';
           }

           for(;;){
               switch (*fmt) {
               case 'u':
                   sign = 0;
                   fmt++;
                   continue;
               case 'm':
                   max_width = 1;
                   fmt++;
                   continue;
               case 'X':
                   hex = 2;
                   sign = 0;
                   fmt++;
                   continue;
               case 'x':
                   hex = 1;
                   sign = 0;
                   fmt++;
               case '.':
                   fmt++;

                   while (*fmt >= '0' && *fmt <= '9') {
                       frac_width = frac_width * 10 + *fmt++ - '0';
                   }

                   break;

               case '*':
                   slen = va_arg(args,size_t);
                   fmt++;
                   continue;

               default:
                   break;
               }

               break;
           }
           switch (*fmt) {
           case 'V':
               v = va_arg(args,ngx_str_t*);
               len = ngx_min(((size_t)(last - buf)),v->len);
               buf = ngx_cpymem(buf,v->data,len);
               fmt++;

               continue;

           case 'v':
               vv = va_arg(args,ngx_variable_value_t*);

               len = ngx_min(((size_t)(last-buf)),((ngx_variable_value_t*)vv)->len);
               buf = ngx_cpymem(buf,((ngx_variable_value_t *)vv)->data,len);
               fmt++;

               continue;

           case 's':
               p = va_arg(args,u_char*);

               if (slen == (size_t)-1) {
                   while(*p && buf < last){
                       *buf++ = *p++;
                   }
               }
               else {
                   len = ngx_min(((size_t)(last - buf)),slen);
                   buf = ngx_cpymem(buf,p,len);
               }
               fmt++;

               continue;

           case 'O':
               i64 = (int64_t) va_arg (args,off_t);
               sign = 1;
               break;

           case 'P':
               i64 = (int64_t) va_arg (args,ngx_pid_t);
               sign = 1;
               break;

           case 'T':
               i64 = (int64_t)va_arg (args,time_t);
               sign = 1;
               break;

           case 'M':
               ms = (ngx_msec_t)va_arg (args,ngx_msec_t);
               if ((ngx_msec_int_t) ms == -1){
                   sign = 1;
                   i64 = -1;
               }
               else {
                   sign = 0;
                   ui64 = (u_int64_t)ms;
               }
               break;

           case 'z':
               if (sign){
                   i64 = (int64_t)va_arg(args,ssize_t);
               }
               else{
                   ui64 = (u_int64_t)va_arg(args,size_t);
               }
               break;

           case 'i':
               if(sign){
                   i64 = (int64_t)va_arg (args,ngx_int_t);
               }
               else{
                   i64 = (u_int64_t)va_arg(args,ngx_uint_t);
               }

               if(max_width){
                   width = NGX_INT_T_LEN;
               }

               break;

           case 'd':
               if(sign){
                   i64 = (int64_t) va_arg (args,int);
               }
               else{
                   ui64 = (u_int16_t)va_arg (args,uint);
               }
               break;

           case 'l':
               if(sign){
                   i64 = (int64_t) va_arg (args,long);
               }
               else{
                   ui64 = (u_int64_t) va_arg (args,u_long);
               }
               break;

           case 'D':
               if(sign){
                   i64 = (int64_t)va_arg (args,int32_t);
               }
               else{
                   ui64 = (u_int64_t)va_arg (args,u_int32_t);
               }
               break;

           case 'L':
               if(sign){
                   i64 = (int64_t)va_arg(args,int64_t);
               }
               else{
                   ui64 = (u_int64_t)va_arg(args,u_int64_t);
               }
               break;

           case 'A':
               if(sign){
                   i64 = (int64_t)va_arg (args,ngx_atomic_int_t);
               }
               else{
                   ui64 = (u_int64_t)va_arg(args,ngx_atomic_uint_t);
               }

               if(max_width){
                   width = NGX_ATOMIC_T_LEN;
               }
               break;

           case 'f':
               f = va_arg(args,double);

               if(f < 0){
                   *buf++ = '-';
                   f = -f;
               }
               ui64 = (u_int16_t)f;
               frac = 0;

               if(frac_width){
                  scale = 1;
                  for (n = frac_width;n;n--){
                      scale *= 10;
                  }

                  frac = (u_int64_t)((f - (double)ui64)*scale + 0.5);

                  if(frac == scale){
                      ui64++;
                      frac = 0;
                  }
               }

               buf = ngx_sprintf_num(buf,last,ui64,zero,0,width);

               if(frac_width){
                   if(buf < last){
                       *buf++ = '.';
                   }

                   buf = ngx_sprintf_num(buf,last,frac,'0',0,frac_width);
               }

               fmt++;
               continue;

#if !(NGX_WIN32)
           case 'r':
               i64 = (int64_t)va_arg (args,rlim_t);
               sign = 1;
               break;
#endif

           case 'p':
               ui64 = (uintptr_t) va_arg(args,void *);
               hex = 2;
               sign = 0;
               zero = '0';
               width = NGX_PTR_SIZE * 2;
               break;

           case 'c':
               d = va_arg(args,int);
               *buf++ = (u_char)(d & 0xff);
               fmt++;

               continue;

           case 'Z':
               *buf++ = '\0';
               fmt++;

               continue;

           case 'N':
#if (NGX_WIN32)
               *buf++ = CR;
               if(buf < last){
                   *buf++ = LF;
               }
#else
               *buf++ = LF;
#endif
               fmt++;

               continue;

           case '%':
              *buf++ = '%';
               fmt++;

               continue;

           default:
               *buf++ = *fmt++;

               continue;
           }

          if(sign){
              if(i64 < 0){
                  *buf++ = '-';
                  ui64 = (u_int64_t)-i64;
              }
              else{
                 ui64 = (u_int64_t)i64;
              }
          }
          buf = ngx_sprintf_num (buf,last,ui64,zero,hex,width);
          fmt++;
       }
       else{
           *buf++ = *fmt++;
       }
   }
   return buf;
}

static u_char*
 ngx_sprintf_num(u_char * buf,u_char *last,u_int64_t ui64,u_char zero,
                 ngx_uint_t hexademical,ngx_uint_t width){
    u_char *p,temp[NGX_INT64_LEN + 1];
    /* we need temp[NGX_INT64_LEN +1]only
     * but icc issues the warning
     */
    size_t len;
    u_int32_t ui32;
    static u_char hex[] = "0123456789abcdef";
    static u_char HEX[] = "0123456789ABCDEF";

    p = temp + NGX_INT64_LEN;

    if(hexademical == 0){

            /*
             * To divide 64-bit numbers and to find remainders
             * on the x86 platform gcc and icc call the libc functions
             * [u]divdi3() and [u]moddi3(), they call another function
             * in its turn.  On FreeBSD it is the qdivrem() function,
             * its source code is about 170 lines of the code.
             * The glibc counterpart is about 150 lines of the code.
             *
             * For 32-bit numbers and some divisors gcc and icc use
             * a inlined multiplication and shifts.  For example,
             * unsigned "i32 / 10" is compiled to
             *
             *     (i32 * 0xCCCCCCCD) >> 35
             */
        if(ui64 <= (u_int64_t)NGX_MAX_INT_T_VALUE){
           ui32 = (u_int32_t)ui64;

           do {
               *--p = (u_char)(ui32 % 10 + '0');
           }
           while (ui32 /= 10);
        }
        else{
           do{
                *--p = (u_char)(ui64 % 10 + '0');
            }
            while (ui64 /= 10);
        }
    }
    else if (hexademical == 1){

        do{
            /* the "(uint32_t)" cast disables the BCC's warning */
            *--p = hex[(u_int32_t)(ui64 & 0xf)];
        }
        while (ui64 >>= 4);
    }
    else {
        /*hexademical == 2*/
        do {
            *--p = HEX[(u_int32_t)(ui64 & 0xf)];
        }
       while (ui64 >>= 4);
    }
    /* zero or space padding */
    len = (temp + NGX_INT64_LEN) - p;

    while (len++ <  width  && buf  < last){
        *buf++ = zero;
    }
    /* number safe copy */

    len = (temp + NGX_INT64_LEN) - p;

    if (buf + len > last){
        len = last - buf;
    }

    return ngx_cpymem(buf,p,len);
}





































