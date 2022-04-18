#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
  
  setlocale(LC_CTYPE, "");
  wchar_t star = 0x2605;
  wprintf(L"%C\n", star);
  wprintf(L"%lc\n", star);
  wprintf(L"sizeof wchar: %d\n", sizeof(star));
  return 0;
}
