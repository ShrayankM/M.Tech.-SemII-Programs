var http = require("http");

var keyArray = [];



var myServer = http.createServer(function(request, response){

    //allows access
    response.setHeader('Access-Control-Allow-Origin', '*');

    //display key in terminal
    console.log(request.url)

})

console.log('server is running...')
myServer.listen(5000);
