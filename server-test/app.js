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
  console.log('get status');
  res.json({ light1, light2 });
});

app.get('/api/update', (req, res) => {
  console.log('update status');
  res.json({ light1, light2 });
});

///////////////////////////////////////////////////
///////////////       RUN      ////////////////////
///////////////////////////////////////////////////
const port = process.env.PORT || 8000;

const server = http.createServer(app);

server.listen(port, () => {
  console.log("Server is running in port:", port) ;
})
