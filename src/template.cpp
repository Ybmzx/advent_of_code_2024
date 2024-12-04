#include <iostream>
using namespace std;
#define OUTPUT_FILE_NAME __FILE_NAME__ ".out"
int main() {
    freopen("input.in", "r", stdin);
    freopen(OUTPUT_FILE_NAME, "w", stdout);



    fclose(stdin);
    fclose(stdout);
    return 0;
}