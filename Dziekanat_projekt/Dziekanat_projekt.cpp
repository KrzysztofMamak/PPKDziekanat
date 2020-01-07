// Dziekanat_projekt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;

string* krotka;

//struktura daty, bo nie mo¿e byæ przechowywana jako string
struct DateTime {
	int rok;
	int miesiac;
	int dzien;
};

// struktura studenta ze wskaznikiem na nastepnego w liscie
struct Student {
	string imie;
	string nazwisko;
	int nrAlbumu;
	Student* next;
	Przedmiot* nextp; //kazdy student ma swoja liste przedmiotow
};

// struktura przedmiotu ze wskaznikiem na nastepny przedmiot na liscie
struct Przedmiot {
	string prowadzacy;
	string nazwa;
	float ocena;
	DateTime data;
	Przedmiot* next;
};

// odczyt pliku z protoko³em
void odczytProtokolu(string nazwaPliku) {
	Przedmiot p1;
	Student s1;
	int nrLinii = 1;
	int nrKrotki = 0;
	string linia;

	fstream plik;
	plik.open(nazwaPliku, ios::in);

	if (plik.good() == false) {
		cout << "Plik jest niedostepny!" << endl;
		exit(0);
	}
	else {
		while (getline(plik, linia)) {

			switch (nrLinii)
			{
				case 1:
					p1.nazwa = linia;
					break;

				case 2:
					p1.prowadzacy = linia;
					break;

				default:
					//krotka[nrKrotki] = linia;
					plik >> s1.imie >> s1.nazwisko >> s1.nrAlbumu >> p1.ocena >> p1.data.rok >> p1.data.miesiac >> p1.data.dzien;
					break;
			}
			nrKrotki++;

		}

		plik.close();
	}
}

void zapisDoPliku(Student s1) {
	string nazwaPliku = to_string(s1.nrAlbumu) + ".txt";
	fstream plik;
	plik.open(nazwaPliku, ios::out | ios::trunc);
	if (plik.good()==true) {

		string doZapisu = s1.imie + " " + s1.nazwisko + '\n' + "nr albumu: " + to_string(s1.nrAlbumu) + '\n' + '\n';
		plik >> doZapisu;
	}
}

void DodajNaPoczatkuStudenta(Student*& head, string imie, string nazwisko, int nrAlbumu)
{
	if (head == nullptr)	//gdy lista jest pusta								
	{
		head = new Student{ imie, nazwisko, nrAlbumu, nullptr };
	}
	else	//gdy lista nie jest pusta												
	{
		head = new Student{ head, nullptr }; //???? 
	}
}

void DodajNaPoczatkuPrzedmiot(Przedmiot*& head, string prowadzacy, string nazwa, float ocena, DateTime data)
{
	if (head == nullptr)	//gdy lista jest pusta								
	{
		head = new Przedmiot{ prowadzacy, nazwa, ocena, data, nullptr };
	}
	else	//gdy lista nie jest pusta												
	{
		head = new Przedmiot{ head, nullptr }; //????
	}
}

void DodajSortowanePrzedmiot(Przedmiot*& head, string prowadzacy, string nazwaP, float ocena, DateTime data)
{
	Przedmiot* tmpFirst = head;
	if (head == nullptr)	//gdy lista jest pusta
	{
		head = new Przedmiot{ prowadzacy, nazwaP, ocena, data, nullptr };
	}
	else if (nazwaP <= head-> nazwa) //dodaj na poczatek listy
	{
		head = new Przedmiot{ prowadzacy, nazwaP, ocena, data, head };
	}
	else
	{
		while (head)
		{
			if (head->next && nazwaP > head->next-> nazwa)	head = head->next;
			else if (head->next == nullptr)	//dodaj na koniec listy
			{
				head->next = new Przedmiot{ prowadzacy, nazwaP, ocena, data, nullptr };
			}
			else
			{
				head->next = new Przedmiot{ prowadzacy, nazwaP, ocena, data, head->next };	//dodaj wewnatrz listy
			}
		}
		head = tmpFirst;
	}
}

int main()
{
	odczytProtokolu("BazyDanych.txt");
}
