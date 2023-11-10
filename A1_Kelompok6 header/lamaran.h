#ifndef lamaran_H
#define lamaran_H

#include "MenuFunction.h"
#include "CRUD.h"
#include "data.h"

Node* save = NULL;  

extern Node* Front;
extern Node* Rear;

extern int jumlahKaryawan;

void clear(Node** head);
void cleaner (int max,int n, int horz, int vert);

void SimpanLamar(Node *simpan){
    fstream file;
    file.open("A1_Kelompok6 datafolder/Pelamar.csv",ios::out | ios::trunc);
    while(simpan != NULL){
        file << simpan->nama << ",";
        file << simpan->alamat << ",";
        file << simpan->SD << ",";
        file << simpan->SMP << ",";
        file << simpan->SMA << ",";
        file << simpan->Kuliah << ",";
        file << simpan->notelp << ",";
        simpan = simpan->next;
        file <<"\n";
    }
    file.close();
}

void readLamar(Node **front, Node **rear){
    string data;
    string namas;
    string alamats;
    string SDs;
    string SMPs;
    string SMAs;
    string Kuliahs;
    string no_telp;
    fstream file;
    file.open("A1_Kelompok6 datafolder/Pelamar.csv");
    if (file.is_open())
    {
        while (getline(file, data))
        {
            stringstream ss(data);
            getline(ss, namas, ',');
            getline(ss, alamats, ',');
            getline(ss, SDs, ',');
            getline(ss, SMPs, ',');
            getline(ss, SMAs, ',');
            getline(ss, Kuliahs, ',');
            getline(ss, no_telp, ',');
            Node *newNode = new Node;
            newNode->nama = namas;
            newNode->alamat = alamats;
            newNode->SD = SDs;
            newNode->SMP = SMPs;
            newNode->SMA = SMAs;
            newNode->notelp = no_telp;
            newNode->Kuliah = Kuliahs;
            if (*front == NULL) {
                *front = newNode;
                *rear = newNode;
            } else {
                (*rear)->next = newNode;
            }
            *rear = newNode;
        }
        file.close();
    }
}

void lamar(Node **front, Node **rear){
    system("cls");
    int counter = 1;
	string NOTELP,NAMA,ALAMAT,iSD,iSMP,iSMA,KULIAH = "";
    int hidden1 = 0;
    int hidden2 = 8;
    int limitBawah = 8; 
    for (;;)
    {
        color(1);gotoxy(0, 0);cout << "=========================================================\n";
        gotoxy(0, 1);color(1);cout << "|";color(7);cout<<"                         LAMAR PEKERJAAN               ";color(1);cout<<"|\n";
        color(1);gotoxy(0, 2);cout << "=========================================================\n";
        displayEdit(0, 3, " >", "Nama         :", NAMA, counter == 1);
        displayEdit(0, 4, " >", "Alamat       :", ALAMAT, counter == 2);
        displayEdit(0, 5, " >", "Telepon      :", NOTELP, counter == 3);
        display(0, 6, " >", "Pendidikan :", counter == 0);
        displayEdit(0, 7, " >", " SD          :", iSD, counter == 4);
        displayEdit(0, 8, " >", " SMP/MTs     :", iSMP, counter == 5);
        displayEdit(0, 9, " >", " SMA/MAN/SMK :", iSMA, counter == 6);
        displayEdit(0, 10, " >", " Perguruan Tinggi :", KULIAH, counter == 7);
        if (NAMA == "" || ALAMAT == "" || NOTELP == "" || iSD == "") {
            limitBawah = 8; 
            hidden1 = 0;
            hidden2 = 8;
            display(18, 12, " >", "Kembali", counter == 8); 
            color(6);gotoxy(0, 13);cout << "=========================================================\n";
        }else{
            limitBawah = 9; 
            hidden1 = 8;
            hidden2 = 9;
            display(18, 12, " >", "Submit", counter == 8, 2); 
            display(18, 13, " >", "Kembali", counter == 9); 
            color(6);gotoxy(0, 14);cout << "=========================================================\n";
        }
        pilih = _getch();
        if (pilih == 72 && (counter <= limitBawah))
        {
            counter--;
            if (counter < 1)
            {
                counter = limitBawah;
            }
        }
        if (pilih == 80 && (counter >= 1))
        {
            counter++;
            if (counter > limitBawah)
            {
                counter = 1;
            }
        }
        if (pilih == '\r')
        {
            if (counter == 1)
            {
                fflush(stdin);
                gotoxy(16,3);getline(cin, NAMA);
            }
            if (counter == 2)
            {
                fflush(stdin);
                gotoxy(16,4);getline(cin, ALAMAT);
            }
            if (counter == 3)
            {
                try
                {
                    fflush(stdin);
                    gotoxy(16,5);getline(cin, NOTELP);
                    stoll(NOTELP);
                }
                catch (invalid_argument &e)
                {
                    NOTELP = "";
                    gotoxy(0, hidden2 + 6);color(4);cout << "Harus Angka";
                    Sleep(1000);
                }
            }
            if (counter == 4)
            {
                fflush(stdin);
                gotoxy(16,7);getline(cin, iSD);
            }
            if (counter == 5)
            {
                fflush(stdin);
                gotoxy(16,8);getline(cin, iSMP);
            }
            if (counter == 6)
            {
                fflush(stdin);
                gotoxy(16,9);getline(cin, iSMA);
            }
            if (counter == 7)
            {
                fflush(stdin);
                gotoxy(21,10);getline(cin, KULIAH);
            }
            if (counter == hidden1){
                system("cls");
                Node *newPelamar = new Node();
                newPelamar->nama = NAMA;
                newPelamar->alamat = ALAMAT;
                newPelamar->notelp = NOTELP;
                newPelamar->SD = iSD;
                newPelamar->SMP =iSMP;
                newPelamar->SMA = iSMA;
                newPelamar->Kuliah= KULIAH;
                if (*front == NULL) {
                    *front = newPelamar;
                    *rear = newPelamar;
                    SimpanLamar(Front);
                    menuAwal();
                } else {
                    (*rear)->next = newPelamar;
                }
                *rear = newPelamar;
                SimpanLamar(Front);
                gotoxy(5,0);color(7);cout << "============================================\n";
                gotoxy(5,1);color(3);cout << "|          TERIMAKASIH SUDAH MELAMAR       |\n";
                gotoxy(5,2);color(7);cout << "============================================\n";
                Sleep(1000);
                menuAwal();
            }
            if (counter == hidden2){
                menuAwal();
            }
        }
        cleaner(15, 60, 0, 3);
    }
}

void dequeue(Node** front, Node** rear){
	if (*front == NULL) {
		return;
	}
	Node *temp = *front;
	if((*front)->next != NULL){
		*front = (*front)->next;
        delete temp;
	} else {
		*front = NULL;
		*rear = NULL;
	}
}

void cekPelamar(Node *front) {
    system("cls");
	if (front == NULL) {
        gotoxy(0,0);color(7);cout << "=====================================================\n";
        gotoxy(0,1);color(4);cout << "|                 TIDAK ADA PELAMAR                 |\n";
        gotoxy(0,2);color(7);cout << "=====================================================\n";
        Sleep(1000);
		menuAdmin();
	}
	string NIK,NOTELP,GAJI,USERNAME,PASSWORD,JABATAN = "";
    int ID;
    int counter = 1;
    for (;;) {
        color(1);gotoxy(0,0);cout << "=========================================================\n";
        gotoxy(0,1);color(1);cout << "|";color(7);cout<<"                    PELAMAR PEKERJAAN                  ";color(1);cout<<"|\n";
        color(1);gotoxy(0,2);cout << "=========================================================\n";
        color(7);
        gotoxy(0,3);cout <<"Nama                : "<<front->nama;
        gotoxy(0,4);cout <<"Alamat              : "<<front->alamat;
        gotoxy(0,5);cout <<"Pendidikan          : ";
        gotoxy(0,6);cout <<"Sekolah Dasar       : "<<front->SD;
        gotoxy(0,7);cout <<"SMP/MTs             : "<<front->SMP;
        gotoxy(0,8);cout <<"SMA/MAN/SMK         : "<<front->SMA;
        gotoxy(0,9);cout <<"Perguruan Tinggi    : "<<front->Kuliah;
        gotoxy(0,10);cout <<"Telepon             : "<<front->notelp;
        display(10,12,"  >", "| Terima |", counter == 1,2);
        display(30,12,"  >", "| Tolak  |", counter == 2,4);
        display(22,13,"  >", "Kembali", counter == 3);
        color(6);gotoxy(0,14);cout << "=========================================================\n";
        pilih = _getch();
        if(pilih == 75 && (counter <=2)){
            counter --;
            if (counter < 1){
                counter = 2;
            }
        }
        if(pilih == 77 && (counter >=1)){
            counter ++;
            if (counter > 2){
                counter = 1;
            }
        }
        if(pilih == 72){
            counter = 1;
        }
        if(pilih == 80){
            counter = 3;
        }
        if (pilih == '\r'){
            if (counter == 1) {
                jumlahKaryawan++;
                ID = jumlahKaryawan;
                tambahPertama(&Head,ID,USERNAME, PASSWORD, front->nama, JABATAN, front->alamat, 0, front->notelp, 0);
                dequeue(&Front, &Rear);
                SimpanLamar(Front);
                update(&Head, ID, "admin2");
            }
            if (counter == 2) {
                dequeue(&Front, &Rear);
                SimpanLamar(Front);
                cekPelamar(Front);
            }
            if (counter == 3) {
                menuAdmin();
            }
        }
        cleaner(3, 40, 5, 12);
    }
}

#endif
