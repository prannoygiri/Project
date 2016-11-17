/*
last check up 
25/01/2012
------------

       _____________
      (             )
      (____________ )
       |           |
       |           |  
      _|           |_
     /               \
   /                  \
  (___________________) 
  |                   |
  |   ...:::Beer:::   |
  |..::Version:0.05::.|
  |                   |
  |___________________|
  |                   |
  |                   |
  |                   |
  |                   |
  |                   |
  (___________________)
0101010101010110101010101010101101010101010   

is held by Apache license 2.0
-----------------------
Beer simple C header

Authors: Cooler_,m0nad,ryonagana,b4r0n,utroz,mentebinaria
E-mail: c00f3r[at]gmail[dot]com
date: 03/08/2011

thanks: 
  _mlk_,m0nad,
  I4K,sigsegv,b-man,kov,utroz,eremitah,vorazbr,mentebinaria
  delfo,c0lt7r,B4r0n,joey,fokerbug,
  zepplin,voidpointer,muzgo,memset,b4r0n,novato_br...
  
  Beer is a C header to help you in small problems

Have a lot functions how
math functions(mmc,mdc,bitwise_sqrt,quadratic equation,factorial,test if number is prime..)
parsers,
string functions (split,strrev..),
validate e-mail,
SQL query filter,
Files Jobs how READ,WRITE,COPY,list DIRs,bytes of file...

strings,numbers convert

    |-hex2int
    |-dec2bin
    |-char2hex
    |-hex2char
    |-string2hex

bitwise macros ,another things
do you want help us ?
send your function...

in the future this header will a dynamic library...

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//time functions...
#include <time.h>
// use to dir functions
#include <dirent.h>


//macro to read stdin string
#define ReadString(a) fgets(a,sizeof(a),stdin),a[strlen(a)-1] = '\0'; 

//return elements of array
#define array_elements(array) (sizeof(array) / sizeof *(array))

//hide and unhide strings
#define UNHIDE_STR(str) do { char *p = str;  while (*p) *p++ += 0x19; } while (0)
#define HIDE_STR(str)   do { char *p = str;  while (*p) *p++ -= 0x19; } while (0)

// bitwise macros
#define XorSwap(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))
#define BIT_POS(N)            ( 1U << (N) )
#define SET_FLAG(N, F)        ( (N) |= (F) )
#define CLR_FLAG(N, F)        ( (N) &= -(F) )
#define TST_FLAG(N, F)        ( (N) & (F) )
#define BIT_RANGE(N, M)       ( BIT_POS((M)+1 - (N))-1 << (N) )
#define BIT_SHIFTL(B, N)      ( (unsigned)(B) << (N) )
#define BIT_SHIFTR(B, N)      ( (unsigned)(B) >> (N) )
#define SET_MFLAG(N, F, V)    ( CLR_FLAG(N, F), SET_FLAG(N, V) )
#define CLR_MFLAG(N, F)       ( (N) &= ~(F) )
#define GET_MFLAG(N, F)       ( (N) & (F) )

#define BUGVIEW 1

#define DEBUG(x, s...) do { \
 if (!BUGVIEW) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "%.*s %s[%d] %s(): ", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
} while (0);

// HEAP alignment :-X
void *xmalloc(unsigned int len)
{
 void *ptr;
 ptr=malloc(len);
 if(ptr==NULL) 
  DEBUG("fail malloc");
 return ptr;
}

// convert decimal to binary
char * dec2bin(int n, char * string)
{ 
 int i; 
 static int size = 8 * sizeof(int);
 
  for(i = size - 1; i >= 0; i--, n >>= 1) 
   string[i] = (01 & n) + '0';
 
 string[size] = '\0'; 
 return string; 
} 

// Hexadecimal to Character

// with bitwise
char Hex2Char(char *Hex)
{
 char rch=0;
 int i=0; 

 while(i<2)
 {
  if ( *(Hex + i) >= '0' && *(Hex + i) <= '9' )
   rch = (rch << 4) + (*(Hex + i) - '0');
  else if ( *(Hex + i) >= 'A' && *(Hex + i) <= 'F' )
   rch = (rch << 4) + (*(Hex + i) - 'A' + 10);
  else
   break;
  i++;
 }
 return rch;
}

//simple version
static char char2Hex(unsigned char c)
{
 static const char *HexCharacters = "0123456789ABCDEF";
   if(c > 15)
   {
     DEBUG("error in char2Hex() %c",HexCharacters[c]);
     return -1;
   }
 return HexCharacters[c];
}

// unsigned char x[]={"google.com"}; string2hex(y,x,16)...
static void string2hex(char *Output, unsigned char *Input, int Length)
{
 char *Out;
 char First;
 char Second;

 Out = Output;
 while (Length > 0)
 {
  First = *Input / 0x10;
  Second = *Input % 0x10;
  *Out = char2Hex(First);
   Out++;
  *Out = char2Hex(Second);
   Out++;
   Length--;
   Input++;
 }
 *Out = '\0';
 return;
}

unsigned long hex2int(char *a, unsigned int len)
{
 int i=0;
 unsigned long val = 0;

 while(i<len)
 {
  if(a[i] <= 57)
   val += (a[i]-48)*(1<<(4*(len-1-i)));
  else
   val += (a[i]-55)*(1<<(4*(len-1-i)));
  i++;
 }
 return val;
}


//  Math functions
/*
MDC Máximo Divisor Comum,dois números inteiros é o maior número inteiro que divide 
ambos sem deixar resto.
*/
int mdc(int a,int b) 
{
  if(!b) 
   return a;
  else 
   return mdc(b,a%b);
}

/*
MMC = mínimo múltiplo comum entre dois números é representado 
pelo menor valor comum pertencente aos múltiplos dos números. 
*/
int mmc(int a,int b) 
{
 int formula;
   if(!b) 
    return a;
   else 
    formula = (a*b)/(mdc(a,b));
 return (formula);
} 

// quadratic equation
char * baskara(float a, float b, float c, float *raizes) 
{
 float delta=((b*b)-4*(a*c));
 float x1=0,x2=0;
 char *reply;

 if((!a)||(delta<0))
 {
  DEBUG("error in equation baskara(), delta: %f ",delta);
  return 0; 
 }
 if(delta>0) 
  x1=((-b + ((float)bit_sqrt(delta)) )/(2*a));
 x2=((-b - ((float)bit_sqrt(delta)) )/(2*a));
 snprintf(reply,sizeof(reply)," X1 : %5.2f \n X2 : %5.2f\n",x1,x2);
 return reply;
}

// simple factorial
int factorial( int n )
{
 if(n<=1)
  return 1;
 else
  return n*factorial(n-1);
}

// test if var is prime
int isprime(int n)
{
 int d=2;

 if(n<=0)
 {
  DEBUG("error isprime(), n = %d ",n);
  return -1;
 }

 while(d<n) 
 {
  if(!(n%d))
   return 0;
  d+=2;
 }
 return 1;
}  

//square root by Cooler_
int bit_sqrt(int num)
{
//so 32 is sizeof(int)<<3
 int num0=num,result=0,tbit=1<<((sizeof(int)<<3)-2);

 if(num<=0)
 {
  DEBUG("error bit_sqrt(), num = %d ",num);
  return -1;
 }
        
 while(tbit>num0)
  tbit>>=2;     
 while(tbit^0)
 {
  if(num0>=result+tbit)
  {
   num0-=result+tbit;
   result=(result>>1)+tbit;
  }else
   result>>=1;
  tbit>>=2;
 }
 return result;
}

// test if is palindrome
int palindrome(const char *s)
{
  int x,y;
  
  y = strlen(s);
  for(x=0; x<y/2; x++)
  {
   if( s[x] != s[y-x-1] ) 
    return 0; 
  }
  return 1;
}

// return time
// example OutPut Wed Aug  3 18:26:24 2011
char *TimeNow()
{
 struct tm *local;
 time_t t;
 t = time(NULL);
 local = localtime(&t);
 local = gmtime(&t);
 return asctime(local);
}

// Files jobs  ##############################################################
int CopyFile(char *fromfile, char *tofile)
{
 FILE *ifp, *ofp;
 int c;

 if((ifp = fopen(fromfile, "r")) == NULL) 
  return -1;
 if((ofp = fopen(tofile, "w")) == NULL) 
 { 
  fclose(ifp); 
  DEBUG("Error CopyFile()");
  return -1; 
 }

 while((c = getc(ifp)) != EOF)
  putc(c, ofp);

 fclose(ifp);
 fclose(ofp);
 return 0;
}

int WriteFile(char *file,char *str)
{
 FILE *arq;
 
 arq=fopen(file,"a"); 
  if(!arq) 
  {
   DEBUG("error in WriteFile() %s",file); 
   return 0;
  }
 fprintf(arq,"%s\n",str); 
 fclose(arq); 
 return 1;
}

// return lines from file, example:  const char *buff=readLine("log.txt"),printf("%s",buff);
const char *readLine(char * NameFile)
{
 FILE * file;
 file = fopen(NameFile, "r");
 if(!file)
 {
  DEBUG("error in file"); 	 
  return;
 }
 char *lineBuffer=calloc(1,1), line[128];

 if(!lineBuffer)
 {
  DEBUG("error in readLine() at %s",NameFile);
  return;
 }

 while(fgets(line,sizeof line,file))  
 {
  lineBuffer=realloc(lineBuffer,strlen(lineBuffer)+strlen(line)+1);
  if(!lineBuffer)
  {
   DEBUG("error in readLine() at %s",NameFile);
   return;
  }
  strcat(lineBuffer,line);
 }

 return lineBuffer;
}

// ListDir(directory_name_2_list,Max_chars)
char *ListDir(char *file2list,int MAX)
{
 DIR *d;
 struct dirent *dir;
 char *ret=xmalloc(sizeof(char)*MAX);

 d = opendir(file2list);
 
 if(!d)
 { 
  DEBUG("error in directory");
  return NULL;
 }  

 while((dir = readdir(d)) != NULL)
 {    
  strncat(ret,dir->d_name,strlen(dir->d_name));
  strncat(ret,"\n",1);
 }  

 free(ret);
 closedir(d);
 return ret; 
}   

// return size of bytes on file , same to unix cmd "du -b file"
long FileSize(const char *file)
{
  long ret;
  FILE *fh = fopen(file, "r");
  if(!fh)
  {
   DEBUG("error in file");
   return 0;
  }
  fseek(fh, 0, SEEK_END);
  ret = ftell(fh);
  fclose(fh);
  return ret;
}


/* #################################################################################
 to use with Sort functions
 example:
  char *list[] = { "madruga", "chaves", "kiko", "chiquinha", "inhonho" };
  qsort((void *)list, array_elements(list), sizeof(list[0]), sort_char);
*/

int sort_char( const void *a, const void *b) 
{
 return( strcmp(a,b) );
}

int sort_int(const void *a, const void *b) 
{
 long *a1, *b1;
 a1 = (long *)a; b1 = (long *)b;
 return (*a1 > *b1);
}

//example mergesort(a, 0, sizeof(a)/sizeof(i) - 1);
void mergesort(int *array, size_t first, size_t last)
{
 int middle;
       
 if(first>=last)
  return;
		
 middle = (first + last) / 2;
 mergesort(array, first, middle);
 mergesort(array, middle + 1, last);

 int *temp;
 size_t i = first,j = middle + 1,tp = 0;
 temp = (int *) xmalloc(sizeof(int) * (last - first + 1));
	       
 while(i <= middle && j <= last)
 {
  if(array[i] <= array[j])
  {
   temp[tp] = array[i];
   ++i;
  }	
  else
  {
   temp[tp] = array[j];
   ++j;
  }
  ++tp;
 }
	
 while(j<=last)
 {
  temp[tp] = array[j];
  ++tp;
  j++;
 }		
 while(i<=middle)
 {
  temp[tp] = array[i];
  ++tp;
  i++;
 }
	
 i=first;
 while(i<=last)
 {
  array[i] = temp[i - first];
  i++;
 }	

 free(temp);
}

void bubbleSort(void *p, int width, int N, int(*fptr)(const void *, const void *)) 
{
 int i, j, k;

 unsigned char buf[256];
 unsigned char *bp = p;

  for (i = N-1; i >= 0; i--) 
  {
   for (j = 1; j <= i; j++) 
   {
    k = fptr((void *)(bp + width*(j-1)), (void *)(bp + j*width));
    if(k > 0) 
    {
     memcpy(buf, bp + width*(j-1), width);
     memcpy(bp + width*(j-1), bp + j*width , width);
     memcpy(bp + j*width, buf, width);
    }
   }
  }
}


// ########################### other functions

char *RandomIp(void)
{     
 char *ipRand=NULL;
 int r1,r2,r3,r4;

 r1 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          
 r2 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          
 r3 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          
 r4 = 1+(int) (255.0*rand()/(RAND_MAX+1.0));          

 ipRand=xmalloc(12*sizeof(char *));
 sprintf(ipRand,"%d.%d.%d.%d",r1,r2,r3,r4); 

 return ipRand; 
}


//test if e-mails is valid
int email_isvalid(const char *address) 
{
  int count = 0;
  const char *c, *domain;
  static char *rfc822_specials = "()<>@,;:\\\"[]";

  /* first we validate the name portion (name@domain) */
  for (c = address;  *c;  c++) 
  {
    if (*c == '\"' && (c == address || *(c - 1) == '.' || *(c - 1) == '\"')) 
    {
      while (*++c) 
      {
        if (*c == '\"') 
         break;
        if (*c == '\\' && (*++c == ' ')) 
         continue;
        if (*c <= ' ' || *c >= 127) 
         return 0;
      }
      if(!*c++) 
       return 0;
      if(*c == '@') 
       break;
      if(*c != '.') 
       return 0;
      continue;
    }
    if(*c == '@') 
     break;
    if(*c <= ' ' || *c >= 127) 
     return 0;
    if(strchr(rfc822_specials, *c)) 
     return 0;
  }
  if(c == address || *(c - 1) == '.') 
   return 0;
  /* next we validate the domain portion (name@domain) */
  if(!*(domain = ++c)) 
   return 0;
  do {
    if (*c == '.') 
    {
      if (c == domain || *(c - 1) == '.') return 0;
      count++;
    }
    if (*c <= ' ' || *c >= 127) return 0;
    if (strchr(rfc822_specials, *c)) return 0;
  } while (*++c);
  return (count >= 1);
}

//use input to escape SQL Injection
char *scapeSQL(const char *input, char quote, int wildcards) {
  char       *out, *ptr;
  const char *c;
   
  /* If every character in the input needs to be escaped, the resulting string
   * would at most double in size.  Also, include room for the surrounding
   * quotes.
   */
  if (quote != '\'' && quote != '\"') return 0;
  if (!(out = ptr = (char *)sbrk(strlen(input) * 2 + 2 + 1))) return 0;
  *ptr++ = quote;
  for (c = input;  *c;  c++) {
    switch (*c) {
      case '\'': case '\"':
        if (quote == *c) *ptr++ = *c;
        *ptr++ = *c;
        break;
      case '%': case '_': case '[': case ']':
        if (wildcards) *ptr++ = '\\';
        *ptr++ = *c;
        break;
      case '\\': *ptr++ = '\\'; *ptr++ = '\\'; break;
      case '\b': *ptr++ = '\\'; *ptr++ = 'b';  break;
      case '\n': *ptr++ = '\\'; *ptr++ = 'n';  break;
      case '\r': *ptr++ = '\\'; *ptr++ = 'r';  break;
      case '\t': *ptr++ = '\\'; *ptr++ = 't';  break;
      default:
        *ptr++ = *c;
        break;
    }
  }
  *ptr++ = quote;
  *ptr = 0;
  return out;
}

// func by  m0nad
void urlobfuscator (char * url, char * obf)
{
  int i;
  for (i = 0; i < (int)strlen (url); i++) 
   snprintf (obf+strlen(obf), sizeof obf, "%02X", url [i]);
//  obf [strlen (obf)] = 0;
   obf[i*2] = 0;
}

//base 64 encode
static inline char* b64_encode(char* str, unsigned long len) 
{

  const char b64[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     "abcdefghijklmnopqrstuvwxyz"
                     "0123456789+/";
  char *ret, *chunk;

  chunk = malloc(((len + 3) << 2) / 4);
  ret=chunk;

   do {
    if (len >= 3) 
    {
      unsigned long bitwise = (str[0] << 16) | (str[1] << 8) | str[2];

      *(chunk++) = b64[bitwise >> 18];
      *(chunk++) = b64[(bitwise >> 12) & 0x3F];
      *(chunk++) = b64[(bitwise >> 6) & 0x3F];
      *(chunk++) = b64[bitwise & 0x3F];
      len -= 3;
      str += 3;

    } else if (len == 2) {
      unsigned long bitwise = (str[0] << 16) | (str[1] << 8);

      *(chunk++) = b64[bitwise >> 18];
      *(chunk++) = b64[(bitwise >> 12) & 0x3F];
      *(chunk++) = b64[(bitwise >> 6) & 0x3D];
      *(chunk++) = '=';
      len -= 2;
      str += 2;

    } else {
      unsigned long bitwise = (str[0] << 16);;

      *(chunk++) = b64[bitwise >> 18];
      *(chunk++) = b64[(bitwise >> 12) & 0x3F];
      *(chunk++) = '=';
      *(chunk++) = '=';
      len--;
      str++;
    }
  } while(len); 
  
  *chunk=0;

  return ret;
}
//func by ryonagana
void changeCharacter(char *dest, const char* str, const char search, const char replace)
{
  while(*dest = *str)
  {
   if(*dest == search)
    *dest =  replace;
   *dest++;
   *str++;
  }
}

// return reverse string
char *strrev(char *str)
{
 char *p1, *p2;

 if(! str || ! *str)
  return str;
 for(p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
 {
  *p1 ^= *p2;
  *p2 ^= *p1;
  *p1 ^= *p2;
 }
 return str;
}


char *StrChunk(char *src, const int start, const int count)
{
 char *tmp,*tmp2;
 tmp = (char *)xmalloc(count+1);
 if (tmp == NULL) 
 {
  DEBUG("error");
  return NULL;
 }

 strncpy(tmp, src+start, count);
 tmp[count] = '\0';
 strncpy(tmp2,tmp,count);
 
 free(tmp);

 return tmp;
}

// simple split return array of strings between string separator
char **split(char *src, const char *token, int *total)
{ 
 char **str;
 register int i, j, count, item, start;
 int len;

 if(!src || !token) 
 {
  *total = 0;
  return NULL;
 }

 count = item = start = 0;
 j = 1;
 len = strlen(src);

 for(i = 0; i < len; i++) 
 {
  if(src[i] == *token)
   count++;
 }

 if(!count) 
 {
  *total = 0;
  return NULL;
 }

 str = (char **)xmalloc(count * sizeof(char *));
 if(str == NULL)
  DEBUG("error");

 for(i = 0; i < len; i++) 
 {
  if(src[i] != *token)
   j++;
  else {
   str[item] = (char *)xmalloc(j-start);
    if (str[item] == NULL) 
    {
     DEBUG("error");
     return NULL;
    }
   *(str+item) = StrChunk(src, start, j-1);
   str[item][j-start-1] = '\0';
   item++;
   start = j++;
  }
 }

 *(str+count) = (char *)xmalloc(j);
 if(str[count] == NULL)
  DEBUG("error");

 str[count] = StrChunk(src, start, j);
 str[count][j-start] = '\0';
 *total = ++count;

 free(str);

 return str;
}

// return string of bin file, coded by Mente Binária "http://www.mentebinaria.com.br/"
void strings(FILE *fp)
{
   unsigned char byte;
   int aux=0;
   int ofs=0;

   while (fread(&byte, sizeof(unsigned char), 1, fp))
   {   
      if (aux==1)
      {   
         putchar('\n');
         printf("%#x  ", ofs);
      }   
      else if (!ofs && isprint(byte))
         printf("0x0  ");

      if (isprint(byte))
      {   
         putchar(byte);
         aux=0;
      }   
      else aux++;

      ofs++;
   }   
   putchar('\n');
}