#include "Dialog.h"
#include <stdio.h>
#include <string.h>

char* dialog[2] = {
"Hello, Pick Monster",
"Battle"
};

char* getLine(int line) {
return dialog[line];
}
