const express = require("express");
const bodyParser = require('body-parser');
const app = express();
app.use(bodyParser.urlencoded({ extended: true }));
require('dotenv').config()


const port = 5000;
var nodemailer = require("nodemailer");

app.listen(port, function (req, res) {
    console.log("listening on port" + port);
});

app.post("/sendMail", function (req, res) {
    console.log(req.body);
    const value = req.body;
    console.log(value)
    var transporter = nodemailer.createTransport({
        service: "gmail",
        auth: {
            user: process.env.AUTH_EMAIL_SENDER,
            pass: process.env.AUTH_PASSWORD_SENDER,
        },
    });

    var mailOptions = {
        from: process.env.AUTH_EMAIL_SENDER,
        to: process.env.EMAIL_TOSEND,
        subject: "!!!!HIMBAUAN JANGAN LUPA DIBACA!!!!",
        html: `<div><img src="https://i.pinimg.com/originals/02/24/ab/0224abe935f6a47b7309c36e76e9e77c.gif"/><div class="Informasi"><div>Informasi</div><div>Suhu : </div><div>Kelembapan : </div><div>konsentrasi Gas : </div></div></div>`,
    };
    transporter.sendMail(mailOptions, function (error, info) {
        if (error) {
            console.log(error);
            res.status(400).send({ message: error });
        } else {
            console.log("Email sent: " + info.response);
            res.status(200).send({
                message: `Sukses Mengirim Pesan`,
            });
        }
    });
});
