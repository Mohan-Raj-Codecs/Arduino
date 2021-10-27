const express = require('express')
const app = express()
const bodyParser = require('body-parser')
const cors = require('cors');
const port = 8080;

app.use(bodyParser.json());

app.use(bodyParser.urlencoded({
    extended: true}));

app.use(cors());

app.get('/in',(req,res)=>{
    console.log("Someone entered")
})

app.post('/',(req,res)=>{
    console.log("On node")
})

app.post('/in.html',(req,res)=>{
    console.log("Received res")
    console.log(req.body.API)
    
})


app.listen(port,()=>{
    console.log("Server is listening at port 8080")
})
app.use(express.static('./'))