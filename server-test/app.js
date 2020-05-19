const express = require('express');
const bodyParser = require('body-parser')
const cors = require('cors');
const http = require('http');
const path = require('path');

const app = express();

var light1 = true;
var light2 = false;

app
   .use(express.static('index.html'))
   .use(cors())
   .use(bodyParser.urlencoded({ extended: true }))
   .use(bodyParser.json());

// Routes
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

app.get('/api/list', (req, res) => {
  console.log('get');
  res.send({ "light1": light1 == "true" ? 1 : 0, "light2": light2 == "true" ? 1 : 0 });
});

app.get('/api/update/light1', (req, res) => {
  console.log('update');
  const status = req.query.status;
  if (status !== undefined) {
    light1 = status;
  }
  res.send({ "light1": light1 == "true" ? 1 : 0, "light2": light2 == "true" ? 1 : 0 });
});

app.get('/api/update/light2', (req, res) => {
  console.log('update');
  const status = req.query.status;
  if (status !== undefined) {
    light2 = status;
  }
  res.send({ "light1": light1 == "true" ? 1 : 0, "light2": light2 == "true" ? 1 : 0 });
});

///////////////////////////////////////////////////
///////////////       RUN      ////////////////////
///////////////////////////////////////////////////
const port = process.env.PORT || 8000;

const server = http.createServer(app);

server.listen(port, () => {
  console.log("Server is running in port:", port) ;
})
