#include <iostream>
#include <string>
using namespace std ;

#include "Llama.h"

int main()
{
    Llama<string,4> S ;
    cerr << "Dumping Test" << endl;
    S.push("one");
    S.push("two");
    S.push("three");
    S.push("four");

    S.push("five");
    S.push("six");
    S.push("seven");
    S.push("eight");

    S.push("nine");
    S.push("ten");
    S.dump();
    cerr << endl;
    cerr << "Popping test using peek function" << endl;
    for (int i = 0; i < S.size(); i++)
    {
        cerr << i << ". " << S.peek(i) << endl;
    }
    cerr << endl;
    cerr << "Popping Test: 3 pops" << endl;
    S.pop();
    S.pop();
    S.pop();
    S.dump();
    cerr << endl;
    cerr << "Pushing Test: 3 pushes" << endl;
    S.push("eleven");
    S.push("twelve");
    S.push("thirteen");
    S.dump();
    cerr << endl;
    cerr << "Swapping Test in same node" << endl;
    S.swap();
    S.dump();
    cerr << endl;
    cerr << "Swapping Test in different nodes: popping once and swapping after" << endl;
    S.pop();
    S.swap();
    S.dump();
    cerr << endl;
    cerr << "Duplicating Test into same node" << endl;
    S.dup();
    S.dump();
    cerr << endl;
    cerr << "Duplicating Test into different node: popping twice and duplicating" << endl;
    S.pop();
    S.pop();
    S.dup();
    S.dump();
    cerr << endl;
    cerr << "Popping duplicated top and pushing in 3 elements for clearer results" << endl;
    S.pop();
    S.push("fourteen");
    S.push("fifteen");
    S.push("sixteen");
    S.dump();
    cerr << endl;
    cerr << "Rotating Test" << endl;
    S.rot();
    S.dump();
    cerr << endl;
    cerr << "Creating empty node by popping 3 times." << endl;
    S.pop();
    S.pop();
    S.pop();
    S.dump();
    cerr << endl;
    cerr << "Deleting empty node by popping twice more" << endl;
    S.pop();
    S.pop();
    S.dump();

    Llama<string, 4> T(S);
    cerr << endl;
    cerr << "Copy Constructor" << endl;
    T.dump();

    Llama<string, 4> U;
    U = S;
    cerr << endl;
    cerr << "Overloaded Assigment Operator" << endl;
    U.dump();



}