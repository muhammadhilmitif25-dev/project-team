


###  Anggota Kelompok CKA 👥 

| NIM       | Nama                             | GitHub                       |
| --------- | -------------------------------- |------------------------------|
| 251511046 | Maheswara Farrel Surendra Tsaqif | farrel-de                            |
| 251511049 | Muhammad Hilmi Farahat           | @muhammadhilmitif25-dev      |

---

### Dosen Penanggung Jawab

Yudi Widhiyasana, S.Si., MT


## Setup Environment (Device)

Untuk menjalankan project ini, dibutuhkan:

* **Sistem Operasi**:

  * Windows 

* **Tools**:

## 🛠️ Setup Environment
Sebelum Project dimulai alangkah baiknya untuk mengunduh Tools tools berikut:

| Tool               | Keterangan                                         | Link Download                  |
|--------------------|----------------------------------------------------|--------------------------------|
| Git                | Digunakan untuk clone repository                   | https://git-scm.com/           |
| MSYS2 / MinGW64    | Environment dan compiler untuk menjalankan program | https://www.msys2.org/         |
| Visual Studio Code | Code editor untuk menulis dan mengedit program     | https://code.visualstudio.com/ |

## ▶️ Cek Instalasi (via CMD)

Buka Command Prompt (CMD), lalu jalankan perintah berikut:

```bash
git --version
where gcc
code --version

```

### 📥 Clone Repository 

Ikuti langkah berikut untuk mengambil project dari GitHub:

1. Buka CMD / Terminal

2. Jalankan perintah berikut:
```bash
git clone https://github.com/username/nama-repo.git
``` 
3. Masuk ke folder project:
cd nama-repo

4. Buka di Visual Studio Code: 
```code .```


## 🛠️ Langkah-Langkah Build & Run (via CMD)

Berikut adalah panduan untuk melakukan kompilasi dan menjalankan program Notepad CKA melalui Command Prompt.

### 1. Kompilasi (Menciptakan notepad_cka.exe)
Kita menggunakan **GCC** untuk menggabungkan semua modul (`.c`) menjadi satu aplikasi utuh. Pastikan kamu berada di dalam folder `consoleapk` sebelum menjalankan perintah ini:

```cmd
gcc main.c buffer.c cursor.c editor.c fileio.c searchfile.c -o notepad_cka.exe
[!IMPORTANT] Daftar File Wajib:
Karena proyek ini sudah modular, pastikan file main.c, buffer.c, cursor.c, editor.c, fileio.c, dan searchfile.c ada di folder yang sama. Jika kamu menambah file .c baru, kamu wajib menambahkannya ke dalam daftar perintah di atas.

2. Menjalankan Program
Setelah proses kompilasi berhasil (tidak ada error), jalankan aplikasi langsung dengan mengetik namanya:

DOS
notepad_cka.exe
🔄 Workflow Pengembangan
Agar setiap logika baru (seperti perbaikan backspace atau wrap kursor) bisa langsung dicoba, ikuti alur ini:

Simpan Perubahan: Tekan Ctrl + S pada VS Code untuk semua file yang diedit.

Re-Compile: Jalankan kembali perintah gcc di atas. Jika muncul pesan error, cek kembali titik koma (;) atau typo pada kode.

Running: Panggil notepad_cka.exe.



