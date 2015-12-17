#!/usr/bin/perl
use strict;
use warnings;

# @dungeon is an array of numbers.  We use bits to check what is in
# each area.  There could potentially be more than one object in each
# area. But, I currently don't do that.
my $explored_bit_mask=	0x00000001;
my $wall_bit_mask=	0x00000010;
my $bork_bit_mask=	0x00100000;
my $pit_bit_mask=	0x01000000;
my $treasure_bit_mask=	0x00000100;
my $weapon_bit_mask=	0x00010000;
my $exit_door_bit_mask=	0x10000000;
my $unexplored_bit_mask=	0x00000000;
my @dungeon;

my $autoloot=0;
my $insane=0;
my $max_score=0;
my $cheater=0;
my $fresh_kill=0;
my $mapsize=1;
my $msg="\n";
my $borks_killed=0;
my $bork_near=0;
my $pit_near=0;
my $total_points=0;
my $kill_bork_points=10;
my $explore_room=1;
my $find_gold_points=5;
my $find_weapon_points=5;
my $size=20;
my $has_weapon=0;
my $location = 0;

# End Game
sub end_game {
	print "\t*** GAME OVER ***\n\nYou earned ",$total_points;
	print " out of a possible ", $max_score, " points this game.\n\n";
	exit 0;
}

sub give_up {
	print "\nYou leave the dungeon and go and tell everyone about the thousands\n";
	print "of bork monsters you slew. Who cares if it's not true? It's not like\n";
	print "anyone will check.\n\n";
	end_game;
}

sub create_entry_exit {
	my $door_wall = int(rand(4));
	my $door_dist = int(rand($size))+1;
	if($door_wall == 0) {
		$dungeon[$door_dist]=$exit_door_bit_mask;
		$location=$door_dist+$size+2;
	}	
	if($door_wall == 3) {
		$dungeon[($size+2)*($size+1)+$door_dist]=$exit_door_bit_mask;
		$location=($size+2)*($size+1)+$door_dist-($size+2);
	}
	if($door_wall == 2) {
		$dungeon[($door_dist)*($size+2)]=$exit_door_bit_mask;
		$location=($door_dist)*($size+2)+1;
	}
	if($door_wall == 1) {
		$dungeon[($door_dist+1)*($size+2)-1]=$exit_door_bit_mask;
		$location=($door_dist+1)*($size+2)-2;
	}
	$dungeon[$location]=$dungeon[$location]|$explored_bit_mask;
}

# A subroutine to generate the map
sub generate_game_map {
	my $x=0;	
	while($x<($size+2)*($size+2)) {
		$dungeon[$x]=$unexplored_bit_mask;
		$x+=1;
	}
	$x=0;
	# Build walls
	while($x<$size+2) {
		$dungeon[$x]=$wall_bit_mask;
		$dungeon[$x*($size+2)]=$wall_bit_mask;
		$dungeon[$x*($size+2)-1]=$wall_bit_mask;
		$dungeon[($size+1)*($size+2)+$x-1]=$wall_bit_mask;
		$x+=1;
	}
	create_entry_exit;
}

sub fill_world {
	my $rooms=$size*$size;
	my $bork_count=int($rooms*0.15);
	my $treasure_count=int($rooms*0.15);
	my $pit_count=int($rooms*0.05);
	my $weapon_count=int($rooms*.15);
	my $loop=0;
	my $place=0;
	$max_score = $bork_count * $kill_bork_points;
	$max_score += $treasure_count * $find_gold_points;
	$max_score += $weapon_count * $find_weapon_points;
	$max_score += ($rooms - ($bork_count+$treasure_count+$pit_count+
		$weapon_count + 1))* $explore_room;	
	$rooms=($size+2)*($size+2);
	while ($loop < $bork_count) {
		$place=int(rand($rooms));	
		if($dungeon[$place]==$unexplored_bit_mask) {
			if($place != $location) {	
				$loop+=1;
				$dungeon[$place]=$bork_bit_mask;
			}
		}
	}

	$loop=0;
	while ($loop < $pit_count) {
		$place=int(rand($rooms));	
		if($dungeon[$place]==$unexplored_bit_mask) {
			if($place != $location) {	
				$loop+=1;
				$dungeon[$place]=$pit_bit_mask;
			}
		}
	}
	
	$loop=0;
	while ($loop < $treasure_count) {
		$place=int(rand($rooms));	
		if($dungeon[$place]==$unexplored_bit_mask) {
			if($place != $location) {	
				$loop+=1;
				$dungeon[$place]=$treasure_bit_mask;
			}
		}
	}
	
	$loop=0;
	while ($loop < $weapon_count) {
		$place=int(rand($rooms));	
		if($dungeon[$place]==$unexplored_bit_mask) {
			if($place != $location) {	
				$loop+=1;
				$dungeon[$place]=$weapon_bit_mask;
			}
		}
	}
}

# Lose game
sub eaten_bork {
	print "You have been eaten by the bork monster.\n";
	end_game;
}

# Win game
sub slain_bork {
	$fresh_kill=1;
	$total_points+=$kill_bork_points;
	$borks_killed+=1;
	$dungeon[$location]=$dungeon[$location] | $explored_bit_mask;
	$dungeon[$location]=$dungeon[$location] ^ $bork_bit_mask;
}

# if you find the bork and have a weapon, you win.  If you find it
# without a weapon, you lose.
sub fight_bork {
	if( $has_weapon == 1 ) {
		slain_bork;
	}
	else {
		eaten_bork;
	}
}

sub fall_to_death {
	print "AHHHHH.  You fell into a pit!\n\n";
	end_game;
}


# This prints the contents of our surroundings. It must obscure rooms we have
# not entered.
sub print_spot {
	my $spot=$_[0];
	if( $spot  & $exit_door_bit_mask) {
		print "E";
	} else {
	if ( ! ($spot ^ $wall_bit_mask)) {
		print "#";
	} else {
		if( ($spot & $explored_bit_mask) | $cheater) {
			# This first test never happens. It's here in case we want
			# to implement a more advanced fighting system later.	
			if( $spot & $bork_bit_mask) {
					print "B";
				} else {
				if( $spot & $treasure_bit_mask) {
					print "\$";
				} else {
				if ( $spot & $weapon_bit_mask) {
					print "W";
				} else {
				       	if ($spot & $pit_bit_mask) {
					print "X";
				}else {
					print ".";
				}}}}
			} else {
		print "?";
	}
}}}

sub small_map {
	print "\n\t\t\t";
	print_spot $dungeon[($location-($size+2)-1)];
	print_spot $dungeon[($location-($size+2))];
	print_spot $dungeon[($location-($size+2)+1)];
	print "\n\t\t\t";
	print_spot $dungeon[($location-1)];
	print "@";
	print_spot $dungeon[($location+1)];
	print "\n\t\t\t";
	print_spot $dungeon[($location+($size+2)-1)];
	print_spot $dungeon[($location+($size+2))];
	print_spot $dungeon[($location+($size+2)+1)];
	print "\n\n";
	if ( $bork_near ) {
		print "A FOUL STENCH fills your nostrils.\n";
		$bork_near=0;
	} else {
		print "\n";
	}
	if ( $pit_near ) {
		print "A HOWLING WIND assails your ears.\n";
		$pit_near=0;
	} else {
		print "\n";
	}
	if($has_weapon) {
		print "You are ARMED and DANGEROUS\n";
	} else {
		print "You are armed with fists, too bad they'll do you no good\n";
	}
	print "You have killed ",$borks_killed," bork monsters and have ",$total_points," / ",$max_score, " points.\n\n";

	if ( $dungeon[$location] & $treasure_bit_mask ) {
		print "\$\$\$\$\$ There's treasure in this room!. \$\$\$\$\$\n";
	} else {
		if ( $dungeon[$location] & $weapon_bit_mask ) {
			print "***** There's a mighty weapon here. *****\n";
		} else {
			print "This room is empty.\n";
		}
	}
	if($fresh_kill) {
		print "\t\t*************\n\tYou have slain a bork monster!\n";
		print "\t\t*************\n\n";
		$fresh_kill=0;
	}

}

sub large_map {
	my $innie=0;
	my $outie=0;
	while ($outie < ($size+2)) {
		while ($innie < ($size+2)) {
			if ( $location == (($outie * ($size+2)) + $innie)) {
				print "@";
			} else {
				print_spot $dungeon[(($outie*($size+2))+$innie)];
			}	
			$innie+=1;
		}
		if ( $outie == 0 ) {
			if ($fresh_kill) {
				print "\t\t*************";
			}
		}
		if ($outie==1) {
			if($fresh_kill) {
				print "\tYou have slain the bork monster.";
			}
		}
		if ($outie == 2) {
			if($fresh_kill) {
				print "\t\t*************";
				$fresh_kill=0;
			}
		}
		if ( $outie == 3 ) {
			print "\tYou have killed ",$borks_killed," bork monsters"
		}
		if ( $outie == 4) {
			print "\tYou have ",$total_points," / ", $max_score, " points.";
		}
		if ( $outie == 6 ) {

			if($has_weapon) {
				print "\tYou are ARMED and DANGEROUS";
			} else {
				print "\tYou are UNARMED";
			}
		}
		if ( $outie == 7 ) {
			if ( $bork_near ) {
				print "\tA FOUL STENCH fills your nostrils.";
				$bork_near=0;
			}
		}
		if ($outie == 8 ) {
			if ( $pit_near ) {
				print "\tA HOWLING WIND assails your ears.";
				$pit_near=0;
			}
		}
		if ($outie == 9) {
			if ( $dungeon[$location] & $treasure_bit_mask ) {
				print "\t\$\$\$\$\$ There's treasure in this room!. \$\$\$\$\$";
			} else {
				if ( $dungeon[$location] & $weapon_bit_mask ) {
					print "\t***** There's a mighty weapon here. *****";
				} else {
					print "\tThis room is empty.";
				}
			}
		}
		print "\n";
		$innie=0;
		$outie+=1;
	}
}

# This subroutine shows us the visible part of our world. Alerts us to
# potential danger and if there's treasure in this room.
sub display_world {
#  This first combo would check corners too, but we can't move to corners so
# it makes no sense to check them.
#	my $sum =  $dungeon[($location-($size+2)-1)] | $dungeon[($location-($size+2))] | $dungeon[($location-($size+2)+1)] | $dungeon[($location-1)] | $dungeon[($location+1)] | $dungeon[($location+($size+2)-1)] | $dungeon[($location+($size+2))] | $dungeon[($location+($size+2)+1)];
	my $sum =  $dungeon[($location-($size+2))] | $dungeon[($location-1)] | $dungeon[($location+1)] | $dungeon[($location+($size+2))];
	if ( $sum & $bork_bit_mask) {
		$bork_near=1;
	}
	if ( $sum & $pit_bit_mask) {
		$pit_near=1;
	}
	if( $sum  & $exit_door_bit_mask) {
		$msg="The exit door is near. Do you want to run away?\n" . $msg;
	}
	if ( $dungeon[$location] & $bork_bit_mask ) {
		fight_bork;
	}
	if ( $dungeon[$location] & $pit_bit_mask ) {
		fall_to_death;
	}
	if ( $dungeon[$location] & $exit_door_bit_mask ) {
		give_up;
	}
	if(!($dungeon[$location] & $explored_bit_mask)) {
		$total_points+=$explore_room;
		$dungeon[$location]=$dungeon[$location] | $explored_bit_mask;
	}
	if ( $mapsize == 0 ) {
		small_map;
	} else {
		large_map;
	}
}

sub go_south {
	if($dungeon[$location+($size+2)] & $wall_bit_mask) {
		$msg= $msg . "Owww, I'm running into walls now!\n";
	}
	else {
		$location+=($size+2);
	}
}

sub go_north {
	if($dungeon[$location-($size+2)] & $wall_bit_mask) {
		$msg= $msg . "Owww, I'm running into walls now!\n";
	} else {
		$location-=($size+2);
	}
}

sub go_east {
	if($dungeon[$location+1] & $wall_bit_mask) {
		$msg= $msg . "Owww, I'm running into walls now!\n";
	} else {
		$location+=1;
	}
}

sub go_west {
	if($dungeon[$location-1] & $wall_bit_mask) {
		$msg= $msg . "Owww, I'm running into walls now!\n";
	} else {
		$location-=1;
	}
}

sub help {
	print "[N]orth: go North
[S]outh: go South
[E]ast: go East
[W]est: go West
[L]oot: pick up a weapon or treasure
e[X]it: Quit immediately
[M]ap: Change map Size
[A]utoLoot: Automatically loot if possible
[?]: Show this menu\n\n";
	print "From this screen you can change the level of difficulty:
[E]asy: 10x10 dungeon
[M]oderate: 16x16 dungeon
[H]ard: 20x20 dungeon
[I]nsane: 20x20 dungeon, small map, no autoloot\n\n";
	print $msg,"Hit Enter or a command to continue: ";
	$msg="\n";
	my $input = <STDIN>;
	if ( $input =~ m/^[mM]/ ) {
		$size=16;
		$total_points=0;
		$has_weapon=0;
		$borks_killed=0;
		$cheater=0;
		$insane=0;
		$mapsize=1;
		@dungeon=();
		generate_game_map;
		fill_world;
	} else {
	if ( $input =~ m/[hH]/ ) {
		$size=20;
		$total_points=0;
		$has_weapon=0;
		$borks_killed=0;
		$cheater=0;
		$insane=0;
		$mapsize=1;
		@dungeon=();
		generate_game_map;
		fill_world;
	} else {
	if ( $input =~ m/^[iI]/ ) {
		$size=20;
		$mapsize=0;
		$total_points=0;
		$has_weapon=0;
		$borks_killed=0;
		$cheater=0;
		$insane=1;
		$autoloot=0;
		@dungeon=();
		generate_game_map;
		fill_world;
	} else {
	if ( $input =~ m/^[eE]/ ) {
		$size=10;
		$total_points=0;
		$has_weapon=0;
		$borks_killed=0;
		$cheater=0;
		$insane=0;
		$mapsize=1;
		@dungeon=();
		generate_game_map;
		fill_world;
	} else {
	if ( $input =~ m/^[aA]/ ) {
		if( $insane==0 ) {
			$autoloot=$autoloot^1;
		} else {
			$msg = $msg . "No auto looting in insane mode!\n";
		}
	} else {
	if ( $input =~ m/^[xX]/ ) {
		exit 0;	
	} else {
	# undocoumented nicer display
	if ( $input =~ m/^[mM]/ ) {
		if ( $insane==0 ) {
			$mapsize = $mapsize ^ 1;
		} else {
			$msg = $msg . "No large map in insane mode.\n";
		}
	} 
	}}}}}}
}

# loot weapon... easy now, but room for growth
sub loot_weapon {
	$total_points+=$find_weapon_points;	
	$total_points-=$explore_room;
	$has_weapon=1;
	my $rooms=($size+2)*($size+2);
	my $loop=0;
	while ($loop < $rooms) {
		if($dungeon[$loop] & $weapon_bit_mask) {
			$dungeon[$loop]=$dungeon[$loop] ^ $weapon_bit_mask;
			$dungeon[$loop]=$dungeon[$loop] | $treasure_bit_mask;
		}
		$loop+=1;
	}
}

sub loot {
	if($dungeon[$location] & $treasure_bit_mask) {
		$total_points+=$find_gold_points;
		$total_points-=$explore_room;
		$dungeon[$location]=$dungeon[$location] ^ $treasure_bit_mask;
	} else {
	if($dungeon[$location] & $weapon_bit_mask) {
		$dungeon[$location]=$dungeon[$location] ^ $weapon_bit_mask;
		loot_weapon;
	} else {
		if ( $autoloot==0 ) {
			$msg= $msg . "You idiot.  There's nothing to loot here!\n";
		}
	}}
}

sub input_prompt {
	print $msg,"What do you wish to do [N,S,E,W,L,X] (? help): ";
	$msg="\n";
	my $input = <STDIN>;
	if ( $input =~ m/^[sS]/ ) {
		go_south;	
	} else {
	if ( $input =~ m/^\?/ ) {
		help;	
	} else {
	if ( $input =~ m/^[nN]/ ) {
		go_north;	
	} else {
	if ( $input =~ m/^[eE]/ ) {
		go_east;	
	} else {
	if ( $input =~ m/^[wW]/ ) {
		go_west;	
	} else {
	if ( $input =~ m/^[lL]/ ) {
		loot;	
	} else {
	if ( $input =~ m/^[xX]/ ) {
		exit 0;	
	} else {
	# undocoumented nicer display
	if ( $input =~ m/^[mM]/ ) {
		if( $insane==0 ) {
			$mapsize = $mapsize ^ 1;
		} else {
			$msg = $msg . "No large map in insane mode.\n";
		}
	} else {
	if ( $input =~ m/^[aA]/ ) {
		if( $insane==0 ) {	
			$autoloot=$autoloot^1;
		} else {
			$msg = $msg . "No auto looting in insane mode.\n";
		}
	} else {
	if ( $input =~ m/Cheater/ ) {
		if( $insane==0 ) {
			$cheater=$cheater ^ 1;
			$max_score = "CHEATER";		# Does not reset
		} else {
			$msg = $msg . "You're too good to cheat!\n";
			$max_score = "NICE_TRY";
		}
	} else {
		$msg= $msg . "I'm sorry, I didn't understand that.\n";
	}}}}}}}}}}
}


generate_game_map;
fill_world;

# Main loop will be here.
while(1) {
	display_world;
	if ($autoloot) {
		loot;
	}
	input_prompt;
}
