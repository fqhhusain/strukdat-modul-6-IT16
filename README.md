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
- Overriding
- Access Modifier, Visibility
- Abstraction
- Polymorphism

# Konsep Graf

1. Traversal (DFS)
2. Shortest Path (Dijkstra)

