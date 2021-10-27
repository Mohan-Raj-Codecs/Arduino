const express = require('express');
const fs = require('fs');
const app = express();
const { JSDOM } = require('jsdom');

global.document = new JSDOM('index.html').window.document;

var fileName="./data.json";
var on_data='{"on":true}';
var off_data='{"on":false}';

var a = document.getElementById("on");//.addEventListener(onclick,on());
document.getElementById("off");//.addEventListener(onclick,off());

a.innerHTML="fk";

function on(){
	fs.writeFile(fileName, on_data, (err) => {
		if (err) throw err;
		console.log('Data written to file');
	});
	console.log("On");
}
function off(){
	fs.writeFile(fileName, off_data, (err) => {
		if (err) throw err;
		console.log('Data written to file');
	});
	console.log("Off");
}


app.listen(8080, () => console.log('listening at 8080'));
app.use(express.static('./'));
