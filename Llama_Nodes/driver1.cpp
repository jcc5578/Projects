/* File: driver1.cpp

   UMBC CMSC 341 Fall 2016 Project 1

   Basic tests for the Llama class.

   This driver program tests push() and pop() with strings.

*/

/*#include <iostream>
#include <string>
using namespace std ;

#include "Llama.h"

int main() {

   Llama<string,4> S ;

   // Push a bunch of strings 
   S.push("cdef") ;
   S.push("yzab") ;
   S.push("vwx") ;
   S.push("stu") ;
   
   S.push("pqr") ;
   S.push("mno") ;
   S.push("jkl") ;
   S.push("ghi") ;

   S.push("def") ;
   S.push("abc") ;
   S.dump() ;
   cout << endl;
   cout << "POP TEST" << endl;
   S.pop();
   S.pop();
   S.dump();
   cerr << "\n***** Dump using peek *****" ;
   cout << endl;
   // cout << "Peek at 0: " << S.peek(0) << endl;
   // cout << "Peek at 1: " << S.peek(1) << endl;
   // cout << "Peek at 2: " << S.peek(2) << endl;
   // cout << "Peek at 3: " << S.peek(3) << endl;
   // cout << "Peek at 4: " << S.peek(4) << endl;
   // cout << "Peek at 5: " << S.peek(5) << endl;
   // cout << "Peek at 6: " << S.peek(6) << endl;
   // cout << "Peek at 7: " << S.peek(7) << endl;
   // cout << "Peek at 8: " << S.peek(8) << endl;
   // cout << "Peek at 9: " << S.peek(9) << endl;

   int size = S.size() ;
   cerr << "\nsize = " << size << endl ;

   for (int i=0 ; i < size ; i++) {
      cerr << i << ": " << S.peek(i) << endl ;
   }

   
   // Pop some strings off
   string s1 ; 

   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   S.dump() ;  // should have "extra" node


   cerr << "\n***** Push Test *****\n" ;
   S.push("x789") ;
   S.push("x456") ;
   S.push("x123") ;

   S.dump() ;  // should use extra node


   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   S.dump() ;  // should have extra node again


   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   S.dump() ;  // extra node should be gone

   /*cerr << "\n***** Dup Test *****\n";
   s1 = S.dup();
   cerr << "dupped " << s1 << endl;
   S.dump();

   cerr << "\n***** Swap Test *****\n";
   s1 = S.swap();
   cerr <<"swapped " << s1 << endl;
   S.dump();
   

   return 0 ;
}*/
/* File: driver1.cpp

   UMBC CMSC 341 Fall 2016 Project 1

   Basic tests for the Llama class.

   This driver program tests push() and pop() with strings.

*/

#include <iostream>
#include <string>
using namespace std ;

#include "Llama.h"

int main() {

   Llama<string,4> S ;

   // Push a bunch of strings 

   S.push("cdef") ;
   S.push("yzab") ;
   S.push("vwx") ;
   S.push("stu") ;
   
   S.push("pqr") ;
   S.push("mno") ;
   S.push("jkl") ;
   S.push("ghi") ;

   S.push("def") ;
   S.push("abc") ;
   S.dump() ;


   cerr << "\n***** Dump using peek *****" ;
   int size = S.size() ;
   cerr << "\nsize = " << size << endl ;

   for (int i=0 ; i < S.size() ; i++) {
      cerr << i << ": " << S.peek(i) << endl ;
   }


   // Pop some strings off
   string s1 ; 

   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   S.dump() ;  // should have "extra" node


   cerr << "\n***** Push Test *****\n" ;
   S.push("x789") ;
   S.push("x456") ;
   S.push("x123") ;

   S.dump() ;  // should use extra node


   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   S.dump() ;  // should have extra node again


   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   S.dump() ;  // extra node should be gone


   return 0 ;
}