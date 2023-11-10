#ifndef MenuFunction_H
#define MenuFunction_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string> 
#include <vector>
#include <algorithm>
#include <windows.h>

#include "CRUD.h"
#include "lamaran.h"

using namespace std;

// Fungsi untuk mengatur warna teks di konsol
void color(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

// Fungsi untuk memindahkan kursor ke posisi tertentu di layar
void gotoxy(int x, int y){
    COORD c;
    c.X=x + 30;
    c.Y=y + 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

// Fungsi untuk menampilkan teks dengan indikator dan kondisi
void display(int x, int y,string indicator, string text, bool kondisi){
    gotoxy(x, y);
    if (kondisi){
        color(3); 
        cout<<indicator<< text;
    }else{
        color(7); 
        cout<< "  "<<text;
    }
}

// Fungsi untuk menampilkan teks dengan penyorotan berdasarkan kondisi dan warna kustom
void display(int x, int y,string indicator, string text, bool kondisi,int custom){
    gotoxy(x, y);
    if (kondisi){
        color(custom); 
        cout<<indicator<< text;
    }else{
        color(7); 
        cout<< "  "<<text;
    }
}

// Menampilkan opsi pengeditan teks dengan indikator, teks, dan atribut tertentu pada posisi layar tertentu
void displayEdit(int x, int y,string indicator, string text, string att, bool kondisi){
    gotoxy(x, y);
    if (kondisi){
        color(3); 
        cout<<indicator<<text<<att;
    }else{
        color(7); 
        cout<< "  "<<text<<att;
    }
}

// Menampilkan opsi pengeditan teks dengan indikator, teks, dan atribut tertentu pada posisi layar tertentu
void displayEdit(int x, int y,string indicator, string text, int att, string satuan, bool kondisi){
    gotoxy(x, y);
    if (kondisi){
        color(3); 
        cout<<indicator<<text<<att<<satuan;
    }else{
        color(7); 
        cout<< "  "<<text<<att<<satuan;
    }
}

// Fungsi untuk membersihkan tampilan pada layar konsol
void cleaner (int max,int n, int horz, int vert) {
    for (int i = 0; i <= max;i++){
        gotoxy(horz, vert + i);cout<<string(n + 1, ' ');
    }
}

// Fungsi untuk mereset data absensi karyawan
void ResetAbsen(Akun **head){
    Akun *temp = (*head);
    while (temp != NULL){
        temp->akun.tanggal=kalender;
        temp->akun.kehadiran="Belum Absen";
        temp->akun.jam="00:00";
        temp = temp->next;
    }
	Simpan(Head);
}

// Fungsi untuk mengatur tanggal untuk setiap karyawan
void tanggal(Akun **head) {
    time_t sekarang = time(0);
    tm* waktu = localtime(&sekarang);
    int tanggal = waktu->tm_mday;
    int bulan = waktu->tm_mon + 1;
    int tahun = waktu->tm_year + 1900;

    string strTanggal = to_string(tanggal);
    string strBulan = to_string(bulan);
    string strTahun = to_string(tahun);

    if (*head == NULL){
        kalender = strTanggal + "/" + strBulan + "/" + strTahun;
        return;
    }

    Akun *temp = (*head);
    if (temp->akun.tanggal == "") {
        lastday = 0;
        kalender = strTanggal + "/" + strBulan + "/" + strTahun;
        ResetAbsen(&Head);
    } else {
        kalender = temp->akun.tanggal;
        lastday = stoi(kalender.substr(0, kalender.find("/")));
        if (lastday != tanggal) {
            kalender = strTanggal + "/" + strBulan + "/" + strTahun;
            lastday = tanggal;
            ResetAbsen(&Head);
        }
    }
}

void clear(Akun** head){ //Berfungsi untk menghapus semua isi linked list
    *head = NULL;        //Untuk refresh data
    return;
}

// Fungsi untuk validasi login berdasarkan username dan password
bool validasiLogin(const string& username, const string& password) {
    Akun* current = Head;
    while (current != NULL) {
        if (current->username == username && current->password == password) {
            return true;
        }
        current = current->next;
		index_user++;
    }
    return false;
}

// Fungsi untuk validasi keunikan username
bool validasiUsername(const string& username) {
    Akun* current = Head;
    while (current != NULL) {
        if (current->username == username) {
            return false;
        }
        current = current->next;
		index_user++;
    }
    return true;
}

// Fungsi untuk menyesuaikan pointer 'prev' dari setiap node pada linked list
void fixPrev(Akun **head , Akun **tail){
    if (*head == NULL){
        return;
    }
    (*head)->prev = NULL;
    Akun *cur = *head;
    while(cur->next != NULL){
     Akun *temp = cur->next;
    temp->prev = cur;
    cur = cur->next;
    }
    *tail = cur;
    (*tail)->next = NULL;
}

// Fungsi untuk menyesuaikan ID karyawan pada linked list
void fixID(Akun **head){
    Akun* current = *head;
    int newID = 1;
    while (current != NULL) {
        current->id = newID;
        newID++;
        current = current->next;
    }
}

void clear(Node** head){ //Berfungsi untk menghapus semua isi linked list
    *head = NULL;        //Untuk refresh data
    return;
}

void clear(Absen** head){ //Berfungsi untk menghapus semua isi linked list
    *head = NULL;        //Untuk refresh data
    return;
}

#endif
