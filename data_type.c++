#include <iostream>
#include <iomanip> 
using namespace std;
int main(){
int i;
long long ll;
char ch;
float f;
double d;
if(!(cin>>i>>ll>>ch>>f>>d))return 0;
cout<<i<<endl;
cout<<ll<<endl;
cout<<ch<<endl;
cout<<fixed<<setprecision(2)<<f<<endl;
cout<<fixed<<setprecision(1)<<d<<endl;
return 0;
}