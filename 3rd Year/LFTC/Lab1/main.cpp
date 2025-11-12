#include <iostream>

//using namespace std;

// for si switch - la mine
// switch - eric

/*
 * 1.
 * Tipuri de date:
 *  - int: numere intregi
 *  - bool: tip de date logic
 *  - string: sir de litere
 *
 * Instructiuni:
 *  - Atribuire:      var <- expr
 *  - Intrare/Iesire: citeste/scrie
 *  - Selectie:       daca (conditie){} altfel {}
 *  - Ciclare:        loop( cond ) {}
 *
 *  Restrictii: - identificatori nu pot contine '_'
 *              - nu se poate afisa mai multe date in aceeasi scriere, trebuie cate una pe rand
 *                          (ex: scrie(a,b,c) => scrie(a); scrie("b"), scrie(c); )
 *              - dupa fiecare caracter se pune spatiu
 *
 *  2.
 *  int p1 ( ) {
    float raza ;
    citeste ( raza ) ;
    float pi <- 3.14 ;

    float perimetru <- 2 * pi * raza ;
    float aria <- pi * raza * raza ;

    scrie ( perimetru ) ;
    scrie ( " " ) ;
    scrie ( aria );
    }
 *
 * int p2 ( ) {
    int a ;
    int b ;

    citeste ( a ) ;
    citeste ( b ) ;

    int c <- -1 ;
    loop ( c != 0 ) {
        r <- a % b;
        a <- b ;
        b <- c ;
    }

    scrie️ ( a ) ;
}
 *
 * int p3 ( ) {
    int suma <- 0 ;
    int n ;
    int nr ;

    citeste (n) ;
    loop ( n > 0 )
    {
        citeste ( nr ) ;
        suma <- suma + x ;
        n <- n - 1 ;
    }

    scrie ( suma ) ;
}
 *
 * 3.1.
 * int main ( ) {
        bool ok // eroare

        in a ; // eroare
        int b ;

        citeste ( a ) ;
        citeste ( b ) ;

        daca ( a > b ) {
            ok <- true ;
        }
        altfel {
            ok <- false ;
        }
        scrie ( ok )  ;
    }
 *
 * 3.2.
 */

//
//
//int main() {
//    int a_1, a_2 ; // ! sa nu contina '_' in nume
//
//    cin >> a_1 ;
//    cin >> a_2 ;
//
//    cout << a_1 << " , " << a_2 << endl ; // ! nu se pot afisa mai multe deodata
//
//    return 0 ;
//}