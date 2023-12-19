-- MENJALANKAN APLIKASI -- 

FE -> 

1) Kalian harus memiliki akun blynk
2) lalu buat project, ketika project sudah dibuat maka akan ada blynk auth token yang bisa digunakan untuk membantu dalam pembentukan endpointnya
3) buat .env file dengan isi didalamnya : 
	BLYNK_AUTH_TOKEN = "TOKEN_AUTH_KALIAN"

UNTUK MENJALANKAN PROGRAM FE (NEXT JS)
command : npm run dev


BE -> 
Jika temen temen ingin membuat sistem, yang sama dengan saya yaitu notifikasi email alert akan muncul jika polusinya tidak baik, maka bisa melakukan konfigurasi dibawah ini : 
1) teman teman harus memiliki akun email
2) email tersebut harus melalui 2FA verication dan allow application untuk email, nanti akan dikirimkan auth_token untuk melakukan pengiriman via email
3) buat .env file dengan isi didalamnya : 
	AUTH_EMAIL_SENDER = "EMAIL_KALIAN"
	AUTH_PASSWORD_SENDER = "AUTH_TOKEN_DARI_EMAIL_KALIAN"
	EMAIL_TOSEND = "EMAIL_YANG_MAU_DIKIRIM_ALERT"


UNTUK MENJALANKAN PROGRAM BE
command : npx nodemon index.js


