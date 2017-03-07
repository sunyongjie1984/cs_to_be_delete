#include "io_preamble.h"

int main()
{
    cout << "hi!" << flush; // flushes the buffer; adds no data
    cout << "hi!" << ends;  // inserts a null, then flushes the buffer
    cout << "hi!" << endl;  // inserts a newline, then flushes the buffer
    cout << unitbuf << "first" << " second" << nounitbuf;
    cout << "first" << flush << " second" << flush;
    cout << endl;
    return 0;
}
