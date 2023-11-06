/*
Să se realizeze un program cu următoarele clase:
a. Persoana (nume, prenume, varsta)
b. Angajat (departament, vechime) moștenește persoana
c. Sef (numar angajati in subordine, proiect) moștenește angajat
Să se creeze funcții de adăugare și afișare a datelor pentru angajați și pentru șefi, precum și
posibilitatea de a căuta sau șterge angajați/șefi. Pentru fiecare clasă (angajat, sef) se va folosi
o listă simplu înlănțuită.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<conio.h>
#include<string>
using namespace std;
class Persoana {
protected:
	string nume;
	string prenume;
	int varsta;
public:
	Persoana(); //constructor vid
	Persoana(string nume, string prenume, int varsta) {
		nume = new char[20];
		prenume = new char[20];
		this->nume = nume;
		this->prenume = prenume;
		this->varsta = varsta;
	}
	//FUNCTIE VIRTUALA PURA
	virtual void afisare() = 0;

};

class Angajat : public Persoana {
protected:
	string departament;
	int vechime;
	Angajat *head, *next, *ult;
public:
	Angajat(); //constructor vid
	Angajat(string nume, string prenume, int varsta, string departament, int vechime) : Persoana(nume, prenume, varsta) {
		head = NULL;
		departament = new char[20];
		this->departament = departament;
		this->vechime = vechime;
	}
	void adaugare();
	void  virtual afisare();
	void cautare(int);
	void stergere(int);
};

class Sef : public Angajat {
protected:
	int nr_angajati_in_subordine;
	string proiect;
	Sef* head, *next, *ult;
public:
	Sef();//construcor vid
	Sef(string nume, string prenume, int varsta, string departament, int vechime, int nr_angajati_in_subordine, string proiect) : Angajat(nume, prenume, varsta, departament, vechime) {
		head = NULL;
		proiect = new char[20];
		this->nr_angajati_in_subordine = nr_angajati_in_subordine;
		this->proiect = proiect;
	}
	void adaugare();
	void virtual afisare();
	void cautare(string);
	void stergere(string);
};

void Angajat::adaugare() {
	Angajat *p = new Angajat(nume, prenume, varsta, departament, vechime);
	cout << "\nNume angajat"; cin >> p->nume;
	cin.ignore();
	cout << "\nPrenume angajat "; cin >> p->prenume;
	cin.ignore();
	cout << "\nVarsta angajat"; cin >> p->varsta;
	cout << "\nDepartament angajat "; cin >> p->departament;
	cout << "\nVechime angajat"; cin >> p->vechime;
	p->next = head;
	head = p;
}

void Sef::adaugare() {
	Sef *p = new Sef(nume, prenume, varsta, departament, vechime, nr_angajati_in_subordine, proiect);
	cout << "\nNume sef"; cin >> p->nume;
	cin.ignore();
	cout << "\nPrenume sef"; cin >> p->prenume;
	cin.ignore();
	cout << "\nVarsta sef"; cin >> p->varsta;
	cout << "\nDepartament sef"; cin >> p->departament;
	cout << "\nVechime sef"; cin >> p->vechime;
	cout << "\nNr de angajati in subordine"; cin >> p->nr_angajati_in_subordine;
	cout << "\nProiect "; cin >> p->proiect;
	p->next = head;
	head = p;
}

void Angajat::afisare() {
	Angajat *p = head;
	while (p != NULL) {
		cout << "Nume angajat: " << p->nume << endl;
		cout << "Prenume angajat :" << p->prenume << endl;
		cout << "Varsta angajat :" << p->varsta << endl;
		cout << "Departament angajat :" << p->departament << endl;
		cout << "Vechime angajat :" << p->vechime << endl;
		p = p->next;
	}
}

void Sef::afisare() {
	Sef *p = head;
	while (p != NULL) {
		cout << "Nume sef: " << p->nume << endl;
		cout << "Prenume sef :" << p->prenume << endl;
		cout << "Varsta sef :" << p->varsta << endl;
		cout << "Departament sef :" << p->departament << endl;
		cout << "Vechime sef :" << p->vechime << endl;
		cout << "Nr angajati in subordine:" << p->nr_angajati_in_subordine << endl;
		cout << "Proiect: " << p->proiect << endl;
		p = p->next;
	}
}

void Angajat::cautare(int varsta_cautata) {
	//caut dupa varsta
	Angajat *p = head;
	bool gasit = false;
	while (p != NULL) {
		if (p->varsta == varsta_cautata) {
			cout << "Nume angajat: " << p->nume << endl;
			cout << "Prenume angajat :" << p->prenume << endl;
			cout << "Varsta angajat :" << p->varsta << endl;
			cout << "Departament angajat :" << p->departament << endl;
			cout << "Vechime angajat :" << p->vechime << endl;
			gasit = true;
		}
		p = p->next;
	}
	if (!gasit)
		cout << "\n Nu exista angajatul cu varsta respectiva ";
}

void Sef::cautare(string departament_de_cautat) {
	Sef* p = head;
	bool gasit = false;
	while (p != NULL) {
		if (p->departament == departament_de_cautat) {
			cout << "Nume sef: " << p->nume << endl;
			cout << "Prenume sef :" << p->prenume << endl;
			cout << "Varsta sef :" << p->varsta << endl;
			cout << "Departament sef :" << p->departament << endl;
			cout << "Vechime sef :" << p->vechime << endl;
			cout << "Nr angajati in subordine:" << p->nr_angajati_in_subordine << endl;
			cout << "Proiect: " << p->proiect << endl;
			gasit = true;
		}
		p = p->next;
	}
	if (!gasit)
		cout << "Nu exista seful cu departamentul cautat" << endl;
}

void Angajat::stergere(int vechime_de_sters) {
	Angajat *c, *a; //c pastram, a nb
	c = head;
	if (head->vechime == vechime_de_sters) {
		a = head;
		head = head->next;
		delete a;
	}
	else {
		while (c->next->vechime != vechime_de_sters)
			c = c->next;
		a = c->next;
		c->next = a->next;

		if (a == ult)
			ult = c;
		delete a;
	}
} //nu mi iese ceva la stergere 

void Sef::stergere(string proiect_de_sters) {
	Sef *c, *a; //c pastram, a nb
	c = head;
	if (head->proiect == proiect_de_sters) {
		a = head;
		head = head->next;
		delete a;
	}
	else {
		while (c->next->proiect != proiect_de_sters)
			c = c->next;
		a = c->next;
		c->next = a->next;

		if (a == ult)
			ult = c;
		delete a;
	}
} //nu mi iese ceva la stergere 


int main() {
	int opt;
	int varsta_cautata;
	string departament_de_cautat;
	int vechime_de_sters;
	string proiect_de_sters;
	Angajat* a = new Angajat(" ", " ", 0, " ", 0);
	Sef* s = new Sef(" ", " ", 0, " ", 0, 0, " ");
	do {
		cout << "\n 1.Adaugare angajat ";
		cout << "\n 2. Adaugare sef";
		cout << "\n 3. Afisare angajat ";
		cout << "\n 4. Afisare sef";

		cout << "\n Introduceti optiunea dorita: "; cin >> opt;

		switch (opt) {
		case 1:
			a->adaugare();
			cout << "\n";
			break;
		case 2:
			s->adaugare();
			cout << "\n";
			break;
		case 3:
			a->afisare();
			cout << "\n";
			break;
		case 4:
			s->afisare();
			cout << "\n";
			break;
		case 5:
			cout << "Varsta dupa care doriti sa cautati angajatul: ";
			cin >> varsta_cautata;
			a->cautare(varsta_cautata);
			cout << "\n";
			break;
		case 6:
			cout << "Departamentul dupa care doriti sa cautati seful: ";
			cin >> departament_de_cautat;
			s->cautare(departament_de_cautat);
			cout << "\n";
			break;
		case 7:
			cout << "Vechimea dupa care doriti sa stergeti angajatul: ";
			cin >> vechime_de_sters;
			a->stergere(vechime_de_sters);
			cout << "\n";
			break;
		case 8:
			cout << "Proiectul dupa care doriti sa stergeti seful: ";
			cin >> proiect_de_sters;
			s->stergere(proiect_de_sters);
			cout << "\n";
			break;

		case 0: break;

		}
	} while (opt);
	return 0;
}