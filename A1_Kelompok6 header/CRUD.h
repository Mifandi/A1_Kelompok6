#ifndef CRUD_H
#define CRUD_H

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include <stdexcept>
#include <string.h>
#include <fstream>
#include <sstream>
#include <ctime>

#include "MenuFunction.h"
#include "data.h"

using namespace std;

string inputnama,inputpassword,kalender;
char pilih;
int index_user,lastday;


void color(int color);
void gotoxy(int x, int y);
void display(int x, int y,string indicator, string text, bool kondisi);
void display(int x, int y,string indicator, string text, bool kondisi,int custom);
void displayEdit(int x, int y,string indicator, string text, string att, bool kondisi);
void displayEdit(int x, int y,string indicator, string text, int att, string satuan, bool kondisi);
void cleaner (int max, int n, int vert,int horz);
void ResetAbsen(Akun *NodeAkun);
void tanggal(Akun* NodeAkun);
bool validasiLogin(const string& username, const string& password);
bool validasiUsername(const string& username);
void fixPrev(Akun **head , Akun **tail);
void fixID(Akun **head);

void menuAwal();
void menuUser(int akun);
void menuAdmin();
void Simpan(Akun *simpan);

void viewKaryawan(Akun *head);

extern Akun *Head;
extern Akun *Tail; 		

extern int jumlahKaryawan; 	
extern int jumlahHadir;		

Akun *KaryawanBaru(int ID,string USERNAME, string PASSWORD, string NAMA, string JABATAN,string ALAMAT,
long long NIK, string NOTELP, long long GAJI) {
	Akun *newKaryawan = new Akun;
	newKaryawan->id = ID;
	newKaryawan->username = USERNAME;
	newKaryawan->password = PASSWORD;
	newKaryawan->akun.nama = NAMA;
	newKaryawan->akun.jabatan = JABATAN;
	newKaryawan->akun.alamat = ALAMAT;
	newKaryawan->akun.nik = NIK;
	newKaryawan->akun.notelp = NOTELP;
	newKaryawan->akun.gaji = GAJI;
    newKaryawan->akun.tanggal=kalender;
    newKaryawan->akun.kehadiran="Belum Absen";
    newKaryawan->akun.jam="00:00";
	return newKaryawan;
}

void tambahPertama(Akun **head,int ID,string USERNAME, string PASSWORD, string NAMA, string JABATAN,string ALAMAT,
long long NIK, string NOTELP, long long GAJI){
	Akun *FirstNewKaryawan = KaryawanBaru(ID,USERNAME, PASSWORD, NAMA, JABATAN, ALAMAT, NIK, NOTELP, GAJI);
	Akun *tail = *head;
    FirstNewKaryawan->next = NULL;
    if (*head == NULL){
        FirstNewKaryawan->prev = NULL;
        *head = FirstNewKaryawan;
        FirstNewKaryawan->id = jumlahKaryawan;
        Simpan(Head);
        return;
    }
    while (tail -> next)
    {
        tail = tail->next;
    }
    tail->next = FirstNewKaryawan;
    FirstNewKaryawan->prev = tail;
    FirstNewKaryawan->id = jumlahKaryawan;
    Simpan(Head);
}

void tambah() {
    int bawah;
    int khusus1;
    int khusus2;
    int khusus3;
    system("cls");
	int counter = 1;
	string NIK,NOTELP,GAJI,USERNAME,PASSWORD,NAMA,JABATAN,ALAMAT = "";
	long long NIK1 = 0,GAJI1 = 0;
    int ID;
    int cordinat = 3;
    for(;;){
        color(1);gotoxy(0,0);cout << "=========================================================\n";
        gotoxy(0,1);color(1);cout << "|";color(7);cout<<"                       TAMBAH DATA                     ";color(1);cout<<"|\n";
        color(1);gotoxy(0,2);cout << "=========================================================\n";
        displayEdit(0,3," >", "Username :",USERNAME,counter == 1);
        displayEdit(0,4," >", "Password :",PASSWORD,counter == 2);
        displayEdit(0,5," >", "Nama     :",NAMA,counter == 3);
        displayEdit(0,6," >", "NIK      :",NIK,counter == 4);
        displayEdit(0,7," >", "Jabatan  :",JABATAN,counter == 5);
        displayEdit(0,8," >", "Alamat   :",ALAMAT,counter == 6);
        displayEdit(0,9," >", "Gaji     :",GAJI,counter == 7);
        displayEdit(0,10," >", "Telepon  :",NOTELP,counter == 8);
        if (NAMA == "") {
            bawah = 9;
            khusus1 = 0;
            khusus2 = 0;
            khusus3 = 9;
            display(24,12," >", "Kembali",counter == 9);
            color(6);gotoxy(0,13);cout << "=========================================================\n";
        }else {
            bawah = 11;
            khusus1 = 9;
            khusus2 = 10;
            khusus3 = 11;
            display(25,12," >", "Simpan",counter == 9);
            display(18,13," >", "Simpan Dan Tambah Lagi",counter == 10);
            display(24,14," >", "Kembali",counter == 11);
            color(6);gotoxy(0,15);cout << "=========================================================\n";
        }
        pilih = _getch();
        if(pilih == 72 && (counter <=bawah)){
            counter --;
            if (counter < 1){
                counter = bawah;
            }
        }
        if(pilih == 80 && (counter >=1)){
            counter ++;
            if (counter > bawah){
                counter = 1;
            }
        }if (pilih == '\r'){
            if (counter == 1){
                gotoxy(12,cordinat);fflush(stdin);getline(cin,USERNAME);
                if (!validasiUsername(USERNAME) || USERNAME == "admin"){
                    USERNAME = "";
                    gotoxy(0,khusus3 + 5);color(4);cout<<"Username sudah terdaftar"<<endl;
                    Sleep(1000);
                }
            }
            if (counter == 2){
                gotoxy(12,cordinat +1);fflush(stdin);getline(cin,PASSWORD);
            }
            if (counter == 3) {
                gotoxy(12,cordinat +2);fflush(stdin);getline(cin,NAMA);
            }
            if (counter == 4){
                try{
                    gotoxy(12,cordinat+3);fflush(stdin);getline(cin,NIK);
                    NIK1 = stoll(NIK);
                }catch(invalid_argument& e){
                    NIK1 = 0;
                    NIK = "";
                    gotoxy(0,khusus3 + 5);color(4);cout << "Harus Angka";
                    Sleep(1000);
                }
            }
            if (counter == 5){
                gotoxy(12,cordinat+4);fflush(stdin);getline(cin,JABATAN);
            }
            if (counter == 6){
                gotoxy(12,cordinat+5);fflush(stdin);getline(cin,ALAMAT);
            }
            if (counter == 7){
                try{
                    gotoxy(12,cordinat+6);fflush(stdin);getline(cin,GAJI);
                    GAJI1 = stoll(GAJI);
                }catch(invalid_argument& e){
                    GAJI1 = 0;
                    GAJI = "";
                    gotoxy(0,khusus3 + 5);color(4);cout << "Harus Angka";
                    Sleep(1000);
                }
            }if (counter == 8){
                try{
                    gotoxy(12,cordinat+7);fflush(stdin);getline(cin,NOTELP);
                    stoll(NOTELP);
                }catch(invalid_argument& e){
                    NOTELP = "";
                    gotoxy(0,khusus3 + 5);color(4);cout << "Harus Angka";
                    Sleep(1000);
                }
            }
            if (counter == khusus1){
                jumlahKaryawan++;
                ID = jumlahKaryawan;
                tambahPertama(&Head,ID,USERNAME, PASSWORD, NAMA, JABATAN, ALAMAT, NIK1, NOTELP, GAJI1);
                viewKaryawan(Head);
            }
            if (counter == khusus2){
                jumlahKaryawan++;
                ID = jumlahKaryawan;
                tambahPertama(&Head,ID,USERNAME, PASSWORD, NAMA, JABATAN, ALAMAT, NIK1, NOTELP, GAJI1);
                Simpan(Head);
                tambah();
            }if (counter == khusus3){
                viewKaryawan(Head);
            }
        }
        cleaner(14, 60, 0, 3);
    }
}

void update(Akun **head, int akun, string code){
    int counterAdmin1 = 0;
    int counterAdmin2 = 0;
    if (code == "admin2" || code == "admin3"){
        system("cls");
        if (*head == NULL){
            gotoxy(5,0);color(7);cout << "========================================\n";
            gotoxy(5,1);color(4);cout << "|               DATA KOSONG            |\n";
            gotoxy(5,2);color(7);cout << "========================================\n";
            system("pause");
            menuAdmin();
        }
        counterAdmin1 = 7;
        counterAdmin2 = 8;
    }
    int counter = 1;
    Akun *temp = (*head);
    while (temp != NULL){
        string USERNAME = temp->username;
        string PASSWORD = temp->password;
        string NAMA = temp->akun.nama;
        string JABATAN = temp->akun.jabatan;
        string ALAMAT = temp->akun.alamat;
        string NIK = to_string(temp->akun.nik);
        string NOTELP = temp->akun.notelp;
        string GAJI = to_string(temp->akun.gaji) ; 
        long long NIK1 = temp->akun.nik;
        long long GAJI1 = temp->akun.gaji;
        int cordinat = 3;
        if (temp->id == akun){
            for (;;)
            {
                color(1);gotoxy(0, 0);cout <<"=========================================================\n";
                gotoxy(0, 1);color(1);cout <<"|";color(7);cout<<"                        EDIT DATA                      ";color(1);cout<<"|\n";
                color(1);gotoxy(0, 2);cout << "=========================================================\n";
                displayEdit(0, 3, " >", "Username :", USERNAME, counter == 1);
                displayEdit(0, 4, " >", "Password :", PASSWORD, counter == 2);
                displayEdit(0, 5, " >", "Nama     :", NAMA, counter == 3);
                displayEdit(0, 6, " >", "NIK      :", NIK, counter == 4);
                displayEdit(0, 7, " >", "Alamat   :", ALAMAT, counter == 5);
                displayEdit(0, 8, " >", "Telepon  :", NOTELP, counter == 6);
                displayEdit(0, 9, " >", "Jabatan  :", JABATAN, counter == 7);
                displayEdit(0, 10, " >", "Gaji     : Rp.", GAJI, counter == 8);
                display(24, 12, " >", "Kembali", counter == 9);
                color(6);gotoxy(0, 13);
                cout << "=========================================================\n";
                pilih = _getch();
                if (pilih == 72 && (counter <= 9))
                {
                    counter--;
                    if (counter < 1)
                    {
                        counter = 9;
                    }
                }
                if (pilih == 80 && (counter >= 1))
                {
                    counter++;
                    if (counter > 9)
                    {
                        counter = 1;
                    }
                }
                if (pilih == '\r')
                {
                    if (counter == 1)
                    {
                        fflush(stdin);
                        gotoxy(12,cordinat);getline(cin, USERNAME);
                        if (!validasiUsername(USERNAME) || USERNAME == "admin")
                        {
                            gotoxy(0, 14);cout << "Username sudah terdaftar!!" << endl;
                            USERNAME = temp->username;
                            Sleep(1000);
                        }
                    }
                    if (counter == 2)
                    {
                        fflush(stdin);
                        gotoxy(12,cordinat +1);getline(cin, PASSWORD);
                    }
                    if (counter == 3)
                    {
                        fflush(stdin);
                        gotoxy(12,cordinat+2);getline(cin, NAMA);
                    }
                    if (counter == 4)
                    {
                        try
                        {
                            fflush(stdin);
                            gotoxy(12,cordinat+3);getline(cin, NIK);
                            NIK1 = stoll(NIK);
                        }
                        catch (invalid_argument &e)
                        {
                            NIK = to_string(temp->akun.nik);
                            NIK1 = temp->akun.nik;
                            gotoxy(0, 14);color(4);cout << "Harus Angka";
                            Sleep(1000);
                        }
                    }
                    if (counter == 5)
                    {
                        fflush(stdin);
                        gotoxy(12,cordinat+4);getline(cin, ALAMAT);
                    }
                    if (counter == 6)
                    {
                        try
                        {
                            fflush(stdin);
                            gotoxy(12,cordinat+5);getline(cin, NOTELP);
                            stoll(NOTELP);
                        }
                        catch (invalid_argument &e)
                        {
                            NOTELP = temp->akun.notelp;
                            gotoxy(0, 14);color(4);cout << "Harus Angka";
                            Sleep(1000);
                        }
                    }
                    if (counter == counterAdmin1)
                    {
                        fflush(stdin);
                        gotoxy(12,cordinat+6);getline(cin, JABATAN);
                    }
                    if (counter == counterAdmin2)
                    {
                        try
                        {
                            fflush(stdin);
                            gotoxy(16,cordinat+7);getline(cin, GAJI);
                            GAJI1 = stoll(GAJI);
                        }
                        catch (invalid_argument &e)
                        {
                            GAJI = to_string(temp->akun.gaji);
                            GAJI1 = temp->akun.gaji;
                            gotoxy(0, 14);color(4);cout << "Harus Angka";
                            Sleep(1000);
                        }
                    }
                    if (counter == 9){
                        temp->password = PASSWORD;
                        temp->username = USERNAME;
                        temp->akun.nama = NAMA;
                        temp->akun.jabatan = JABATAN;
                        temp->akun.alamat = ALAMAT;
                        temp->akun.gaji = GAJI1;
                        temp->akun.nik = NIK1;
                        temp->akun.notelp = NOTELP;
                        Simpan(Head);
                        if (code == "admin2"){
                            menuAdmin();
                        }else if (code == "admin3") {
                            viewKaryawan(Head);
                        }
                        else{
                            menuUser(akun);
                        }
                    }
                }
                cleaner(17, 50, 0, 1);
            }
        }
        temp = temp->next;
    }
    system("cls");
    gotoxy(5,0);color(7);cout << "========================================\n";
    gotoxy(5,1);color(4);cout << "|          AKUN TIDAK DITEMUKAN        |\n";
    gotoxy(5,2);color(7);cout << "========================================\n";
    Sleep(1000);
    if (code == "admin" || code == "admin2"){
        menuAdmin();
    }else if (code == "admin3") {
        viewKaryawan(Head);
    }
    else{
        menuUser(akun);
    }
}

void hapus(Akun **head, string posisi) {
    if (*head == NULL){
        system("cls");
        gotoxy(5,0);color(7);cout << "========================================\n";
        gotoxy(5,1);color(4);cout << "|              DATA KOSONG             |\n";
        gotoxy(5,2);color(7);cout << "========================================\n";
        gotoxy(5,3);system("pause");
        viewKaryawan(Head);
    }
    if (*head == NULL || stoi(posisi) <= 0){
        system("cls");
        gotoxy(5,0);color(7);cout << "========================================\n";
        gotoxy(5,1);color(4);cout << "|          AKUN TIDAK DITEMUKAN        |\n";
        gotoxy(5,2);color(7);cout << "========================================\n";
        Sleep(1000);
        return;
    }
    Akun* current = *head;
    int i;
    for (i = 1; current != NULL && i < stoi(posisi); i++){
        current = current->next;
    }
    if (current == NULL){   
        system("cls");
        gotoxy(5,0);color(7);cout << "========================================\n";
        gotoxy(5,1);color(4);cout << "|          AKUN TIDAK DITEMUKAN        |\n";
        gotoxy(5,2);color(7);cout << "========================================\n";
        Sleep(1000);
        return;
    }
    if (*head == NULL || current == NULL) {
        return;
    }
    if (*head == current) {
        *head = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    free(current);
    jumlahKaryawan--;
    system("cls");
    fixID(&Head);
    Simpan(Head);
    gotoxy(5,0);color(7);cout << "=========================================\n";
    gotoxy(5,1);color(2);cout << "|          DATA BERHASIL DIHAPUS        |\n";
    gotoxy(5,2);color(7);cout << "=========================================\n";
    Sleep(1000);
}


Absen *findNode(Absen *head, int idx)
{
    for (int a = 0; a < idx; a++)
    {
        head = head->next;
    }
    return head;
}

void shellSort(Absen *head, int code){
    for (int gap = jumlahHadir / 2; gap > 0; gap /= 2)
    {
            for (int i = gap; i < jumlahHadir; i++)
            {
                string temp = findNode(head, i)->nama;
                string kehadiran = findNode(head, i)->kehadiran;
                string tanggal = findNode(head, i)->tanggal;
                string jam = findNode(head, i)->jam;
                int j;
                if (code == 1){
                    for (j = i; j >= gap && findNode(head, j - gap)->nama > temp; j -= gap)
                    {
                        findNode(head, j)->nama = findNode(head, j - gap)->nama;
                        findNode(head, j)->kehadiran = findNode(head, j - gap)->kehadiran;
                        findNode(head, j)->tanggal = findNode(head, j - gap)->tanggal;
                        findNode(head, j)->jam = findNode(head, j - gap)->jam;
                    }
                }else if (code == 2){
                    for (j = i; j >= gap && findNode(head, j - gap)->nama < temp; j -= gap)
                    {
                        findNode(head, j)->nama = findNode(head, j - gap)->nama;
                        findNode(head, j)->kehadiran = findNode(head, j - gap)->kehadiran;
                        findNode(head, j)->tanggal = findNode(head, j - gap)->tanggal;
                        findNode(head, j)->jam = findNode(head, j - gap)->jam;
                    }
                }
                findNode(head, j)->nama = temp;
                findNode(head, j)->kehadiran = kehadiran;
                findNode(head, j)->tanggal = tanggal;
                findNode(head, j)->jam = jam;
        }
        
    }
}


void shellSort2(Absen *head, int code){
    for (int gap = jumlahHadir / 2; gap > 0; gap /= 2)
    {
            for (int i = gap; i < jumlahHadir; i++)
            {
                string temp = findNode(head, i)->jam;
                string kehadiran = findNode(head, i)->kehadiran;
                string tanggal = findNode(head, i)->tanggal;
                string nama = findNode(head, i)->nama;
                int j;
                if (code == 1){
                    for (j = i; j >= gap && findNode(head, j - gap)->jam > temp; j -= gap)
                    {
                        findNode(head, j)->jam = findNode(head, j - gap)->jam;
                        findNode(head, j)->kehadiran = findNode(head, j - gap)->kehadiran;
                        findNode(head, j)->tanggal = findNode(head, j - gap)->tanggal;
                        findNode(head, j)->nama = findNode(head, j - gap)->nama;
                    }
                }else if (code == 2){
                    for (j = i; j >= gap && findNode(head, j - gap)->jam < temp; j -= gap)
                    {
                        findNode(head, j)->jam = findNode(head, j - gap)->jam;
                        findNode(head, j)->kehadiran = findNode(head, j - gap)->kehadiran;
                        findNode(head, j)->tanggal = findNode(head, j - gap)->tanggal;
                        findNode(head, j)->nama = findNode(head, j - gap)->nama;
                    }
                }
                findNode(head, j)->jam = temp;
                findNode(head, j)->kehadiran = kehadiran;
                findNode(head, j)->tanggal = tanggal;
                findNode(head, j)->nama = nama;
        }
        
    }
}

const int NO_OF_CHARS = 256;


string toLowerCase(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}

void badCharHeuristic(const string& str, int size, int badChar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badChar[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        badChar[(int)tolower(str[i])] = i;
    }
}

int BoyerMoore(Akun* head, const string& pat, int corx, int cory) {
    bool found = false;

    int m = pat.size();
    string pattern = toLowerCase(pat);

    Akun* current = head;
    while (current != nullptr) {
        int n = current->akun.nama.size();
        int badChar[NO_OF_CHARS];
        badCharHeuristic(current->akun.nama, n, badChar);

        int shift = 0;
        while (shift <= (n - m)) {
            int j = m - 1;
            while (j >= 0 && pattern[j] == tolower(current->akun.nama[shift + j])) {
                j--;
            }
            if (j < 0) {
                found = true;
                gotoxy(corx, cory);cout<<"|"<<current->id<<".|"<< current->akun.nama<<endl;
                cory++;
                break;
            }
            shift += (j >= 0) ? max(1, j - badChar[tolower(current->akun.nama[shift + j])]) : 1;
        }
        current = current->next;
    }
    if (!found) {
        system("cls");
        gotoxy(5,0);color(7);cout << "========================================\n";
        gotoxy(5,1);color(4);cout << "|          AKUN TIDAK DITEMUKAN        |\n";
        gotoxy(5,2);color(7);cout << "========================================\n";
        Sleep(1000);
        viewKaryawan(Head);
    }
    return cory;
}

#endif
