#include "Dialog_2.h"

extern std::string log;
extern std::ofstream logFile;

Dialog_2::Dialog_2(int w, int h) : Fl_Window(w, h) {
	//----------------------Настройка окна диалога--------------------------
	color(0x00ffff00);
	label("Multilogin");
	begin();
	box = new Fl_Box(FL_DOWN_BOX,10,10,250,80,"");
	box->color(0xffffff00);
	chInternet = new Fl_Check_Button(10,10,80,30,"Интернет");
	chSecret = new Fl_Check_Button(10,30,80,30,"Секретно");
	chAbsSec = new Fl_Check_Button(10,50,80,30,"Совершенно секретно");
	chCloseSessions = new Fl_Check_Button(10,100,80,30,"Завершить существующие сессии");
	button = new Fl_Button(290,100,80,30,"Вход");
	button->callback(s_call_handler, this);
	lBox = new Fl_Box(FL_DOWN_BOX, 0, 6*h/7, w, h/7, "");
	lBox->color(0xffffff00);
	end();
};

void Dialog_2::s_call_handler(Fl_Widget* w, void* f) {
	Dialog_2 *D2 = (Dialog_2*)f;

	//--------------------Проверка на наличие выборки чекбоксов--------------
	if (!((D2->chInternet->value() == 1) || 
	    (D2->chSecret->value() == 1) ||
	    (D2->chAbsSec->value() == 1))) {
		logFile << "Не сделан выбор типа сервера" << std::endl;
		D2->lBox->label("Не сделан выбор типа сервера");
		return;
	}
	std::vector<std::string> check;
	if (D2->chInternet->value() == 1) check.push_back(std::string(D2->chInternet->label()));
	if (D2->chSecret->value() == 1) check.push_back(std::string(D2->chSecret->label()));
	if (D2->chAbsSec->value() == 1) check.push_back(std::string(D2->chAbsSec->label()));

	//--------------------Проверка наличия файлов----------------------------
	std::ifstream file1, file2;
	std::string strfile1 = "/root/.ssh/known_hosts";
	std::string strfile2 = "/opt/var/srv_color_label";

	file1.open(strfile1.c_str());
	file2.open(strfile2.c_str());

	if (!file1.is_open()) {
		std::string str = "Файл не может быть открыт: ";
		std::cout << str << strfile1 << std::endl;	
		logFile  << str << strfile1 << std::endl;
		D2->lBox->label((str + strfile1).c_str());
		return;
	}
	if (!file2.is_open()) {
		std::string str = "Файл не может быть открыт: ";
		std::cout << str << strfile2 << std::endl;	
		logFile << str << strfile2 << std::endl;
		D2->lBox->label((str + strfile2).c_str());
		return;
	}

	std::string lineToScript = D2->logpas;
	std::string TERM = " TERM";

	if (D2->chCloseSessions->value() == 1) lineToScript = lineToScript + TERM;
	std::cout << lineToScript << std::endl;

	//--------------------Выбор серверов из файлов и вектора check------------
	std::vector<std::string> main_line;
	std::string line, word, ipword;
	while (getline(file1, line)) {						//Выборка по первому файлу
		ipword.clear();
		std::istringstream sline(line);
		sline >> ipword;
		file2.clear();
		file2.seekg(0, std::ios::beg);
		line.clear();
		while (getline(file2, line)) {					//Выборка по второму файлу
			word.clear();
			std::istringstream sline2(line);
			getline(sline2, word, '=');
			if (word == ipword) {					//Сравнение ip
				getline(sline2, word, '='); word.clear();
				getline(sline2, word, '=');
				for (int c=0; c<check.size(); c++) {		//Выборка по чекбоксам
//					std::cout << word << std::endl;
					if (word==check[c]) {			//Сравнение имен
						main_line.push_back(line);
//						std::cout << line << std::endl;
						break;
					}
				}
			}
		}
	}

	//--------------------------Проверка наличия серверов---------------------
	if (main_line.size()==0) {
		logFile << "Нет ни одного сервера" << std::endl;
		D2->lBox->label("Нет ни одного сервера");
		return;
	}
	
	//--------------------------Формирование листа строк для скрипта-----------
	std::vector<std::string> listToScript;
	std::string colorWord, nameWord;
	for (int i=0; i<main_line.size(); i++) {
		line.clear();
		ipword.clear(); colorWord.clear(); nameWord.clear();
		std::istringstream sline(main_line[i]);
		getline(sline, ipword, '=');
		getline(sline, colorWord, '=');
		getline(sline, nameWord, '=');
		line = lineToScript + ' ' + colorWord + " \'" + nameWord + "\' " + ipword + " &";
//		std::cout << line << std::endl;
		listToScript.push_back(line);
	}
	
	//---------------------------Запуск скрипта в цикле-------------------------
	std::string script = "/opt/bin/tl-client.sh ";		//Файл должен быть chmod +x
	for (int i=0; i<listToScript.size(); i++)
		system((script + listToScript[i]).c_str());

	//--------------------------Завершение программы скрытием окна-------------
	D2->hide();
};

Dialog_2::~Dialog_2() {

}
