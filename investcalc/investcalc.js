function Loan(termIn, amountIn, rateIn, delayIn) {
	this.term = termIn;
	this.amount = amountIn;
	this.rate = rateIn;
	this.delay = delayIn;
	this.endRes = 0;
	this.increase = 0;
	this.invested = 0;
}

var loans = [];
loans[0] = new Loan(20, 100, 5, 1);
loans[1] = new Loan(20, 100, 6, 1);

function total(loan) {
	var sum = 0;
	invested(loan);
	for(var n = loans[loan].delay;
			n <= ((loans[loan].term * 12) + loans[loan].delay);
			++n) {
		sum += loans[loan].amount * Math.pow(
				(1 + loans[loan].rate / 1200),
				n );
	}
	return sum;
}

function setAmount(loan) {
	loans[loan].amount = document.getElementById('amountInput'+loan).value;
	update();
}

function setRate(loan) {
	loans[loan].rate = document.getElementById("rateInput"+loan).value;
	update();
}

function setTerm(loan) {
	loans[loan].term = document.getElementById("yearsInput"+loan).value;
	update();
}

function invested(loan) {
	loans[loan].invested = loans[loan].amount * 12 * loans[loan].term;
}

function loanResults(loan) {
	document.getElementById('loan'+loan).innerHTML = 
		'Results of Investment<br>The return for $'
		+ loans[loan].amount + " each month for "
		+ loans[loan].term + " years at "
		+ loans[loan].rate + "%.</p>"
		+ '<p>Amount put in: $'
		+ loans[loan].invested.toLocaleString(
				'en-US', {minimumFractionDigits: 2})
		+ '<br>' + "Amount at end: $"
		+ loans[loan].endRes.toLocaleString(
				'en-US', {minimumFractionDigits: 2})
		+ '<br>' + "Amount earned: $"
		+ loans[loan].increase.toLocaleString(
				'en-US', {minimumFractionDigits: 2});
}

function update() {
	loans[0].endRes = total(0);
	loans[1].endRes = total(1);
	loans[0].increase = loans[0].endRes - loans[0].invested;
	loans[1].increase = loans[1].endRes - loans[1].invested;
	loanResults(0);
	loanResults(1);
	document.getElementById("outputBox").innerHTML =
		"Investment #1 matures with <b>$" +
		(loans[1].endRes - loans[0].endRes).toLocaleString(
			       'en-US', {minimumFractionDigits: 2})
		+ "</b> less than Investment #2."; 
}
