/*
Sa se modeleze 2 entitati de tip persoana care are urm proprietati : prenume si varsta
,student care are 3 proprietati : universitate facultate an studiu
Sa se creeze o lista de studenti si apoi un meniu care permite
1 adaugarea unui student in lista ,
2 afisarea stud din lista
3 cautarea dupa prenume
4 stergerea unui student dupa prenume
5 modificarea facultatii unui student dupa prenume
6 sortarea listei de studenti dupa prenume
*/

#include<iostream>
#include<string>
#include<list>
using namespace std;
class persoana {
private:
	string _prenume;
	int _varsta;

protected:
	persoana(string p, int v)
	{
		_prenume = p;
		_varsta = v;
	}
	persoana()
	{

	}
	void af()
	{
		cout << _prenume << endl << _varsta << endl;
	}
	string returnare_prenume()
	{
		return _prenume;
	}
};

class student : private persoana
{
	string _facultate;
	string _universitate;
	int _an_studiu;
public:
	student(string f, string u, int an, string p, int v) :persoana(p, v)
	{
		_facultate = f;
		_universitate = u;
		_an_studiu = an;
	}
	student()
	{

	}
	void afisare()
	{
		cout << _facultate << endl << _universitate << endl << _an_studiu << endl;
		af();
	}

	void modificare_fac(string fac)
	{
		_facultate = fac;
	}
	string returnare_prenume()
	{
		return persoana::returnare_prenume();
	}
};
student* adaugare()
{
	student *st;
	string p, u, f;
	int an, v;
	cout << "Introduceti prenumele" << endl;
	cin >> p;
	cout << "Introduceti universitatea" << endl;
	cin >> u;
	cout << "Introduceti facultatea" << endl;
	cin >> f;
	cout << "Introduceti varsta" << endl;
	cin >> v;
	cout << "Introduceti anul de studiu" << endl;
	cin >> an;
	st = new student(f, u, an, p, v);
	return st;
}
student* cautare(list<student*> *s)
{
	string pren;
	cout << "Introduceti prenumele" << endl;
	cin >> pren;
	for (student* stud : *s)
	{
		if (stud->returnare_prenume() == pren)
		{
			return stud;
		}
	}
	return nullptr;
}
void modificare(list<student*> *s)
{
	string fac;
	cout << "Introduceti noua facultate" << endl;
	cin >> fac;
	string pren;
	cout << "Introduceti prenumele" << endl;
	cin >> pren;
	for (student* stud : *s)
	{
		if (stud->returnare_prenume() == pren)
		{
			stud->modificare_fac(fac);
		}
	}
}
int main()
{
	list<student*> *s;
	s = new list<student*>;
	int opt, n = 0;
	do {
		cout << "Introduceti optiunea :" << endl << "1 adaugarea unui student in lista " << endl << "2 afisarea stud din lista";
		cout << endl << "3 cautarea dupa prenume";
		cout << endl << "4 stergerea unui student dupa prenume";
		cout << endl << "5 modificarea facultatii unui student dupa prenume";
		cout << endl << "6 sortarea listei de studenti dupa prenume";
		cout << endl << "0.Iesire";
		cin >> opt;
		switch (opt)
		{
		case 1:
			s->push_back(adaugare());
			n++;
			break;
		case 2:
			for (student* stud : *s)
			{
				stud->afisare();
			}
			break;
		case 3:
			cautare(s)->afisare();
			break;
		case 4:
			s->remove(cautare(s));
			n--;
			break;
		case 5:
			modificare(s);
			break;
		case 6:
			s->sort([](student* s1, student* s2) {
				return s1->returnare_prenume() < s2->returnare_prenume();
			});
			break;
		}
	} while (opt != 0);
	for (student* stud : *s)
		delete stud;
	return 0;
}