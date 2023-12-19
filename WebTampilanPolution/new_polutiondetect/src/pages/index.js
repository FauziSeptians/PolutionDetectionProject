import { Inter } from "next/font/google";
import { useEffect, useState, useRef } from "react";
import axios from "axios";
import * as React from "react";
import Card from "@mui/material/Card";
import CardActions from "@mui/material/CardActions";
import CardContent from "@mui/material/CardContent";
import CardMedia from "@mui/material/CardMedia";
import Button from "@mui/material/Button";
import Typography from "@mui/material/Typography";

let sendmail = false;

export default function Home() {
    const [Result, setResult] = useState("");
    const [Humidity, setHumidity] = useState(null);
    const [Temperature, setTemperature] = useState(null);
    const [Gas, setGas] = useState(null);

    // let Result = "Bad"

    const fetchData = () => {
        axios
            .get(
                "/api/blynkv2"
            )
            .then((response) => {
                console.log(response);
                setResult(response.data);
            });

        axios   
            .get(
                "/api/blynkv0"
            )
            .then((response) => {
                console.log(response);
                setHumidity(response.data);
            });

        axios
            .get(
                "/api/blynkv4"
            )
            .then((response) => {
                console.log(response);
                setTemperature(response.data);
            });

        axios
            .get(
                "/api/blynkv1"
            )
            .then((response) => {
                console.log(response);
                setGas(response.data);
            });
    };

    useEffect(() => {
        const interval = setInterval(() => {
            fetchData();
        }, 1000);

        return () => clearInterval(interval);
    }, []);

    const videoRef = useRef(null);

    useEffect(() => {
        if (videoRef.current) {
            videoRef.current.play();
        }
    });

   

    useEffect(() => {
        console.log(Result.includes("Bad"));

        if (Result.includes("Bad")) {
            if (sendmail == false) {
                axios.post(`${NEXT_PUBLIC_PORT_SERVER}/sendMail`,{
                    
                    body : {
                        Humidity : Humidity,
                        Gas : Gas,
                        Temperature : Temperature,
                    }
                }).then((response) => {
                    console.log(response);
                })
                sendmail = true;
            }
        } else {
            sendmail = false;
        }
    });

    return (
        <>
            <div className="p-5 bg-green-100">
                <div className="w-full h-screen">
                    <div
                        className="flex justify-center w-full mb-4"
                        style={{ fontSize: "35px" }}
                    >
                        Polution Detection
                    </div>
                    <div className="flex justify-center gap-3 mb-4">
                        <Card>
                            <CardMedia
                                sx={{ height: 140 }}
                                image="data:image/jpeg;base64,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"
                                title="green iguana"
                            />
                            <CardContent>
                                <Typography
                                    gutterBottom
                                    variant="h5"
                                    component="div"
                                >
                                    Humidity
                                </Typography>
                                <Typography
                                    variant="body2"
                                    color="text.secondary"
                                >
                                    konsentrasi kandungan dari uap air yang ada
                                    di udara
                                </Typography>
                            </CardContent>
                            <CardActions>
                                <Button size="small">{Humidity} %</Button>
                                {/* <Button size="small">Learn More</Button> */}
                            </CardActions>
                        </Card>
                        <Card>
                            <CardMedia
                                sx={{ height: 140 }}
                                image="https://cms-tugu-prod.afedigi.com/files/2022/10/Sumber-Panas-Bumi-1-scaled.jpg"
                                title="green iguana"
                            />
                            <CardContent>
                                <Typography
                                    gutterBottom
                                    variant="h5"
                                    component="div"
                                >
                                    Gas
                                </Typography>
                                <Typography
                                    variant="body2"
                                    color="text.secondary"
                                >
                                    konsentrasi kandungan dari uap air yang ada
                                    di udara
                                </Typography>
                            </CardContent>
                            <CardActions>
                                <Button size="small">{Gas} PPM</Button>
                                {/* <Button size="small">Learn More</Button> */}
                            </CardActions>
                        </Card>
                        <Card>
                            <CardMedia
                                sx={{ height: 140 }}
                                image="data:image/jpeg;base64,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"
                                title="green iguana"
                            />
                            <CardContent>
                                <Typography
                                    gutterBottom
                                    variant="h5"
                                    component="div"
                                >
                                    Temperature
                                </Typography>
                                <Typography
                                    variant="body2"
                                    color="text.secondary"
                                >
                                    konsentrasi kandungan dari uap air yang ada
                                    di udara
                                </Typography>
                            </CardContent>
                            <CardActions>
                                <Button size="small">{Temperature} C</Button>
                                {/* <Button size="small">Learn More</Button> */}
                            </CardActions>
                        </Card>
    
                    </div>
                 
                    <div className="w-full flex justify-center">
                        {Result.includes("Good") ? (
                           <div>
                             <div className="mt-5 w-full flex justify-center mb-3" style={{fontSize:"25px"}}>{Result}</div>
                             <div>
                                <img src="https://media.tenor.com/Q5pjo7CE1mEAAAAC/good-bt21.gif"   width={500}></img>
                             </div>
                           </div>
                        ) : null}
                        {Result.includes("Bad") ? (
                            <>
                                <div className="mt-5">
                                    <div className="w-full flex justify-center">
                                        <div>
                                            <video
                                                src="https://i.pinimg.com/originals/02/24/ab/0224abe935f6a47b7309c36e76e9e77c.gif"
                                                loop
                                                width={500}
                                            ></video>
                                        </div>
                                    </div>
                                    <div style={{ color: "red", fontSize : "25px", marginTop  :"20px"}}>
                                        Polusi diluar sana berbahaya, kamu harus
                                        menggunakan Masker !!!
                                    </div>
                                </div>
                            </>
                        ) : (
                            ""
                        )}
                    </div>
                   
                </div>
            </div>
        </>
    );
}
