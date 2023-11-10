/*still in progress
task
task list
user
*/
#include<iostream>
#include<conio.h>
#include<list>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;
ofstream ufout("users.txt", ios::app);
ofstream tfout("tasks.txt", ios::app);

ifstream ufin("users.txt");
ifstream tfin("tasks.txt");

enum stages { not_started, work_in_progress, done };

class Task {
protected:
	string task_name;
	string task_details;
	stages stage;
	string deadline;
	
public:
	Task() {}
	Task(string task_name, string task_details, stages stage, string deadline) {
		this->task_name = task_name;
		this->task_details = task_details;
		this->stage = stage;
		this->deadline = deadline;
	}


	void display_task() const {
		cout << "Task name: " << task_name << endl;
		cout << "\nTask details: " << task_details << endl;
		cout << "\nStage: " << stage << endl;
		cout << "\nDeadline: " << deadline << endl;
	}

	static Task create_task() {
		Task ts;
		int stage_value;
	
		cout << "\nTask name: "; cin >> ts.task_name;
		cout << "\nTask details: "; cin >> ts.task_details;
		cout << "\nStage(0-not started, 1-in progress, 2-done): "; cin >> stage_value;
		if (stage_value >= 0 && stage_value <= 2) {
			ts.stage = static_cast<stages>(stage_value);
		}
		cout << "\nDeadline: "; cin >> ts.deadline;
		return ts;
	}

	string to_string() const {
			const char* v_stage[3] = { "0", "1", "2" };
			return task_name + "," + task_details + "," + (string)v_stage[stage] + "," + deadline + ";";
		}
	static Task string_to_task(string data) {
		Task rez;
		stringstream ss(data);
		string stage_value;

		getline(ss, rez.task_name, ',');
		getline(ss, rez.task_details, ',');
		getline(ss, stage_value, ',');
		const stages stgs[3] = { not_started, work_in_progress, done };
		rez.stage = stgs[stoi(stage_value)];
		getline(ss, rez.deadline, ',');
		return rez;
	 }
};


class TaskList {
protected:
	std::list<Task> tasks;
public:
	TaskList() {}
	void add_task(const Task& task) {
		tasks.push_back(task);
	}

	void display_task_list() const {
		for (const Task& task : tasks) {
			task.display_task();
			cout << "-----------";
		}
	}
	
	void save_to_file() const {
		string rez;
		for (const Task& task : tasks) {
		rez=rez + task.to_string();
		}
		tfout << rez + "\n";
	}

	static TaskList string_to_task_list(string data) {
		TaskList rez;
		stringstream ss(data);
		string token;

		while (getline(ss, token, ';')) {
			rez.add_task(Task::string_to_task(token));
		}
		return rez;
	 }


};

class User {
protected:
	string user_name;
	string password;
	TaskList task_list;
public:

	User() {}
	User(string user_name, string password) {
		this->password = password;
		this->user_name = user_name;
	}
	User register_user(list<User> data);
	void save_to_file();
	//void add_task_to_user() {
	void add_task_to_user() {
		Task new_task = Task::create_task();
		task_list.add_task(new_task);
	}
	void display_user_task_list() const {
		cout << "User: " << user_name << "'s Task List" << endl;
		task_list.display_task_list();
	}
	void save_task_list();
	/*string to_string() {
		return user_name + "," + password + "\n";
	}*/

	static User string_to_user(string data) {
		User rez;
		stringstream ss(data);

		getline(ss, rez.user_name, ',');
		getline(ss, rez.password, ',');
		return rez;
	}
	void populate_tasklist(const TaskList &data) const{
		const_cast<User*>(this)->task_list = data;
	}

	bool find_name(string name) const{
		return name == user_name;
	}

	bool verify_password(string pass) const {
		return pass == password;
	}

};

User User::register_user(std::list<User> data) {
	string u_n, p_w;
	
	cout << "\nUsername: "; cin >> u_n;
	cin.ignore();
	//functie anonima (fara nume) incepand cu  []
	auto it = find_if(data.begin(), data.end(), [&u_n](const User& user) {
		return user.find_name(u_n);
	});


	if (it != data.end()) {
		const User& foundUser = *it; // Access the value pointed to by it

		cout << "\nPassword: "; cin >> p_w;
		cin.ignore();
		if (foundUser.verify_password(p_w))
			return foundUser;
		else
			return User();
	}
	else {
		cout << "\nPassword: "; cin >> p_w;
		cin.ignore();
		User createdUser =  User(u_n, p_w);
		createdUser.save_to_file();
		return createdUser;
	}
	

}

void User::save_to_file() {
	if (ufout.is_open()) {
		ufout << user_name << "," << password << endl;
		ufout.close();
	}
}

void User::save_task_list() {
	task_list.save_to_file();
}



std::list<User> get_all_users(){
	std::list<User> rez;
	string line;
	while (getline(ufin, line)) {
		rez.push_back(User::string_to_user(line));
	}
	return rez;
}

std::list<TaskList> get_all_tasklists() {
	std::list<TaskList> rez;
	string line;
	while (getline(tfin, line)) {
		rez.push_front(TaskList::string_to_task_list(line));
	}
	return rez;
}

int main() {
	int opt;
	User user;

	if (ufin.is_open())
		cout << "Success!" << endl;
	else cout << "Failed to open users.txt!" << endl;

	if (tfin.is_open())
		cout << "Success!" << endl;
	else cout << "Failed to open tasks.txt!" << endl;
	std::list<User> users = get_all_users();
	std::list<TaskList> tasklists = get_all_tasklists();
	int i = 0;
	std::list<TaskList>::iterator it = tasklists.begin();
	for (const User& user : users) {
		advance(it, i);
		if (it != tasklists.end()) {
			user.populate_tasklist(*it);
			i++;
		}
		else {
		
			break;
		}
	
	}
	cout << "\nRegister: ";
	user = user.register_user(users);

	

	do {

		cout << "\nMenu: ";
		cout << "\n1. Display task list: ";
		cout << "\n2. Add task : ";
		cout << "\n3. Delete task based on name : ";
		cout << "\n4. Search for a task based on name  : ";
		cout << "------------------------------";
		cout << "\nOption: ";	cin >> opt;
		switch (opt) {
		case 0: break;
		case 1:
			user.display_user_task_list();
			cout << "\n";
			break;
		case 2:
			user.add_task_to_user();
			
			cout << "\n";
			break;
		case 3:

			cout << "\n";
			break;
		case 4:

			cout << "\n";
			break;
		}
	} while (opt);
	user.save_task_list();



	return 0;
}