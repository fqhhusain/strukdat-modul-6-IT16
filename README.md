# strukdat-modul-6-IT16

## Deskripsi singkat

Mengkombinasikan konsep OOP dan graf untuk membuat peta beserta list character dari sebuah video game.
Peta direpresentasikan dengan adjecency list yang menggambarkan jarak suatu kota menuju kota lain melalui jalan darat atau laut. Graf yang diterapkan berupa unweighted undireced graph. Program ini menerapkan konsep shortest path untuk mencari jarak terdekat antara dua kota menggunakan algoritma dijkstra. Selain itu, algoritma graf traversal dfs juga digunakan untuk menggambarkan proses perjalanan dari character.


## Konsep OOP 

- Class & Object

Class adalah sebuah tipe data yang terdiri dari satu atau lebih data dan satu atau lebih fungsi. Sebuah class dapat diakses ketika class tersebut dipanggil dan dibuat dalam bentuk instance dari class tersebut.
Berikut ini adalah Class yang diterapkan di dalam program:

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/c340c1ac-f457-44da-b606-418b1610b502)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/c1815ea7-5e79-4907-9677-37102fd52906)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/f642ea84-f92f-4910-94e2-2b68e5dfcb21)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/ae3ecd1b-f227-4536-85e0-cbaaeea5ddf0)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/98ffc449-3131-4bb3-a5f2-7aa0a623996f)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/310eef60-39e6-4a70-a241-098d18e26ae7)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/3e85407e-2fc7-4145-958e-32b68a33d927)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/dd41cf54-c8d6-4d4c-8370-79a6700c478e)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/01d08f49-e907-4a2a-b16c-24b224548cc6)

- Attribute, Property & Method, Behavior

Attribute/Property adalah anggota variabel data yang berada dalam sebuah class yang mewakili suatu fitur tertentu. Attribute/Property juga dapat disebut sebagai karakteristik class yang dapat diakses dari object lain atau membedakan suatu class dengan class lainnya.
Contoh penerapan attribute pada program:

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/1023d073-3baa-4963-8675-dfb381e47ce9)

Class character memiliki attribute string name, int hp, dan string city.

Method/Behavior adalah fungsi yang terdapat dalam sebuah class. Method/Behavior dapat menggunakan suatu parameter dan menerima argumen yang nantinya dapat dimanipulasi untuk menghasilkan sebuah output sesuai tujuan dibuatnya Method/Behavior tersebut.
Contoh peneraoan method pada program:

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/8d803350-9d97-4f76-a6a2-b163c3b1cabe)

- Constructor

Pada program menerapkan Parameterized Constructor.Constructor ini digunakan ketika kita ingin menginisialisasi data anggota dengan nilai tertentu pada saat pembuatan objek.

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/1999c094-a1f8-4e38-918f-7f57340c78b5)

- Setter & Getter

  Karena adjlist berada dalam protected sehingga memerlukan getter

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/71688da0-4fcd-477a-9e35-9933cfd4e6b6)


- Encapsulation

Encapsulation dalam pemrograman berorientasi objek (OOP) adalah konsep untuk mengemas data bersama dengan metode yang beroperasi pada data tersebut dalam sebuah class. Ini berarti bahwa data (variabel) bersama dengan operasi (metode atau fungsi) yang bekerja pada data itu, dikemas bersama dalam satu unit yang disebut objek.

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/5ec2920f-2718-4bb0-b911-246676ef1973)

Data Hiding

Data hiding adalah cara membatasi akses anggota data dengan menyembunyikan detail implementasi. Dalam contoh berikut menggunakan protected.

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/3441f58b-4231-4cd4-8372-c8db63173ae5)

- Inheritance

Inheritance adalah suatu fitur atau proses dimana class baru dibuat dari class yang sudah ada. Kelas baru yang dibuat disebut “derived class” atau “child class” dan class yang sudah ada disebut “base class” atau “parent class”.

Derived class diwariskan oleh base class. Artinya, derived class memperoleh properti dan karakteristik dari base class, dan bisa menambah fitur tersendiri tanpa mengubah properti dari base class.

NPC memiliki sub class Trader dan Enemy

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/efba54e7-2827-4176-8715-27d1885e0b2d)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/7c357a98-e7e5-46af-b0c6-8d1193d07e73)

BaseGraph memiliki subclass RoadGraph dan SeaRouteGraph

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/ee0086f1-88d2-410b-9d9f-be50394f7a79)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/00a4dd72-cd95-4a9e-8795-0c353acf01c6)

- Overriding

Overriding adalah sebuah method dari superclass (kelas induk) yang ditulis kembali pada subclass (kelas anak). Karena sering kali terdapat sebuah method dari superclass (kelas induk) yang aksi pada methodnya tidak sesuai jika diterapkan pada subclass (kelas anak).

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/8014bd6e-e3d5-4571-a8d4-f63761be3c3e)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/dfdddc28-1064-40f2-9e5a-07f8bda20775)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/c15901b5-5982-4c23-aedf-87be693c5f03)

Fungsi printInfo() di kelas Enemy digunakan untuk mencetak informasi tentang musuh seperti nama, kota, HP, dan serangan.

Fungsi printInfo() di kelas Trader digunakan untuk mencetak informasi tentang pedagang seperti nama, kota, dan barang-barang yang dijualnya beserta statistik masing-masing barang.

- Access Modifier, Visibility

Konsep "Access Modifier" atau "Visibility" adalah bagian penting dari pemrograman berorientasi objek karena membantu mengatur akses terhadap properti dan metode dari suatu kelas.

Public 

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/2bf1f5cf-e9fe-402f-93bc-902221ba1bd8)

Protected

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/597aaa8a-e5ca-4564-9804-923e3b516841)

- Abstraction

Data Abstraction
![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/a6ce096b-0c46-4f1e-a673-9f8dd94ea1c5)

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/13673c16-e3c3-45e6-b515-0af808d10658)


Control Abstraction

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/ac58a6db-356e-4be2-a902-6cd25afbbe3a)

- Polymorphism
  
Berupa Runtime Polymorphism. Jenis polymorphism ini dicapai dengan Penimpaan Fungsi. 

Virtual function adalah fungsi anggota yang dideklarasikan di kelas dasar menggunakan kata kunci virtual dan didefinisikan ulang (override) di kelas turunan.

![image](https://github.com/fqhhusain/strukdat-modul-6-IT16/assets/88548292/916329e3-146b-41f7-9a7c-136594f2559d)


# Konsep Graf

1. Traversal (DFS)
2. Shortest Path (Dijkstra)

