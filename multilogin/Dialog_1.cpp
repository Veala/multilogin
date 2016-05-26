#include "Dialog_1.h"

//------------------------Лог файл без реализации времени---------------------------
std::string log = "/tmp/multilogin.log";
std::ofstream logFile;

Dialog_1::Dialog_1(int x, int y, int w, int h) : Fl_Window(x, y, w, h) {
	//-------------------------Настройка окна диалога----------------------------
	color(0x00ffff00);
	label("Multilogin");
	dialog_2 = new Dialog_2(w,h);
	begin();
	tLogin = new Fl_Input(80,10,80,30,"Логин");
	tPassw = new Fl_Input(80,50,80,30,"Пароль");
	chCloseSessions = new Fl_Check_Button(10,100,80,30,"Завершить существующие сессии");
	button = new Fl_Button(290,100,80,30,"Вход");
	lBox = new Fl_Box(FL_DOWN_BOX, 0, 6*h/7, w, h/7, "");
	lBox->color(0xffffff00);
	end();
	button->callback(s_call_dialog_2, this);
	std::cout << "Hello!" << std::endl;

	//-------------------------Открытие лог файла--------------------------------
	logFile.open(log.c_str(), std::ios_base::app);
	logFile << "Multilogin запущен" << std::endl;
	lBox->label("Multilogin запущен");

};

void Dialog_1::s_call_dialog_2(Fl_Widget* w, void* f) {
	//----------------------Необходимые алгоритмы проверки логина и пароля--------
	Dialog_1 *D1 = (Dialog_1*)f;
	std::string log = D1->tLogin->value();
	std::string pas = D1->tPassw->value();  
	if ((log == "Igor") & (pas == "Alaev")) { //Условно
		D1->hide();
		D1->dialog_2->show();
		D1->dialog_2->position(D1->x_root(), D1->y_root());
		D1->dialog_2->logpas = log + ' ' + pas;
		D1->dialog_2->lBox->label("Логин и пароль корректны");
		logFile << "Логин и пароль корректны" << std::endl;

	} else {
		D1->lBox->label("Некорректный логин или пароль");
		logFile << "Некорректный логин или пароль" << std::endl;
		return;
	}

	//--------------------------Алгоритмы обработки завершения сессий--------------
	if (D1->chCloseSessions->value() == 1) {
		//Алгоритм 1
		std::cout << "Алгоритм 1" << std::endl;
	} else {
		//Алгоритм 2
		std::cout << "Алгоритм 2" << std::endl;
	}
};

Dialog_1::~Dialog_1() {
	std::cout << "Bye!" << std::endl;
	logFile.close();
	delete dialog_2;
};

