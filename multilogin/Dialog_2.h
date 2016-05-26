#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Dialog_2 : public Fl_Window
{
	public:
		Dialog_2(int w, int h);
		std::string logpas;
		Fl_Box *lBox;
		~Dialog_2();
	private:
		Fl_Box *box;
		Fl_Check_Button *chInternet;
		Fl_Check_Button *chSecret;
		Fl_Check_Button *chAbsSec;
		Fl_Check_Button *chCloseSessions;
		Fl_Button *button;
		static void s_call_handler(Fl_Widget*, void*);

};

