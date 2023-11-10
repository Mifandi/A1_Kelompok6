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

void color(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void gotoxy(int x, int y){
    COORD c;
    c.X=x + 30;
    c.Y=y + 5;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

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

void cleaner (int max,int n, int horz, int vert) {
    for (int i = 0; i <= max;i++){
        gotoxy(horz, vert + i);cout<<string(n + 1, ' ');
    }
}

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

void clear(Akun** head){ 
    *head = NULL;        
    return;
}

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

void fixID(Akun **head){
    Akun* current = *head;
    int newID = 1;
    while (current != NULL) {
        current->id = newID;
        newID++;
        current = current->next;
    }
}

void clear(Node** head){ 
    *head = NULL;        
    return;
}

void clear(Absen** head){ 
    *head = NULL;        
    return;
}

#endif
