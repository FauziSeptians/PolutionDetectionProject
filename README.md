PROJECT DETEKSI POLUSI DENGAN MENGGUNAKAN IOT SENSOR DAN DIINTEGRASIKAN DENGAN MENGGUNAKAN WEBSITE

KONSEP YANG DIPAKAI ADALAH IOT DAN PEMBUATAN APLIKASI
- IOT
untuk flow pengerjaan projectnya dalam scope IOT :
1) data diterima dari sensor, yang sudah terpasang di board arduino
2) data yang sudah diterima oleh board, di passing ke board nodemcu (sebagai module wifi), menggunakan digital pin untuk transfer datanya
3) kami passing data yang sudah diterima di Nodemcu ke dalam blynk (website penyimpanan data secara cloud)

- PEMBUATAN APLIKASI
flownya :
1) data yang sudah tersimpan di blynk, lalu kita hit apinya
2) data yang sudah diterima dari apinya, disimpan di client side
3) data yang tersimpan di client side tersebut langsung di consume dan diolah untuk ditampilkan di menu / tampilan website kami.
