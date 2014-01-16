Pebble.addEventListener("ready",
  function(e) {
    console.log("JavaScript app ready and running!");
	getPrice();
  }
);

function getPrice() {
        var response;
        var req = new XMLHttpRequest();
        
        var rates;
        
        req.open('GET', "https://api.vircurex.com/api/get_last_trade.json?base=DOGE&alt=BTC", true);
        req.onreadystatechange = function(e) {
                if (req.readyState == 4) {
                        if(req.status == 200) {
								var value;
								var output;
                                rates = response = JSON.parse(req.responseText);
								value = response.value;
								output = "1 DOGE = " + value + " BTC";
								console.log("Asking price is " + value + ".");
								console.log(output);
                                var message = {
								"value": output.toString()
                                };
                                
                                console.log("Sending...");
                                console.log(JSON.stringify(message));
                                Pebble.sendAppMessage(message);
                                
                        } else {
                                console.log("Error " + req.status);
                        }
                }
        };
        req.send(null);
}