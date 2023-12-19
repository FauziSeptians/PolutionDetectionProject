// Next.js API route support: https://nextjs.org/docs/api-routes/introduction
import axios from "axios";
export default function handler(req, res) {
   axios.get(
      `https://blynk.cloud/external/api/get?token=${process.env.BLYNK_AUTH_TOKEN}&v1`
   ).then((response) => {
      if (response.status === 200) {
         res.status(200).send(response.data);
      } else if (response.status === 404) {
         res.status(404).send({ data: null });
      }
   });
}
