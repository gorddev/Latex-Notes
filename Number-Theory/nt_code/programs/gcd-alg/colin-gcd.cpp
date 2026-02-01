#include <iostream>

using namespace std;

long eucAlg(long a, long b){
    long r=0;
    long c=a;
    long t=0;
    r=a%b;
    while(c>=0){
        c-=b;
        t++;
    }
    t--;
    cout<< "\t" << a << " &= "<<t<<"\\cdot " << b << " + "<<r<<"\\\\\n";

    if(r!=0)
    { b= eucAlg(b,r); }
    return b;
}

int main(){
    long a=0;
    long b=0;

    cout<<"What is a?"<<endl;
    cin>>a;
    cout<<"What is b?"<<endl;
    cin>>b;

    cout << "\n";
    cout << "\\begin{align*}\n";

    if(a<b){
        long c=a;
        a=b;
        b=c;
    }

    eucAlg(a,b);
    cout << "\\end{align*}\n";

    return 0;
}