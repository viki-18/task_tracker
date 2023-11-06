/*
//bets Viki-350 linii de cod,  Vlad - 600;   viki- nu terminam pe 7.11.2023, Vlad- terminam pana la 5.AM pe 7.11.2023 
task
task list 
user
*/
#include<iostream>
#include<conio.h>
#include<list>

using namespace std;

enum stages { not_started, work_in_progress, done };
class Task {
protected:
	string task_name;
	string task_details;
	stages stage;
	string deadline;

public:
	Task();
	Task(string task_name, string task_details, stages stage, string deadline) {
		this->task_name = task_name;
		this->task_details = task_details;
		this->stage = stage;
		this->deadline = deadline;
	}

};

class TaskList {
protected:
	list<Task> tasks;
public:
	TaskList ();
	//aici metode 

};

class User {
protected:
	string user_name;
	string password;
	TaskList task_list;
public:
	User();
	User(string user_name, string password) {
		this->password = password;
		this->user_name = user_name;
	}
	void register();
};
 
void User::register() {
	string u_n, p_w;

	cout << "\nUsername: "; cin >> u_n;
	cout << "\nPassword: "; cin >> p_w;
	User *
}

int main() {


	return 0;
}