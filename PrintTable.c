#include "VariadicTable.h"

int main()
{
	{
		VariadicTable<std::string, double, int, std::string> vt({"Name", "Weight", "Age", "Brother"}, 10);
		vt.addRow("Cody", 180.2, 40, "John");
		vt.addRow("David", 175.2, 38, "Andrew");
		vt.addRow("Robert", 140.2, 27, "Fande");
		vt.print(std::cout);
	}
	return 0;
}
