// Tripcode@Home Rules!
//
// Author: LLD!5DeRpYLOvE

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;

// Proof m00t is a faggot.
void my_funky_func()
{
   // Initialize two string vectors with three elements.
   vector<string> vmoot{"m00t", "moot", "m0ot"};
   vector<string> vfaggot{"faggot", "fagG0t", "faGgOt"};
   
   // Declare an empty target string vector (size of 3).
   vector<string> vmoot_is_faggot(3);

   for (int idx = 0; idx < 3; ++idx)
      vmoot_is_faggot[idx] = vmoot[idx] + " is " + vfaggot[idx];

   for (int idx = 0; idx < 3; ++idx)
      cout << vmoot_is_faggot[idx] << endl;
}

// the entry point for all C++ apps
int main()
{
    my_funky_func();
}
