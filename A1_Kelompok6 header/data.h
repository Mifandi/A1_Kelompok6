#ifndef data_H
#define data_H

#include <iostream>
#include <string>

using namespace std;    

struct Absen {
    string nama;
    string kehadiran;
    string tanggal;
    string jam;
    Absen* next = NULL;
};

struct DataAkun {
    string nama;
    long long nik;
    string jabatan;
    string notelp;
    string alamat;
    long long gaji;      
    string kehadiran;
    string tanggal;
    string jam;
};

struct Akun {
    int id;
    string username;
    string password;
    DataAkun akun;
    Akun* next = NULL;
    Akun* prev = NULL;
};

struct Node {
    string nama;
    string alamat;    
    string SD;    
    string SMP;    
    string SMA;    
    string Kuliah;    
    string notelp;
    Node *next = NULL;
};

#endif
