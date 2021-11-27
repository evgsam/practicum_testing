#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;


void AssertImpl(bool value, const string& t_str,  const string& file,
                     const string& func, unsigned line, const string& hint) {
   if (!value){
       cout << boolalpha;
       cout << file << "("s << line << "): "s << func << ": "s;
       cout << "ASSERT("s << t_str << ") failed."s;
       if (!hint.empty()) {
           cout << " Hint: "s << hint;
       }
       cout << endl;
       abort();

   }
}

#define ASSERT(expr) AssertImpl((expr), #expr, __FILE__, __FUNCTION__, __LINE__, ""s)/* реализовать самостоятельно */

#define ASSERT_HINT(expr, hint) AssertImpl((expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint)) /* реализовать самостоятельно */

int main() {
    string hello = "hello"s;
    ASSERT(!hello.empty());
    ASSERT_HINT(2 + 2 == 5,"This will fail"s);
}
