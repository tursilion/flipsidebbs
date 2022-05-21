/*
** string function library
** by Tom Wible
** modifed by Mike Ward (index)
** for use with the Flip Side
*/
strlen(s) /* returns string length*/
char *s;
{
     int n;
     n = 0;
     while (*s++)
          ++n;
     return (n);
}

strcmp(s1, s2) /* compares s1 to s2, returns n<0 if s1 before s2, etc*/
char *s1, *s2;
{
     int r12;
     while ((*s1) | (*s2)) {
          r12 = (*s1) - (*s2);
          if (r12)
               return (r12);
          else {
               ++s1;
               ++s2;
          }
     }
     return (0);
}


index(s, c) /* returns location of c in s */
char s[], c[];
{
     int n,x,y;
     n = 0;
     x=strlen(c);
     while (s[n])
     { y=0; x=0;
       while (c[x])
         if (s[n+x]!=c[x++]) y=1;
       if (y==0)
         return (n+1);
       else n++;
     }
     return (0);
}

strcat(s1, s2) /* concatenate s2 to end of s1*/
char *s1, *s2;
{
     char *p;
     p = s1;   /*point to s1*/
     while (*p++)
          ;    /*point to end of s1*/
     --p;
     while ((*p++) = (*s2++))
          ;    /*move s2 to end of s1*/
     return;
}


strcpy(s1, s2) /*copy s2 into s1*/
char *s1, *s2;
{
     while ((*s1++) = (*s2++))
          ;
     return;
}
