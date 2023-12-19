import axios from "axios";

export default function handler(req, res) {
  axios.get(`https://blynk.cloud/external/api/get?token=${process.env.BLYNK_AUTH_TOKEN}&v2`)
    .then((response) => {
      if (response.status === 200) {
        res.status(200).send(response.data);
      } else {
        // Send a generic error response for any other status code
        res.status(response.status || 500).send({
          error: "Unexpected status code or error",
          data: null
        });
      }
    })
    .catch((error) => {
      // Handle any errors that occur during the request
      console.error("Error fetching data:", error);
      res.status(500).send({ error: "Internal server error", data: null });
    });
}
