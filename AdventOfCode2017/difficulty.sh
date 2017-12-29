#!/usr/bin/awk -f
BEGIN{
	total = 0;
	stars = 0;
}
{
	day = $1;
	both = $2;
	single = $3;
	n = 100 * single / ( single + both );
	stars = stars + 2 * both + single;
	total = total + n;
	printf "%0.2f%%\tout of\t%i\tonly did part one of Day %i\n", n, both + single, day;
}
END{
	printf "\nAverage day: %0.2f%%\n", total / 25;
	printf "%i total stars awarded.\n", stars;
}
