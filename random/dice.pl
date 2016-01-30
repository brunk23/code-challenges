#!/usr/bin/perl

my $d0 = 1;
my $d1 = 1;
my $d2 = 1;
my $d3 = 1;

my @results;

while ($d0 <=6 ) {
	$d1=1;
	while ($d1 <= 6) {
		$d2=1;
		while ($d2 <= 6) {
			$d3=1;
			while ($d3 <= 6) {
				$results[($d0*$d1*$d2*$d3)]+=1;
				$d3+=1;
			}
			$d2+=1;
		}
		$d1+=1;
	}
	$d0+=1;
}

my $looper = 0;
while ( $looper <= (6*6*6*6)) {
	if ($results[$looper]) { 
		print $looper,": ",$results[$looper],"\n";
	}
	$looper+=1;
}
