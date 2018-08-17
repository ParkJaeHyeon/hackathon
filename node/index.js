var app = require('express')();
var http = require('http').Server(app);
var fs = require('fs');
var mysql = require('mysql');
var connection = mysql.createConnection({
    host: '192.168.2.91',
    user: 'jin',
    password: '1234',
    port: 3305,
    database : 'jin'
  });
 
  connection.connect();

connection.query('SELECT * from Persons', function(err, rows, fields) {
  if (!err)
          console.log('The solution is: ', rows);
        else
          console.log('Error while performing Query.', err);
      });

connection.end();
      
app.get('/', function (req, res) {
res.sendFile(__dirname + '/index.html');
});

http.listen(3000, function () {
    console.log('listening on *:3000');
});

app.get('/imgs', function (req, res) {
    fs.readFile('0505.png', function (error, data) {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(data);
    });
});

app.get('/clientlist', function (req, res) {
    fs.readFile('list.png', function (error, data) {
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(data);
    });
});

