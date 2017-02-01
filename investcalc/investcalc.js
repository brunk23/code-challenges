var years = 20;	// Length of investment
var amount = 100;	// Amount Monthly
var rate = 9;		// Percent Return
var previous = 0;	// For comparing

function total() {
	var sum = 0;
	for(var n = 0; n <= ((years * 12) - 1); ++n) {
		sum += amount * Math.pow( (1 + rate / 1200), n );
	}
	return sum;
}

function setAmount() {
	amount = document.getElementById("amountInput").value;
	update();
}

function setRate() {
	rate = document.getElementById("rateInput").value;
	update();
}

function setTerm() {
	years = document.getElementById("yearsInput").value;
	update();
}

function setPrevious() {
	previous = document.getElementById("previousInput").value;
	update();
}

function update() {
	var endRes = total();
	var putIn = amount * 12 * years;
	var incr = endRes - putIn;
	var improve = endRes - previous;
	document.getElementById("outputBox").innerHTML = '<p>'
		+ "The returns for $" + amount + " each month for "
		+ years + " years at " + rate + "%.</p>"
		+ '<p>Amount put in: $'
		+ putIn.toLocaleString('en-US', {minimumFractionDigits: 2})
		+ '<br>' + "Amount at end: $"
		+ endRes.toLocaleString('en-US', {minimumFractionDigits: 2})
		+ ' ( Difference from Previous: $'
		+ improve.toLocaleString('en-US', {minimumFractionDigits: 2})
		+ ' )' + '<br>' + "Amount earned: $"
		+ incr.toLocaleString('en-US', {minimumFractionDigits: 2})
		+ '</p>';
}
