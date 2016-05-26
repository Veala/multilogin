main:	main.o	Dialog_1.o	Dialog_2.o
	g++ `fltk-config --cxxflags` main.o Dialog_1.o Dialog_2.o `fltk-config --ldflags` -o multilogin
main.o:	main.cpp	Dialog_1.h
	g++ `fltk-config --cxxflags` main.cpp `fltk-config --ldflags` -c
Dialog_1.o:	Dialog_1.cpp	Dialog_1.h	Dialog_2.h
	g++ `fltk-config --cxxflags` Dialog_1.cpp `fltk-config --ldflags` -c
Dialog_2.o:	Dialog_2.cpp	Dialog_2.h
	g++ `fltk-config --cxxflags` Dialog_2.cpp `fltk-config --ldflags` -c
