#include <stdio.h>  // Εισαγωγή βιβλιωθηκών 
#include <math.h>

long long seen[1000];     //Δημιουργία πίνακα για ανίχνευση κύκλων 
int seen_count = 0;       //Μετράει πόσοι αριθμοί έχουν αποθηκευτή στον πίνακα 

// Υπολογίζει το άθροισμα των ορθών διαιρετών του n
long long aliquot_sum(long long n) {
    if (n <= 1) 
    return 0;
    long long sum = 1;     //Το ένα είναι πάντα διαιρέτης του n 
    long long sqrt_n = sqrt(n);   //Υπολογισμός τετραγωνικής ρίζας του n 

    // Έλεγχος όλων των αριθμών απο το 2 εώς την ρίζα 
    for (long long divisor = 2; divisor <= sqrt_n; divisor++) {
        if (n % divisor== 0) {              //Βρίσκω οτι το n διαρείται ακριβώς απο το divisor
            long long sub = n / divisor; 
            if (divisor!= sub)             //Βρίσκω τον συμπληρωματικό διαιρέτη 
                sum += divisor + sub;
            else
                sum += divisor;
        }
    }
    return sum;
}

// Έλεγχος αν έχουμε ξαναδεί το n
int has_seen(long long n) {
    for (int i = 0; i < seen_count; i++) {
        if (seen[i] == n)          
            return 1;      //Βρέθηκε κύκλος 
    }
    return 0;   //Δεν βρέθηκε κύκλος 
}

// Αποθήκευση του n στο ιστορικό
void add_seen(long long n) {
    if (seen_count < 10000)    //Έλεγχος μην ξεπεραστεί το επιτρεπόμενο μέγεθος
        seen[seen_count++] = n;   //Αυξηση του μετρητη κατα 1 
}

int main(void) {
    long long n;
    int maxl,count=0;
    char tos;

    printf("Please give the number to start the aliquot sequence from: ");  //Ζητάει απο τον χρήστη τον πρώτο αριθμό της ακολουθίας (n)
    if (scanf("%lld", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");  //Εκτύπωσει μηνύματος σε περίπτωση εσφαλμένης τιμής 
        return 1;
    }

    printf("Provide the max aliquot length to look for (0 for unlimited): "); //Ζητάει απο τον χρήστη το μέγιστο μήκος της ακολουθίας (maxl)
    if (scanf("%d", &maxl) != 1) {
        fprintf(stderr, "Invalid input.\n");  //Εκτύπωσει μηνύματος σε περίπτωση εσφαλμένης τιμής 
        return 1;
    }

    printf("Do you want to print the full sequence ('f') or just the length ('l')? "); //Ζητάει απο τον χρήστη τον τύπο της ακολουθίας (tos)
    if (scanf(" %c", &tos) != 1 || (tos != 'f' && tos != 'l')) {
        fprintf(stderr, "Invalid output mode. Use 'f' or 'l'.\n"); //Εκτύπωσει μηνύματος σε περίπτωση εσφαλμένης τιμής 
        return 1;
    }

    //Ελεγχος για υπερχείλιση (μην ξεπερνάει το 10^15)
    if (n > 1000000000000000LL) {
        fprintf(stderr, "Number exceeds maximum supported integer (%lld). Stopping.\n",1000000000000000LL);
        return 1;
    }

    if (tos == 'f')          //Αν επιλεχτεί το f τυπώνει τον πρώτο αριθμό (n)
        printf("%lld\n", n);  

    if (maxl == 0)
        add_seen(n);  // κρατά ιστορικό μόνο αν έχουμε unlimited (maxl=0)

    while (1) {
        if ( maxl!=0 && count>=maxl)    //Επαναλαβάνεται επι άπειρον ή μεχρι να φτάσει maxl=step αν έχει δοθεί όριο
         break;
        long long sum = aliquot_sum(n); //Υπολογισμός επόμενου όρου 

        //Ελεγχος για υπερχείλιση (μην ξεπερνάει το 10^15)
        if (sum > 1000000000000000LL) {
            fprintf(stderr, "Number exceeds maximum supported integer (%lld). Stopping.\n",1000000000000000LL);
            return 1;
        }
        
        count++;      //Με κάθε επανάληψη ο μετρητής count αυξάνεται κατα ένα 

        if (maxl == 0) {  // έλεγχος κύκλου μόνο αν maxl=0
            if (has_seen(sum)) {
                printf("Cycle detected at %lld after %d steps.\n", sum, count);
                break;
            }
            add_seen(sum);
        }

        n = sum;      //Το n παίρνει την τιμή του επόμενου όρου 

        if (tos == 'f')
            printf("%lld\n", n);    //Εκτύπωση νέου n 

        if (n == 0) {      //Τερματισμός επανάληψης σε περίπτωση που το n=0 
          break;
        }
    }

    if (tos == 'l')
        printf("Length of aliquot sequence: %d\n", count);  //Εκτύπωση μήκους ακολουθίας αν ο χρήστης επιλέξει l 

    return 0;
}
