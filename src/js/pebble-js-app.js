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
								var micro;
                                rates = response = JSON.parse(req.responseText);
								value = response.value;
								console.log("Asking price is " + value + ".");
								micro = value*1000000;
								output = "1 DOGE" + "\n = \n" + micro + " " + "\xB5" + "BTC";
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