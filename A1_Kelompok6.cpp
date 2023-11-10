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

#include "A1_Kelompok6 header/data.h"
#include "A1_Kelompok6 header/MenuFunction.h"
#include "A1_Kelompok6 header/CRUD.h"
#include "A1_Kelompok6 header/lamaran.h"
#include "A1_Kelompok6 header/absensi.h"
#include "A1_Kelompok6 header/view.h"

using namespace std;

void menuAwal();
void menuUser(int akun);
void menuAdmin();
void Simpan(Akun *simpan);

// Pointer ke awal linked list data karyawan
Akun *Head = NULL;
// Pointer ke akhir linked list data karyawan    
Akun *Tail = NULL;

// Pointer ke awal linked list data lamaran pekerjaan
Node* Front = NULL;
// Pointer ke akhir linked list data lamaran pekerjaan 
Node* Rear = NULL;

// Pointer ke awal linked list data absensi karyawan
Absen* Kepala = NULL;

int jumlahKaryawan;   
int jumlahHadir; 

// Fungsi untuk menyimpan data karyawan ke dalam file CSV
void Simpan(Akun* simpan) {
    fstream file;
    file.open("A1_Kelompok6 datafolder/Database.csv", ios::out | ios::trunc);
    
    while (simpan != NULL) {
        file << simpan->id << ",";
        file << simpan->username << ",";
        file << simpan->password << ",";
        file << simpan->akun.nama << ",";
        file << simpan->akun.nik << ",";
        file << simpan->akun.jabatan << ",";
        file << simpan->akun.notelp << ",";
        file << simpan->akun.alamat << ",";
        file << simpan->akun.gaji << ",";
        file << simpan->akun.kehadiran << ",";
        file << simpan->akun.tanggal << ",";
        file << simpan->akun.jam << "\n"; 
        simpan = simpan->next;
    }
    file.close();
}

// Fungsi untuk membaca data karyawan dari file CSV dan membangun linked list
void BacaFile(Akun** head, Akun** tail){
	jumlahKaryawan = 0;
    clear(head);
	string data,id, username, password, nama , nik, jabatan, notelp, alamat, gaji, kehadiran, tanggal, jam;
	int id_int,nik_int, gaji_int;
    ifstream file;
	file.open("A1_Kelompok6 datafolder/Database.csv");
	if(file.is_open()) {
        while (getline(file,data)){
			stringstream ss(data);
			getline(ss,id,',');
			getline(ss,username,',');
			getline(ss,password,',');
			getline(ss,nama,',');
			getline(ss,nik,',');
			getline(ss,jabatan,',');
			getline(ss,notelp,',');
			getline(ss,alamat,',');
			getline(ss,gaji,',');
			getline(ss,kehadiran,',');
			getline(ss,tanggal,',');
			getline(ss,jam,',');
			stringstream id_string(id);
			stringstream nik_string(nik);
			stringstream gaji_string(gaji);
			id_string >> id_int;
			nik_string >> nik_int;
			gaji_string >> gaji_int;
            Akun* newKaryawan = new Akun;
			newKaryawan->id = id_int;
			newKaryawan->username = username;
			newKaryawan->password = password;
			newKaryawan->akun.nama = nama;
			newKaryawan->akun.nik = nik_int;
			newKaryawan->akun.jabatan = jabatan;
			newKaryawan->akun.notelp = notelp;
			newKaryawan->akun.alamat = alamat;
			newKaryawan->akun.gaji = gaji_int;
			newKaryawan->akun.kehadiran = kehadiran;
			newKaryawan->akun.tanggal = tanggal;
			newKaryawan->akun.jam = jam;
            newKaryawan->next = *head;
			newKaryawan->prev = *tail;
            if (*head == NULL) {
                *head = newKaryawan;
                *tail = newKaryawan;
            } else {
                (*tail)->next = newKaryawan;
                *tail = newKaryawan;
            }
            newKaryawan->next = NULL;
			jumlahKaryawan++;
		}
        file.close();
	} 
	else {
        cout << "File tidak ditemukan" << endl;
	}
}

// Fungsi untuk membaca data kehadiran karyawan dari file CSV dan membangun linked list
void readAbsen(Absen** head){
    clear(head);
	jumlahHadir = 0;
	string data,id, username, password, nama , nik, jabatan, notelp, alamat, gaji, kehadiran, tanggal, jam;
    ifstream file;
	file.open("A1_Kelompok6 datafolder/Database.csv");
	if(file.is_open()) {
        while (getline(file,data)){
			stringstream ss(data);
			getline(ss,id,',');
			getline(ss,username,',');
			getline(ss,password,',');
			getline(ss,nama,',');
			getline(ss,nik,',');
			getline(ss,jabatan,',');
			getline(ss,notelp,',');
			getline(ss,alamat,',');
			getline(ss,gaji,',');
			getline(ss,kehadiran,',');
			getline(ss,tanggal,',');
			getline(ss,jam,',');
            Absen* newAbsen = new Absen;
			if (kehadiran != "Belum Absen"){
				newAbsen->nama = nama;
				newAbsen->kehadiran = kehadiran;
				newAbsen->tanggal = tanggal;
				newAbsen->jam = jam;
				newAbsen->next = *head;
				*head = newAbsen;
				jumlahHadir++;
			}
		}
        file.close();
	} 
	else {
        cout << "File tidak ditemukan" << endl;
	}
}

// Fungsi untuk login admin
void loginAdmin() {
	system("cls");
	int counter = 1;
	inputnama = "";
	inputpassword = "";
	for(;;){
		system("cls");
		color(7);
		color(1);gotoxy(0,0);cout << "==========================================\n";    
		color(7);gotoxy(0,1);cout << "               Menu Login Admin           \n";    
		color(1);gotoxy(0,2);cout << "==========================================\n"; 
		displayEdit(5,3," >", "Username :",inputnama,counter == 1);
		displayEdit(5,4," >", "Password :",inputpassword,counter == 2);
		display(16,6,"  >", "Login",counter == 3);
		display(15,7,"  >", "Kembali",counter == 4);
		gotoxy(0,8);color(6);cout << "==========================================\n";
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
		}if (pilih == '\r'){
			if (counter == 1){
				gotoxy(17,3);fflush(stdin);getline(cin,inputnama);
			}
			if (counter == 2){
				gotoxy(17,4);fflush(stdin);getline(cin,inputpassword);
			}
			if (counter == 3){
				if(inputnama == "" || inputpassword ==""){
					color(4);gotoxy(0,9);cout << "Inputan tidak boleh kosong";
					Sleep(1000);
					loginAdmin();
				}else{
					if(inputnama == "admin"&&inputpassword == "admin"){
						system ("cls");
						gotoxy(5,0);color(7);cout << "=======================================\n";
						gotoxy(5,1);color(2);cout << "|         ANDA BERHASIL MASUK         |\n";
						gotoxy(5,2);color(7);cout << "=======================================\n";
						Sleep(1000);
						menuAdmin();
					}else {
						system("cls");
                        gotoxy(0,0);color(7);cout << "=====================================================\n";
                        gotoxy(0,1);color(4);cout << "|  USERNAME ATAU PASSWORD YANG ANDA MASUKKAN SALAH  |\n";
                        gotoxy(0,2);color(7);cout << "=====================================================\n";
						gotoxy(0,3);system("pause");
						loginAdmin();
					}
				}
			}
			if (counter == 4){
				menuAwal();
			}
		}
		cleaner(4, 25, 0, 3);
	}
}

// Fungsi untuk login user
void loginUser(Akun *head) {
	system("cls");
	int counter = 1;
	inputnama = "";
	inputpassword = "";
	Akun *user = NULL;
	for(;;){
		system("cls");
		color(1);gotoxy(0,0);cout << "==========================================\n";    
		color(7);gotoxy(0,1);cout << "               Menu Login User              \n";    
		color(1);gotoxy(0,2);cout << "==========================================\n"; 
		displayEdit(5,3," >", "Username :",inputnama,counter == 1);
		displayEdit(5,4," >", "Password :",inputpassword,counter == 2);
		display(16,6,"  >", "Login",counter == 3);
		display(15,7,"  >", "Kembali",counter == 4);
		gotoxy(0,8);color(6);cout << "==========================================\n";
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
		}if (pilih == '\r'){
			if (counter == 1){
				gotoxy(17,3);fflush(stdin);getline(cin,inputnama);
			}
			if (counter == 2){
				gotoxy(17,4);fflush(stdin);getline(cin,inputpassword);
			}
			if (counter == 3){
				if(inputnama == "" || inputpassword ==""){
					color(4);gotoxy(0,9);cout << "Inputan tidak boleh kosong";
					Sleep(1000);
					loginAdmin();
				}else{
					Akun *temp = head;
                    while (temp != NULL) {
                        if (temp->username == inputnama && temp->password == inputpassword) {
                            user = temp;
                            break;
                        }
                        temp = temp->next;
                    }
					if (user != NULL) {
                        system("cls");
						gotoxy(5,0);color(7);cout << "=======================================\n";
						gotoxy(5,1);color(2);cout << "|         ANDA BERHASIL MASUK         |\n";
						gotoxy(5,2);color(7);cout << "=======================================\n";
                        Sleep(1000);
						menuUser(user->id);
                    } else {
                        system("cls");
                        gotoxy(0,0);color(7);cout << "=====================================================\n";
                        gotoxy(0,1);color(4);cout << "|  USERNAME ATAU PASSWORD YANG ANDA MASUKKAN SALAH  |\n";
                        gotoxy(0,2);color(7);cout << "=====================================================\n";
						gotoxy(0,3);system("pause");
                        loginUser(head);
                    }
				}
			}
			if (counter == 4){
				menuAwal();
			}
		}
		cleaner(4, 25, 0, 3);
	}
}

// Fungsi untuk menu admin
void menuAdmin (){
	int counter = 1;
	system("cls");
	gotoxy(0,0);color(1);cout << "================================================================\n";
	gotoxy(0,1);color(1);cout <<"|";color(7);cout<<"          Program Pendataan Karyawan PT. Maju Mundur          ";color(1);cout<<"|\n";
	gotoxy(0,2);color(1);cout << "================================================================\n";
	for (int j = 3; j <=8 ; j++){
		for(int a = 0; a <= 63; a++){
			gotoxy(0,j);color(7);cout << "|";
			gotoxy(63,j);color(7);cout << "|";
			gotoxy(a,9);color(6);cout << "=";
		}
	}
    for (;;){
        display(18,4,"  >","1. Data Manager", counter == 1);
        display(18,5,"  >","2. Lihat Absensi Karyawan", counter == 2);
        display(18,6,"  >","3. Lihat Pelamar Pekerjaan", counter == 3);
        display(18,7,"  >","4. Kembali", counter == 4);
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
				viewKaryawan(Head);
			}
			if(counter == 2){
				readAbsen(&Kepala);
				viewAbsen(Kepala);
				cout << "\n\n";
				system("pause"); system("cls"); 
				menuAdmin();
			}
			if(counter == 3){
				cekPelamar(Front);
			}
			if(counter == 4){
				menuAwal();
			}
		}
		cleaner(4, 34, 18, 4);
    }
}

// Fungsi untuk menu user
void menuUser(int akun) {
	system("cls");
	int counter = 1;
	gotoxy(0,0);color(1);cout << "================================================================\n";
	gotoxy(0,1);color(1);cout <<"|";color(7);cout<<"          Program Pendataan Karyawan PT. Maju Mundur          ";color(1);cout<<"|\n";
	gotoxy(0,2);color(1);cout << "================================================================\n";
	for (int j = 3; j <=7 ; j++){
		for(int a = 0; a <= 63; a++){
			gotoxy(0,j);color(7);cout << "|";
			gotoxy(63,j);color(7);cout << "|";
			gotoxy(a,8);color(6);cout << "=";
		}
	}
	for (;;){
		display (22,4,"  >", "1. Profil",counter == 1);
		display (22,5,"  >", "2. Absen",counter == 2);
		display (22,6,"  >", "3. Kembali",counter == 3);
		pilih = _getch();
		if(pilih == 72 && (counter <=3)){
			counter --;
			if (counter < 1){
				counter = 3;
			}
		}
		if(pilih == 80 && (counter >=1)){
			counter ++;
			if (counter > 3){
				counter = 1;
			}
		}
		if(pilih == '\r'){
			if(counter == 1){
				system("cls");
				update(&Head,akun,"user");
			}
			if(counter == 2){
				menuAbsen(&Head, akun);
			}
			if(counter == 3){
				menuAwal();
			}
		}
		cleaner(3, 13, 22,4);
	}
}

// Fungsi untuk menu awal ketika program di jalankan pertama kali
void menuAwal() {
    system("cls");
    int counter = 1;
	gotoxy(0,0);color(1);cout << "================================================================\n";
	gotoxy(0,1);color(1);cout <<"|";color(7);cout<<"          Program Pendataan Karyawan PT. Maju Mundur          ";color(1);cout<<"|\n";
	gotoxy(0,2);color(1);cout << "================================================================\n";
    for (int j = 3; j <=8 ; j++){
		for(int a = 0; a <= 63; a++){
			gotoxy(0,j);color(7);cout << "|";
			gotoxy(63,j);color(7);cout << "|";
			gotoxy(a,9);color(6);cout << "=";
		}
	}
    for (;;){
        display(21,4,"  >","1. Login Admin", counter == 1);
        display(21,5,"  >","2. Login Karyawan", counter == 2);
        display(21,6,"  >","3. Lamar Pekerjaan", counter == 3);
        display(21,7,"  >","4. Keluar", counter == 4);
		pilih = _getch();
        if (pilih == 72 && (counter <=4) ){
        counter --;
            if (counter < 1){
                counter = 4;
            }
		}
		if (pilih == 80 && (counter >=1)){
			counter ++;
			if (counter > 4){
				counter = 1;
			}
		}
        if (pilih == '\r'){
            if (counter == 1){
				loginAdmin();
			}
			if (counter == 2){
				loginUser(Head);
			}
			if (counter == 3){
				lamar(&Front, &Rear);
			}
			if (counter == 4){
				color(16);
				system("cls");
				exit(0);
			}
        }
		cleaner(4, 22, 21, 4);
    }
}

int main (){
    BacaFile(&Head, &Tail);
	readAbsen(&Kepala);
	readLamar(&Front, &Rear);
	tanggal(&Head);
	menuAwal();
}
