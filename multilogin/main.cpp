#include "Dialog_1.h"
#include <FL/Fl.H>

int main(int argc, char** argv)
{
	Dialog_1 d1(300, 300, 400, 200);
	d1.show();
	return Fl::run();
}

  
