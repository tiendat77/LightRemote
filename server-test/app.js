const express = require('express');
const bodyParser = require('body-parser')
const cors = require('cors');
const http = require('http');
const path = require('path');

const app = express();

app
   .use(express.static('index.html'))
   .use(cors())
   .use(bodyParser.urlencoded({ extended: true }))
   .use(bodyParser.json());

// Routes
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

app.get('/api/status', (req, res) => {
  console.log('get status');
  res.json({
    light1: true,
    light2: false
  });
});

///////////////////////////////////////////////////
///////////////       RUN      ////////////////////
///////////////////////////////////////////////////
const port = process.env.PORT || 8000;

const server = http.createServer(app);

server.listen(port, () => {
  console.log("Server is running in port:", port) ;
})
