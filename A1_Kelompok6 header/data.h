#ifndef data_H
#define data_H

#include <iostream>
#include <string>

using namespace std;    

// Struktur data untuk menyimpan absensi karyawan
struct Absen {
    string nama;
    string kehadiran;
    string tanggal;
    string jam;
    Absen* next = NULL;
};

// Struktur data untuk menyimpan informasi karyawan
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

// Struktur data untuk merepresentasikan akun karyawan
struct Akun {
    int id;
    string username;
    string password;
    DataAkun akun;
    Akun* next = NULL;
    Akun* prev = NULL;
};

// Struktur data untuk menyimpan informasi personal
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
