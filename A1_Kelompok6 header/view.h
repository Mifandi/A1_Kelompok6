#ifndef view_H
#define view_H

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
#include "CRUD.h"

void readAbsen(Absen** head);

// Variabel global yang digunakan untuk menyimpan alamat dari linked list Absen dan jumlah karyawan yang sudah melakukan absensi
extern Absen *Kepala;
extern int jumlahHadir;

// Fungsi untuk menampilkan data karyawan dan memberikan opsi pengelolaannya
void viewKaryawan(Akun *head){
    system("cls");
    int counter = 1;
    int corY = 3;
    int corX = 5;
    int tampil = 10;
    int code = 0;
    string search;
    Akun *current = head;
    for(;;){
        if (code == 1){
            corY = 3;
            color(7);corY = BoyerMoore(Head, search, 0, corY);
        }
        else{
            color(7);
            while (current != NULL && tampil > 0){
                if (current->next == NULL){
                    tampil = 1;
                }
                gotoxy(0, corY);cout<<"|"<<current->id<<".|"<< current->akun.nama<<endl;
                corY++;
                tampil --;
                current = current->next;
            }
        }
        color(1);gotoxy(0,0);cout << "==================================================\n";
        gotoxy(0,1);color(1);cout << "|";color(7);cout<<"                   Data Karyawan                ";color(1);cout<<"|\n";
        color(1);gotoxy(0,2);cout << "==================================================\n";
        color(7);gotoxy(0,corY);cout << "__________________________________________________\n";
        display(corX + 2, corY + 1,"  >","|  Awal  |", counter == 1);
        display(corX + 23, corY + 1,"  >","| Berikutnya |", counter == 2);
        display(corX + 2 ,corY + 2,"  >","| Tambah |", counter == 3);
        display(corX + 23, corY + 2,"  >","|    Hapus   |", counter == 4);
        display(corX + 14 , corY + 3,"  >","Kembali", counter == 5);
        color(6);gotoxy(0,corY + 4);cout << "==================================================\n";
        display(0, corY + 5," >","Cari     :", counter == 6);
        display(0, corY + 6," >","Pilih  ID:", counter == 7);
        pilih = _getch();
        if (pilih == 72 && (counter <= 7)) {
            counter--;
            if (counter < 1) {
                counter = 7;
            }
        }
        if (pilih == 80 && (counter >= 1)) {
            counter++;
            if (counter > 7) {
                counter = 1;
            }
        }
        if (pilih == '\r') {
            if (counter == 1){
                system("cls");
                code = 0;
                corY = 3;
                tampil = 10;
                current = head;
            }
            if (counter == 2){
                if (code == 2){
                    code = 0;
                    system("cls");
                }else{
                    if (current != NULL){
                        system("cls");
                        tampil = 10;
                        corY = 3;
                    }
                }
            }
            if (counter == 3){
                tambah();
            }
            if (counter == 4){
                string posisi;
                bool ulang = false;
                while (!ulang) {
                    try {
                        color(7);gotoxy(0, corY + 6);cout << "Masukkan ID yang ingin dihapus:";
                        getline(cin, posisi);
                        stoi(posisi);
                        ulang = true;
                    } catch (invalid_argument& e) {
                        color(4);gotoxy(0, corY + 7);cout << "Harus Angka" << endl;
                        Sleep(1000);
                    }
                }
                hapus(&Head, posisi);
                viewKaryawan(Head);
            }
            if (counter == 5){
                menuAdmin();
            }
            if (counter == 6){
                gotoxy(13,corY + 5);getline(cin, search);
                code = 1;
                system("cls");
            }
            if (counter == 7){
                string inputS;
                int input;
                try
                {
                    fflush(stdin);
                    gotoxy(13,corY + 6);getline(cin, inputS);
                    input = stoi(inputS);
                }
                catch (invalid_argument &e)
                {
                    gotoxy(0, 15);color(4);cout << "Input Invalid";
                    Sleep(1000);
                    viewKaryawan(Head);
                }
                if (input > 0 || input < jumlahKaryawan){
                    update(&Head, input, "admin3");
                }
            }
        }
        cleaner(5, 40, corX, corY + 1);
    }
}

// Fungsi untuk menampilkan data absensi karyawan dan memberikan opsi pengelolaannya
void viewAbsen(Absen *head){
    system("cls");
    int counter = 1;
    int corY = 3;
    int corX = 15;
    int tampil = 10;
    int jumlah = 0;
    int code = 0;
    int LimitBawah = 4;
    int Hidden1;
    int Hidden2;
    int Hidden3;
    int Hidden4;
    int Hidden5;
    int Hidden6;
    Absen *current = head;
    for(;;){
        color(1);gotoxy(0,0);cout << "==================================================\n";
        gotoxy(0,1);color(1);cout << "|";color(7);cout<<"                     Absensi                    ";color(1);cout<<"|\n";
        color(1);gotoxy(0,2);cout << "==================================================\n";
        while (current != NULL && tampil > 0){
                if (current->next == NULL){
                    tampil = 1;
                }
                jumlah++;
                color(7);gotoxy(0, corY);cout<<"|"<<jumlah<<".|"<< current->nama<<" "<< current->kehadiran<<" "<<current->jam<<" "<<current->tanggal<<endl;
                corY++;
                tampil --;
            current = current->next;
        }
        color(7);gotoxy(0,corY);cout << "__________________________________________________\n";
        display(corX + 3, corY + 1,"  >","Berikutnya", counter == 1);
        display(corX + 5, corY + 2,"  >","Awal", counter == 2);
        display(corX + 4, corY + 3,"  >","Sorting", counter == 3);
        if (code == 1) {
            Hidden1 = 4;
            Hidden2 = 5;
            Hidden3 = 6;
            Hidden4 = 7;
            Hidden5 = 8;
            Hidden6 = 9;
            gotoxy(corX + 4, corY + 4);color(7);cout<<"Nama :";
            display(corX + 6, corY + 5,"  >","Ascending", counter == 4);
            display(corX + 6, corY + 6,"  >","Descending", counter == 5);
            gotoxy(corX + 4, corY + 7);color(7);cout<<"Waktu :";
            display(corX + 6, corY + 8,"  >","Ascending", counter == 6);
            display(corX + 6, corY + 9,"  >","Descending", counter == 7);
            display(corX + 5, corY + 10,"  >","Default", counter == 8);
            display(corX + 4, corY + 11,"  >","Kembali", counter == 9);
            color(6);gotoxy(0,corY + 12);cout << "==================================================\n";
        }else {
            Hidden1 = 0;
            Hidden2 = 0;
            Hidden3 = 0;
            Hidden4 = 0;
            Hidden5 = 0;
            Hidden6 = 4;
            display(corX + 4, corY + 4,"  >","Kembali", counter == 4);
            color(6);gotoxy(0,corY + 5);cout << "==================================================\n";
        }
        pilih = _getch();
        if (pilih == 72 && (counter <= LimitBawah)) {
            counter--;
            if (counter < 1) {
                counter = LimitBawah;
            }
        }
        if (pilih == 80 && (counter >= 1)) {
            counter++;
            if (counter > LimitBawah) {
                counter = 1;
            }
        }
        if (pilih == '\r') {
            if (counter == 1){
                if (current != NULL){
                    system("cls");
                    tampil = 10;
                    corY = 3;
                }
            }
            if (counter == 2){
                system("cls");
                corY = 3;
                tampil = 10;
                current = head;
                jumlah = 0;
            }
            if (counter == 3){
                code = 1;
                LimitBawah = 9;
            }
            if (counter == Hidden1){
                system("cls");
                shellSort(Kepala, 1);
                corY = 3;
                jumlah = 0;
                tampil = 10;
                current = head;
            }
            if (counter == Hidden2){
                system("cls");
                shellSort(Kepala, 2);
                corY = 3;
                jumlah = 0;
                tampil = 10;
                current = head;
            }
            if (counter == Hidden3){
                system("cls");
                shellSort2(Kepala, 1);
                corY = 3;
                jumlah = 0;
                tampil = 10;
                current = head;
            }
            if (counter == Hidden4){
                system("cls");
                shellSort2(Kepala, 2);
                corY = 3;
                jumlah = 0;
                tampil = 10;
                current = head;
            }
            if (counter == Hidden5){
                readAbsen(&Kepala);
                viewAbsen(Kepala);
            }
            if (counter == Hidden6){
                menuAdmin();
            }
        }
        cleaner(10, 60, 0, corY + 1);
    }
}

#endif
