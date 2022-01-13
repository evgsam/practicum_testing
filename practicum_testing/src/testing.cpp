#include <fstream>
#include <string>
#include "log_duration.h"

using namespace std;

int main() {
    ofstream out_file("ballad.txt"s);
    {
    	LOG_DURATION("Text write"s);
    for (int i = 0; i < 50000; ++i) {
    	out_file << "С любимыми не расставайтесь"<<endl;
    }
    }
    throw;
}
