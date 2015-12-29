var http = require('http');

const PORT=8080; 

function handleRequest(request, response){
  response.end('Client request arrived: ' + request.url);
  var params = require('url').parse(request.url, true);
  //console.log("Params: %O", params);
  if (params.pathname=="/gps") {
    console.log("Is GPS");
  }
}

var server = http.createServer(handleRequest);

server.listen(PORT, function(){
  console.log("Server listening on: http://localhost:%s", PORT);
});