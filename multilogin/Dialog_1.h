#include <FL/Fl_Input.H>
#include "Dialog_2.h"

class Dialog_1 : public Fl_Window
{
	public:
		Dialog_1(int x, int y, int w, int h);
		~Dialog_1();
	private:
		Fl_Input *tLogin;
		Fl_Input *tPassw;
		Fl_Check_Button *chCloseSessions;
		Fl_Button *button;
		Fl_Box *lBox;
		Dialog_2* dialog_2;
		static void s_call_dialog_2(Fl_Widget*, void*);
};
