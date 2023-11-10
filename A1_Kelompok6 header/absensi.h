#ifndef absensi_H
#define absensi_H

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
#include "CRUD.h"
#include "lamaran.h"

// Eksternal variable untuk menyimpan jumlah kehadiran
extern int jumlahHadir;

// Fungsi menuAbsen untuk melakukan proses absensi karyawan
void menuAbsen (Akun **head, int akun) {
    system("cls");
    int counter = 1;
    Akun *temp = (*head);
    while (temp != NULL){
        if (temp->id == akun){
            if (temp->akun.kehadiran == "Belum Absen"){
                color(1);gotoxy(0,0);cout << "================================================================\n";
                gotoxy(0,1);color(1);cout << "|";color(7);cout<<"               Absensi Karyawan PT. Maju Mundur               ";color(1);cout<<"|\n";
                color(1);gotoxy(0,2);cout << "================================================================\n";
                for (int j = 3; j <=8 ; j++){
                    for(int a = 0; a <= 63; a++){
                        gotoxy(0,j);color(7);cout << "|";
                        gotoxy(63,j);color(7);cout << "|";
                        gotoxy(a,9);color(6);cout << "=";
                    }
                }
                for(;;) {
                    display(21,4,"  >", "1. Hadir", counter == 1);
                    display(21,5,"  >", "2. Izin", counter == 2);
                    display(21,6,"  >", "3. Sakit", counter == 3);
                    display(21,7,"  >", "4. Kembali", counter == 4);
                    pilih = _getch();
                    if(pilih == 72 && (counter <=4)){
                        counter --;
                        if (counter < 1){
                            counter = 4;
                        }
                    }
                    if(pilih == 80 && (counter >=1)){
                        counter ++;
                        if (counter > 4){
                            counter = 1;
                        }
                    }
                    if(pilih == '\r'){
                        if(counter == 1){
                            temp->akun.kehadiran="Hadir";
                            jumlahHadir++;
                        }
                        if(counter == 2){
                            temp->akun.kehadiran="Izin";
                            jumlahHadir++;
                        }
                        if(counter == 3){
                            temp->akun.kehadiran="Sakit";
                            jumlahHadir++;
                        }
                        if(counter == 4){
                            color(7);
                            menuUser(akun);
                        }
                        time_t sekarang = time(0);
                        tm *waktu = localtime(&sekarang);

                        int Jam = waktu->tm_hour;
                        int Menit = waktu->tm_min;

                        char jamAbsen[6];
                        sprintf(jamAbsen, "%02d:%02d", Jam, Menit);
                        temp->akun.jam = jamAbsen;
                        system("cls");
						gotoxy(0,1);color(7);cout << "===================================================\n";
						gotoxy(0,2);color(2);cout << "|         TERIMAKASIH TELAH MENGISI ABSEN         |\n";
						gotoxy(0,3);color(7);cout << "===================================================\n";
                        Sleep(1000);
                        Simpan(Head);
                        color(7);
                        menuUser(akun);
                    }
                    cleaner(4, 10, 21, 4);
                }
            }else {
                system("cls");
                gotoxy(5,1);color(7);cout << "====================================\n";
                gotoxy(5,2);color(2);cout << "|         ANDA SUDAH ABSEN         |\n";
                gotoxy(5,3);color(7);cout << "====================================\n";
                Sleep(1000);
                menuUser(akun);
            }
        }
        temp = temp->next;
    }
}

#endif
