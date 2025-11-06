#include <stdio.h> 
int main() { 
  long long n,sum,sum2,pre=0; 
    int maxl,count=0,divisor; 
    char tos; 
    if (scanf("%lld %d %c", &n, &maxl, &tos)!= 3) { 
        fprintf(stderr, "Invalid input.\n"); 
        return 1; 
    } 
    if (tos != 'f' && tos != 'l') 
    { fprintf(stderr,"Invalid output mode. Use 'f' or 'l'.\n");
     return 1; 
    } 
    if (n > 1000000000000000LL) { 
        fprintf(stderr," Number exceeds maximum supported integer(1000000000000000).Stopping\n");
         return 1;
         } 
         while (n != 0 && (maxl == 0 || count < maxl)) 
         { sum=0; for (divisor=1;divisor<=n/2;divisor++){
             if (n%divisor==0) sum+=divisor;
             }
              if (tos=='f') { 
                printf ("%lld\n", n); } 
                pre=n; 
                n=sum; 
                count++; 
            } 
            if (tos=='l'){ 
            printf("Length of aliquot sequence %d\n:",count);
         } 
            if (sum == n ) { 
                if (tos == 'f') 
                    printf("%lld\n", n);
            } 
            if (sum == pre && n != sum && pre != 0) { 
                if (tos == 'f') {
                printf("%lld\n", sum); 
                }
            } 
            sum2 = sum; if (sum2 == n && sum != n ) { 
                if (tos == 'f') 
                printf("%lld and %lld\n", n, sum); 
            } 
            return 0; 
        }
