#include <iostream>

using std::cout;
using std::endl;

struct element {
	int length;
	int evolves[6];
};

const int ELEMENTS = 93;

/*
 * Be able to refer to the elements by name instead of number to reduce
 * errors down below.
 */
enum name {
	H = 1,	He,	Li,	Be,	B,	C,	N,	O,	F,
	Ne,	Na,	Mg,	Al,	Si,	P,	S,	Cl,	Ar,
	K,	Ca,	Sc,	Ti,	V,	Cr,	Mn,	Fe,	Co,
	Ni,	Cu,	Zn,	Ga,	Ge,	As,	Se,	Br,	Kr,
	Rb,	Sr,	Y,	Zr,	Nb,	Mo,	Tc,	Ru,	Rh,
	Pd,	Ag,	Cd,	In,	Sn,	Sb,	Te,	I,	Xe,
	Cs,	Ba,	La,	Ce,	Pr,	Nd,	Pm,	Sm,	Eu,
	Gd,	Tb,	Dy,	Ho,	Er,	Tm,	Yb,	Lu,	Hf,
	Ta,	W,	Re,	Os,	Ir,	Pt,	Au,	Hg,	Tl,
	Pb,	Bi,	Po,	At,	Rn,	Fr,	Ra,	Ac,	Th,
	Pa,	U
};

void init_table(element table[ELEMENTS]);
unsigned long look_say_length(element table[ELEMENTS], int elem, int depth);

int main()
{
	// We make a table of 93 to keep the numbering
	// consistant with the table
	element table[ELEMENTS];

	init_table(table);

	// We are looking for the 40th (part 1) and 50th (part 2)
	// evolution of the string "1321131112" ... which happens to
	// be element #70 "Yb", so we call the function with that
	// as the element to evolve.

	cout << "Part 1 (40 evolutions): "
		<< look_say_length(table, 70, 40) << endl
		<< "Part 2 (50 evolutions): "
		<< look_say_length(table, 70, 50) << endl;


	return 0;
}

/*
 * This will call itself until it has reached the last required evolution.
 * At that point, it will return the length of the element it was called
 * with. If there are still more evolutions to do, it will call itself
 * on each of the strings it evolves to and reduce the remaining evolutions
 * by one.
 */
unsigned long look_say_length(element table[ELEMENTS], int elem, int depth) 
{
	unsigned long total = 0;
	if ( depth == 0 ) {
		return table[elem].length;
	}
	
	/*
	 * If we aren't at the last depth, call ourselves for each of the
	 * evolves states that this element has (reducing the depth of
	 * remaining evolution by 1). For add the total length for each
	 * of the possible states.
	 */
	for(int x = 0; x < 6; ++x) {
		if( table[elem].evolves[x] > 0 ) {
			total += look_say_length(table, table[elem].evolves[x], depth - 1);
		}
	}
	return total;
}

/*
 * We hard code Conway's table and relationships
 * From: http://www.se16.info/js/lands2.htm
 *
 * I don't know if there is a way to generate this. While each element
 * decays into the next lowest element, it doesn't always do just that.
 * So I hard code.
 */
void init_table(element table[ELEMENTS]) {
	table[0].length = 0;
	table[0].evolves[0] = 0;
	table[0].evolves[1] = 0;
	table[0].evolves[2] = 0;
	table[0].evolves[3] = 0;
	table[0].evolves[4] = 0;
	table[0].evolves[5] = 0;

	// H "22" -> H (does not evolve)
	table[H].length = 2;
	table[H].evolves[0] = H;
	table[H].evolves[1] = 0;
	table[H].evolves[2] = 0;
	table[H].evolves[3] = 0;
	table[H].evolves[4] = 0;
	table[H].evolves[5] = 0;
	
	// He "13112221133211322112211213322112" -> Hf Pa H Ca Li
	table[He].length = 32;
	table[He].evolves[0] = Hf;
	table[He].evolves[1] = Pa;
	table[He].evolves[2] = H;
	table[He].evolves[3] = Ca;
	table[He].evolves[4] = Li;
	table[He].evolves[5] = 0;
	
	// Li "312211322212221121123222112" -> He
	table[Li].length = 27;
	table[Li].evolves[0] = He;
	table[Li].evolves[1] = 0;
	table[Li].evolves[2] = 0;
	table[Li].evolves[3] = 0;
	table[Li].evolves[4] = 0;
	table[Li].evolves[5] = 0;
	
	// Be "111312211312113221133211322112211213322112" -> Ge Ca Li
	table[Be].length = 42;
	table[Be].evolves[0] = Ge;
	table[Be].evolves[1] = Ca;
	table[Be].evolves[2] = Li;;
	table[Be].evolves[3] = 0;
	table[Be].evolves[4] = 0;
	table[Be].evolves[5] = 0;
	
	// B "1321132122211322212221121123222112" -> Be
	table[B].length = 34;
	table[B].evolves[0] = Be;
	table[B].evolves[1] = 0;
	table[B].evolves[2] = 0;
	table[B].evolves[3] = 0;
	table[B].evolves[4] = 0;
	table[B].evolves[5] = 0;
	
	// C "3113112211322112211213322112" -> B
	table[C].length = 28;
	table[C].evolves[0] = B;
	table[C].evolves[1] = 0;
	table[C].evolves[2] = 0;
	table[C].evolves[3] = 0;
	table[C].evolves[4] = 0;
	table[C].evolves[5] = 0;
	
	// N "111312212221121123222112" -> C
	table[N].length = 24;
	table[N].evolves[0] = C;
	table[N].evolves[1] = 0;
	table[N].evolves[2] = 0;
	table[N].evolves[3] = 0;
	table[N].evolves[4] = 0;
	table[N].evolves[5] = 0;

	// O "132112211213322112" -> N
	table[O].length = 18;
	table[O].evolves[0] = N;
	table[O].evolves[1] = 0;
	table[O].evolves[2] = 0;
	table[O].evolves[3] = 0;
	table[O].evolves[4] = 0;
	table[O].evolves[5] = 0;

	// F "31121123222112" -> O
	table[F].length = 14;
	table[F].evolves[0] = O;
	table[F].evolves[1] = 0;
	table[F].evolves[2] = 0;
	table[F].evolves[3] = 0;
	table[F].evolves[4] = 0;
	table[F].evolves[5] = 0;

	// Ne "111213322112" -> F
	table[Ne].length = 12;
	table[Ne].evolves[0] = F;
	table[Ne].evolves[1] = 0;
	table[Ne].evolves[2] = 0;
	table[Ne].evolves[3] = 0;
	table[Ne].evolves[4] = 0;
	table[Ne].evolves[5] = 0;

	// Na "123222112" -> Ne
	table[Na].length = 9;
	table[Na].evolves[0] = Ne;
	table[Na].evolves[1] = 0;
	table[Na].evolves[2] = 0;
	table[Na].evolves[3] = 0;
	table[Na].evolves[4] = 0;
	table[Na].evolves[5] = 0;

	// Mg "3113322112" -> Pm Na
	table[Mg].length = 10;
	table[Mg].evolves[0] = Pm;
	table[Mg].evolves[1] = Na;
	table[Mg].evolves[2] = 0;
	table[Mg].evolves[3] = 0;
	table[Mg].evolves[4] = 0;
	table[Mg].evolves[5] = 0;

	// Al "1113222112" -> Mg
	table[Al].length = 10;
	table[Al].evolves[0] = Mg;
	table[Al].evolves[1] = 0;
	table[Al].evolves[2] = 0;
	table[Al].evolves[3] = 0;
	table[Al].evolves[4] = 0;
	table[Al].evolves[5] = 0;

	// Si "1322112" -> Al
	table[Si].length = 7;
	table[Si].evolves[0] = Al;
	table[Si].evolves[1] = 0;
	table[Si].evolves[2] = 0;
	table[Si].evolves[3] = 0;
	table[Si].evolves[4] = 0;
	table[Si].evolves[5] = 0;

	// P "311311222112" -> Ho Si
	table[P].length = 12;
	table[P].evolves[0] = Ho;
	table[P].evolves[1] = Si;
	table[P].evolves[2] = 0;
	table[P].evolves[3] = 0;
	table[P].evolves[4] = 0;
	table[P].evolves[5] = 0;

	// S "1113122112" -> P
	table[S].length = 10;
	table[S].evolves[0] = P;
	table[S].evolves[1] = 0;
	table[S].evolves[2] = 0;
	table[S].evolves[3] = 0;
	table[S].evolves[4] = 0;
	table[S].evolves[5] = 0;

	// Cl "132112" -> S
	table[Cl].length = 6;
	table[Cl].evolves[0] = S;
	table[Cl].evolves[1] = 0;
	table[Cl].evolves[2] = 0;
	table[Cl].evolves[3] = 0;
	table[Cl].evolves[4] = 0;
	table[Cl].evolves[5] = 0;

	// Ar "3112" -> Cl
	table[Ar].length = 4;
	table[Ar].evolves[0] = Cl;
	table[Ar].evolves[1] = 0;
	table[Ar].evolves[2] = 0;
	table[Ar].evolves[3] = 0;
	table[Ar].evolves[4] = 0;
	table[Ar].evolves[5] = 0;

	// K "1112" -> Ar
	table[K].length = 4;
	table[K].evolves[0] = Ar;
	table[K].evolves[1] = 0;
	table[K].evolves[2] = 0;
	table[K].evolves[3] = 0;
	table[K].evolves[4] = 0;
	table[K].evolves[5] = 0;

	// Ca "12" -> K
	table[Ca].length = 2;
	table[Ca].evolves[0] = K;
	table[Ca].evolves[1] = 0;
	table[Ca].evolves[2] = 0;
	table[Ca].evolves[3] = 0;
	table[Ca].evolves[4] = 0;
	table[Ca].evolves[5] = 0;

	// Sc "3113112221133112" -> Ho Pa H Ca Co
	table[Sc].length = 16;
	table[Sc].evolves[0] = Ho;
	table[Sc].evolves[1] = Pa;
	table[Sc].evolves[2] = H;
	table[Sc].evolves[3] = Ca;
	table[Sc].evolves[4] = Co;
	table[Sc].evolves[5] = 0;

	// Ti "11131221131112" -> Sc
	table[Ti].length = 14;
	table[Ti].evolves[0] = Sc;
	table[Ti].evolves[1] = 0;
	table[Ti].evolves[2] = 0;
	table[Ti].evolves[3] = 0;
	table[Ti].evolves[4] = 0;
	table[Ti].evolves[5] = 0;

	// V "13211312" -> Ti
	table[V].length = 8;
	table[V].evolves[0] = Ti;
	table[V].evolves[1] = 0;
	table[V].evolves[2] = 0;
	table[V].evolves[3] = 0;
	table[V].evolves[4] = 0;
	table[V].evolves[5] = 0;

	// Cr "31132" -> V
	table[Cr].length = 5;
	table[Cr].evolves[0] = V;
	table[Cr].evolves[1] = 0;
	table[Cr].evolves[2] = 0;
	table[Cr].evolves[3] = 0;
	table[Cr].evolves[4] = 0;
	table[Cr].evolves[5] = 0;
	
	// Mn "111311222112" -> Cr Si
	table[Mn].length = 12;
	table[Mn].evolves[0] = Cr;
	table[Mn].evolves[1] = Si;
	table[Mn].evolves[2] = 0;
	table[Mn].evolves[3] = 0;
	table[Mn].evolves[4] = 0;
	table[Mn].evolves[5] = 0;
	
	// Fe "13122112" -> Mn
	table[Fe].length = 8;
	table[Fe].evolves[0] = Mn;
	table[Fe].evolves[1] = 0;
	table[Fe].evolves[2] = 0;
	table[Fe].evolves[3] = 0;
	table[Fe].evolves[4] = 0;
	table[Fe].evolves[5] = 0;
	
	// Co "32112" -> Fe
	table[Co].length = 5;
	table[Co].evolves[0] = Fe;
	table[Co].evolves[1] = 0;
	table[Co].evolves[2] = 0;
	table[Co].evolves[3] = 0;
	table[Co].evolves[4] = 0;
	table[Co].evolves[5] = 0;
	
	// Ni "11133112" -> Zn Co
	table[Ni].length = 8;
	table[Ni].evolves[0] = Zn;
	table[Ni].evolves[1] = Co;
	table[Ni].evolves[2] = 0;
	table[Ni].evolves[3] = 0;
	table[Ni].evolves[4] = 0;
	table[Ni].evolves[5] = 0;
	
	// Cu "131112" -> Ni
	table[Cu].length = 6;
	table[Cu].evolves[0] = Ni;
	table[Cu].evolves[1] = 0;
	table[Cu].evolves[2] = 0;
	table[Cu].evolves[3] = 0;
	table[Cu].evolves[4] = 0;
	table[Cu].evolves[5] = 0;
	
	// Zn "312" -> Cu
	table[Zn].length = 3;
	table[Zn].evolves[0] = Cu;
	table[Zn].evolves[1] = 0;
	table[Zn].evolves[2] = 0;
	table[Zn].evolves[3] = 0;
	table[Zn].evolves[4] = 0;
	table[Zn].evolves[5] = 0;

	// Ga "13221133122211332" -> Eu Ca Ac H Ca Zn
	table[Ga].length = 17;
	table[Ga].evolves[0] = Eu;
	table[Ga].evolves[1] = Ca;
	table[Ga].evolves[2] = Ac;
	table[Ga].evolves[3] = H;
	table[Ga].evolves[4] = Ca;
	table[Ga].evolves[5] = Zn;

	// Ge "31131122211311122113222" -> Ho Ga
	table[Ge].length = 23;
	table[Ge].evolves[0] = Ho;
	table[Ge].evolves[1] = Ga;
	table[Ge].evolves[2] = 0;
	table[Ge].evolves[3] = 0;
	table[Ge].evolves[4] = 0;
	table[Ge].evolves[5] = 0;

	// As "11131221131211322113322112" -> Ge Na
	table[As].length = 26;
	table[As].evolves[0] = Ge;
	table[As].evolves[1] = Na;
	table[As].evolves[2] = 0;
	table[As].evolves[3] = 0;
	table[As].evolves[4] = 0;
	table[As].evolves[5] = 0;

	// Se "13211321222113222112" -> As
	table[Se].length = 20;
	table[Se].evolves[0] = As;
	table[Se].evolves[1] = 0;
	table[Se].evolves[2] = 0;
	table[Se].evolves[3] = 0;
	table[Se].evolves[4] = 0;
	table[Se].evolves[5] = 0;

	// Br "3113112211322112" -> Se
	table[Br].length = 16;
	table[Br].evolves[0] = Se;
	table[Br].evolves[1] = 0;
	table[Br].evolves[2] = 0;
	table[Br].evolves[3] = 0;
	table[Br].evolves[4] = 0;
	table[Br].evolves[5] = 0;

	// Kr "11131221222112" -> Br
	table[Kr].length = 14;
	table[Kr].evolves[0] = Br;
	table[Kr].evolves[1] = 0;
	table[Kr].evolves[2] = 0;
	table[Kr].evolves[3] = 0;
	table[Kr].evolves[4] = 0;
	table[Kr].evolves[5] = 0;

	// Rb "1321122112" -> Kr
	table[Rb].length = 10;
	table[Rb].evolves[0] = Kr;
	table[Rb].evolves[1] = 0;
	table[Rb].evolves[2] = 0;
	table[Rb].evolves[3] = 0;
	table[Rb].evolves[4] = 0;
	table[Rb].evolves[5] = 0;

	// Sr "3112112" -> Rb
	table[Sr].length = 7;
	table[Sr].evolves[0] = Rb;
	table[Sr].evolves[1] = 0;
	table[Sr].evolves[2] = 0;
	table[Sr].evolves[3] = 0;
	table[Sr].evolves[4] = 0;
	table[Sr].evolves[5] = 0;

	// Y "1112133" -> Sr U
	table[Y].length = 7;
	table[Y].evolves[0] = Sr;
	table[Y].evolves[1] = U;
	table[Y].evolves[2] = 0;
	table[Y].evolves[3] = 0;
	table[Y].evolves[4] = 0;
	table[Y].evolves[5] = 0;

	// Zr "12322211331222113112211" -> Y H Ca Tc
	table[Zr].length = 23;
	table[Zr].evolves[0] = Y;
	table[Zr].evolves[1] = H;
	table[Zr].evolves[2] = Ca;
	table[Zr].evolves[3] = Tc;
	table[Zr].evolves[4] = 0;
	table[Zr].evolves[5] = 0;

	// Nb "1113122113322113111221131221" -> Er Zr
	table[Nb].length = 28;
	table[Nb].evolves[0] = Er;
	table[Nb].evolves[1] = Zr;
	table[Nb].evolves[2] = 0;
	table[Nb].evolves[3] = 0;
	table[Nb].evolves[4] = 0;
	table[Nb].evolves[5] = 0;

	// Mo "13211322211312113211" -> Nb
	table[Mo].length = 20;
	table[Mo].evolves[0] = Nb;
	table[Mo].evolves[1] = 0;
	table[Mo].evolves[2] = 0;
	table[Mo].evolves[3] = 0;
	table[Mo].evolves[4] = 0;
	table[Mo].evolves[5] = 0;

	// Tc "311322113212221" -> Mo
	table[Tc].length = 15;
	table[Tc].evolves[0] = Mo;
	table[Tc].evolves[1] = 0;
	table[Tc].evolves[2] = 0;
	table[Tc].evolves[3] = 0;
	table[Tc].evolves[4] = 0;
	table[Tc].evolves[5] = 0;

	// Ru "132211331222113112211" Eu Ca Tc
	table[Ru].length = 21;
	table[Ru].evolves[0] = Eu;
	table[Ru].evolves[1] = Ca;
	table[Ru].evolves[2] = Tc;
	table[Ru].evolves[3] = 0;
	table[Ru].evolves[4] = 0;
	table[Ru].evolves[5] = 0;

	// Rh "311311222113111221131221" -> Ho Ru
	table[Rh].length = 24;
	table[Rh].evolves[0] = Ho;
	table[Rh].evolves[1] = Ru;
	table[Rh].evolves[2] = 0;
	table[Rh].evolves[3] = 0;
	table[Rh].evolves[4] = 0;
	table[Rh].evolves[5] = 0;

	// Pd "111312211312113211" -> Rh
	table[Pd].length = 18;
	table[Pd].evolves[0] = Rh;
	table[Pd].evolves[1] = 0;
	table[Pd].evolves[2] = 0;
	table[Pd].evolves[3] = 0;
	table[Pd].evolves[4] = 0;
	table[Pd].evolves[5] = 0;

	// Ag "132113212221" -> Pd
	table[Ag].length = 12;
	table[Ag].evolves[0] = Pd;
	table[Ag].evolves[1] = 0;
	table[Ag].evolves[2] = 0;
	table[Ag].evolves[3] = 0;
	table[Ag].evolves[4] = 0;
	table[Ag].evolves[5] = 0;
	
	// Cd "3113112211" -> Ag
	table[Cd].length = 10;
	table[Cd].evolves[0] = Ag;
	table[Cd].evolves[1] = 0;
	table[Cd].evolves[2] = 0;
	table[Cd].evolves[3] = 0;
	table[Cd].evolves[4] = 0;
	table[Cd].evolves[5] = 0;
	
	// In "11131221" -> Cd
	table[In].length = 8;
	table[In].evolves[0] = Cd;
	table[In].evolves[1] = 0;
	table[In].evolves[2] = 0;
	table[In].evolves[3] = 0;
	table[In].evolves[4] = 0;
	table[In].evolves[5] = 0;
	
	// Sn "13211" -> In
	table[Sn].length = 5;
	table[Sn].evolves[0] = In;
	table[Sn].evolves[1] = 0;
	table[Sn].evolves[2] = 0;
	table[Sn].evolves[3] = 0;
	table[Sn].evolves[4] = 0;
	table[Sn].evolves[5] = 0;
	
	// Sb "3112221" -> Pm Sn
	table[Sb].length = 7;
	table[Sb].evolves[0] = Pm;
	table[Sb].evolves[1] = Sn;
	table[Sb].evolves[2] = 0;
	table[Sb].evolves[3] = 0;
	table[Sb].evolves[4] = 0;
	table[Sb].evolves[5] = 0;
	
	// Te "1322113312211" -> Eu Ca Sb
	table[Te].length = 13;
	table[Te].evolves[0] = Eu;
	table[Te].evolves[1] = Ca;
	table[Te].evolves[2] = Sb;
	table[Te].evolves[3] = 0;
	table[Te].evolves[4] = 0;
	table[Te].evolves[5] = 0;
	
	// I "311311222113111221" -> Ho Te
	table[I].length = 18;
	table[I].evolves[0] = Ho;
	table[I].evolves[1] = Te;
	table[I].evolves[2] = 0;
	table[I].evolves[3] = 0;
	table[I].evolves[4] = 0;
	table[I].evolves[5] = 0;

	// Xe "11131221131211" -> I
	table[Xe].length = 14;
	table[Xe].evolves[0] = I;
	table[Xe].evolves[1] = 0;
	table[Xe].evolves[2] = 0;
	table[Xe].evolves[3] = 0;
	table[Xe].evolves[4] = 0;
	table[Xe].evolves[5] = 0;

	// Cs "13211321" -> Xe
	table[Cs].length = 8;
	table[Cs].evolves[0] = Xe;
	table[Cs].evolves[1] = 0;
	table[Cs].evolves[2] = 0;
	table[Cs].evolves[3] = 0;
	table[Cs].evolves[4] = 0;
	table[Cs].evolves[5] = 0;

	// Ba "311311" -> Cs
	table[Ba].length = 6;
	table[Ba].evolves[0] = Cs;
	table[Ba].evolves[1] = 0;
	table[Ba].evolves[2] = 0;
	table[Ba].evolves[3] = 0;
	table[Ba].evolves[4] = 0;
	table[Ba].evolves[5] = 0;

	// La "11131" -> Ba
	table[La].length = 5;
	table[La].evolves[0] = Ba;
	table[La].evolves[1] = 0;
	table[La].evolves[2] = 0;
	table[La].evolves[3] = 0;
	table[La].evolves[4] = 0;
	table[La].evolves[5] = 0;

	// Ce "1321133112" -> La H Ca Co
	table[Ce].length = 10;
	table[Ce].evolves[0] = La;
	table[Ce].evolves[1] = H;
	table[Ce].evolves[2] = Ca;
	table[Ce].evolves[3] = Co;
	table[Ce].evolves[4] = 0;
	table[Ce].evolves[5] = 0;

	// Pr "31131112" -> Ce
	table[Pr].length = 8;
	table[Pr].evolves[0] = Ce;
	table[Pr].evolves[1] = 0;
	table[Pr].evolves[2] = 0;
	table[Pr].evolves[3] = 0;
	table[Pr].evolves[4] = 0;
	table[Pr].evolves[5] = 0;

	// Nd "111312" -> Pr
	table[Nd].length = 6;
	table[Nd].evolves[0] = Pr;
	table[Nd].evolves[1] = 0;
	table[Nd].evolves[2] = 0;
	table[Nd].evolves[3] = 0;
	table[Nd].evolves[4] = 0;
	table[Nd].evolves[5] = 0;

	// Pm "132" -> Nd
	table[Pm].length = 3;
	table[Pm].evolves[0] = Nd;
	table[Pm].evolves[1] = 0;
	table[Pm].evolves[2] = 0;
	table[Pm].evolves[3] = 0;
	table[Pm].evolves[4] = 0;
	table[Pm].evolves[5] = 0;

	// Sm "311332" -> Pm Ca Zn
	table[Sm].length = 6;
	table[Sm].evolves[0] = Pm;
	table[Sm].evolves[1] = Ca;
	table[Sm].evolves[2] = Zn;
	table[Sm].evolves[3] = 0;
	table[Sm].evolves[4] = 0;
	table[Sm].evolves[5] = 0;

	// Eu "1113222" -> Sm
	table[Eu].length = 7;
	table[Eu].evolves[0] = Sm;
	table[Eu].evolves[1] = 0;
	table[Eu].evolves[2] = 0;
	table[Eu].evolves[3] = 0;
	table[Eu].evolves[4] = 0;
	table[Eu].evolves[5] = 0;

	// Gd "13221133112" -> Eu Ca Co
	table[Gd].length = 11;
	table[Gd].evolves[0] = Eu;
	table[Gd].evolves[1] = Ca;
	table[Gd].evolves[2] = Co;
	table[Gd].evolves[3] = 0;
	table[Gd].evolves[4] = 0;
	table[Gd].evolves[5] = 0;

	// Tb "3113112221131112" -> Ho Gd
	table[Tb].length = 16;
	table[Tb].evolves[0] = Ho;
	table[Tb].evolves[1] = Gd;
	table[Tb].evolves[2] = 0;
	table[Tb].evolves[3] = 0;
	table[Tb].evolves[4] = 0;
	table[Tb].evolves[5] = 0;

	// Dy "111312211312" -> Tb
	table[Dy].length = 12;
	table[Dy].evolves[0] = Tb;
	table[Dy].evolves[1] = 0;
	table[Dy].evolves[2] = 0;
	table[Dy].evolves[3] = 0;
	table[Dy].evolves[4] = 0;
	table[Dy].evolves[5] = 0;

	// Ho "1321132" -> Dy
	table[Ho].length = 7;
	table[Ho].evolves[0] = Dy;
	table[Ho].evolves[1] = 0;
	table[Ho].evolves[2] = 0;
	table[Ho].evolves[3] = 0;
	table[Ho].evolves[4] = 0;
	table[Ho].evolves[5] = 0;

	// Er "311311222" -> Ho Pm
	table[Er].length = 9;
	table[Er].evolves[0] = Ho;
	table[Er].evolves[1] = Pm;
	table[Er].evolves[2] = 0;
	table[Er].evolves[3] = 0;
	table[Er].evolves[4] = 0;
	table[Er].evolves[5] = 0;

	// Tm "11131221133112" -> Er Ca Co
	table[Tm].length = 14;
	table[Tm].evolves[0] = Er;
	table[Tm].evolves[1] = Ca;
	table[Tm].evolves[2] = Co;
	table[Tm].evolves[3] = 0;
	table[Tm].evolves[4] = 0;
	table[Tm].evolves[5] = 0;

	// Yb "1321131112" -> Tm
	table[Yb].length = 10;
	table[Yb].evolves[0] = Tm;
	table[Yb].evolves[1] = 0;
	table[Yb].evolves[2] = 0;
	table[Yb].evolves[3] = 0;
	table[Yb].evolves[4] = 0;
	table[Yb].evolves[5] = 0;
	
	// Lu "311312" -> Yb
	table[Lu].length = 6;
	table[Lu].evolves[0] = Yb;
	table[Lu].evolves[1] = 0;
	table[Lu].evolves[2] = 0;
	table[Lu].evolves[3] = 0;
	table[Lu].evolves[4] = 0;
	table[Lu].evolves[5] = 0;
	
	// Hf "11132" -> Lu
	table[Hf].length = 5;
	table[Hf].evolves[0] = Lu;
	table[Hf].evolves[1] = 0;
	table[Hf].evolves[2] = 0;
	table[Hf].evolves[3] = 0;
	table[Hf].evolves[4] = 0;
	table[Hf].evolves[5] = 0;
	
	// Ta "13112221133211322112211213322113" -> Hf Pa H Ca W
	table[Ta].length = 32;
	table[Ta].evolves[0] = Hf;
	table[Ta].evolves[1] = Pa;
	table[Ta].evolves[2] = H;
	table[Ta].evolves[3] = Ca;
	table[Ta].evolves[4] = W;
	table[Ta].evolves[5] = 0;
	
	// W "312211322212221121123222113" -> Ta
	table[W].length = 27;
	table[W].evolves[0] = Ta;
	table[W].evolves[1] = 0;
	table[W].evolves[2] = 0;
	table[W].evolves[3] = 0;
	table[W].evolves[4] = 0;
	table[W].evolves[5] = 0;
	
	// Re "111312211312113221133211322112211213322113" -> Ge Ca W
	table[Re].length = 42;
	table[Re].evolves[0] = Ge;
	table[Re].evolves[1] = Ca;
	table[Re].evolves[2] = W;
	table[Re].evolves[3] = 0;
	table[Re].evolves[4] = 0;
	table[Re].evolves[5] = 0;
	
	// Os "1321132122211322212221121123222113" -> Re
	table[Os].length = 34;
	table[Os].evolves[0] = Re;
	table[Os].evolves[1] = 0;
	table[Os].evolves[2] = 0;
	table[Os].evolves[3] = 0;
	table[Os].evolves[4] = 0;
	table[Os].evolves[5] = 0;

	// Ir "3113112211322112211213322113" -> Os
	table[Ir].length = 28;
	table[Ir].evolves[0] = Os;
	table[Ir].evolves[1] = 0;
	table[Ir].evolves[2] = 0;
	table[Ir].evolves[3] = 0;
	table[Ir].evolves[4] = 0;
	table[Ir].evolves[5] = 0;

	// Pt "111312212221121123222113" -> Ir
	table[Pt].length = 24;
	table[Pt].evolves[0] = Ir;
	table[Pt].evolves[1] = 0;
	table[Pt].evolves[2] = 0;
	table[Pt].evolves[3] = 0;
	table[Pt].evolves[4] = 0;
	table[Pt].evolves[5] = 0;

	// Au "132112211213322113" -> Pt
	table[Au].length = 18;
	table[Au].evolves[0] = Pt;
	table[Au].evolves[1] = 0;
	table[Au].evolves[2] = 0;
	table[Au].evolves[3] = 0;
	table[Au].evolves[4] = 0;
	table[Au].evolves[5] = 0;

	// Hg "31121123222113" -> Au
	table[Hg].length = 14;
	table[Hg].evolves[0] = Au;
	table[Hg].evolves[1] = 0;
	table[Hg].evolves[2] = 0;
	table[Hg].evolves[3] = 0;
	table[Hg].evolves[4] = 0;
	table[Hg].evolves[5] = 0;

	// Tl "111213322113" -> Hg
	table[Tl].length = 12;
	table[Tl].evolves[0] = Hg;
	table[Tl].evolves[1] = 0;
	table[Tl].evolves[2] = 0;
	table[Tl].evolves[3] = 0;
	table[Tl].evolves[4] = 0;
	table[Tl].evolves[5] = 0;

	// Pb "123222113" -> Tl
	table[Pb].length = 9;
	table[Pb].evolves[0] = Tl;
	table[Pb].evolves[1] = 0;
	table[Pb].evolves[2] = 0;
	table[Pb].evolves[3] = 0;
	table[Pb].evolves[4] = 0;
	table[Pb].evolves[5] = 0;

	// Bi "3113322113" -> Pm Pb
	table[Bi].length = 10;
	table[Bi].evolves[0] = Pm;
	table[Bi].evolves[1] = Pb;
	table[Bi].evolves[2] = 0;
	table[Bi].evolves[3] = 0;
	table[Bi].evolves[4] = 0;
	table[Bi].evolves[5] = 0;

	// Po "1113222113" -> Bi
	table[Po].length = 10;
	table[Po].evolves[0] = Bi;
	table[Po].evolves[1] = 0;
	table[Po].evolves[2] = 0;
	table[Po].evolves[3] = 0;
	table[Po].evolves[4] = 0;
	table[Po].evolves[5] = 0;

	// At "1322113" -> Po
	table[At].length = 7;
	table[At].evolves[0] = Po;
	table[At].evolves[1] = 0;
	table[At].evolves[2] = 0;
	table[At].evolves[3] = 0;
	table[At].evolves[4] = 0;
	table[At].evolves[5] = 0;

	// Rn "311311222113" -> Ho At
	table[Rn].length = 12;
	table[Rn].evolves[0] = Ho;
	table[Rn].evolves[1] = At;
	table[Rn].evolves[2] = 0;
	table[Rn].evolves[3] = 0;
	table[Rn].evolves[4] = 0;
	table[Rn].evolves[5] = 0;

	// Fr "1113122113" -> Rn
	table[Fr].length = 10;
	table[Fr].evolves[0] = Rn;
	table[Fr].evolves[1] = 0;
	table[Fr].evolves[2] = 0;
	table[Fr].evolves[3] = 0;
	table[Fr].evolves[4] = 0;
	table[Fr].evolves[5] = 0;

	// Ra "132113" -> Fr
	table[Ra].length = 6;
	table[Ra].evolves[0] = Fr;
	table[Ra].evolves[1] = 0;
	table[Ra].evolves[2] = 0;
	table[Ra].evolves[3] = 0;
	table[Ra].evolves[4] = 0;
	table[Ra].evolves[5] = 0;

	// Ac "3113" -> Ra
	table[Ac].length = 4;
	table[Ac].evolves[0] = Ra;
	table[Ac].evolves[1] = 0;
	table[Ac].evolves[2] = 0;
	table[Ac].evolves[3] = 0;
	table[Ac].evolves[4] = 0;
	table[Ac].evolves[5] = 0;

	// Th "1113" -> Ac
	table[Th].length = 4;
	table[Th].evolves[0] = Ac;
	table[Th].evolves[1] = 0;
	table[Th].evolves[2] = 0;
	table[Th].evolves[3] = 0;
	table[Th].evolves[4] = 0;
	table[Th].evolves[5] = 0;

	// Pa "13" -> Th
	table[Pa].length = 2;
	table[Pa].evolves[0] = Th;
	table[Pa].evolves[1] = 0;
	table[Pa].evolves[2] = 0;
	table[Pa].evolves[3] = 0;
	table[Pa].evolves[4] = 0;
	table[Pa].evolves[5] = 0;

	// U "3" -> Pa
	table[U].length = 1;
	table[U].evolves[0] = Pa;
	table[U].evolves[1] = 0;
	table[U].evolves[2] = 0;
	table[U].evolves[3] = 0;
	table[U].evolves[4] = 0;
	table[U].evolves[5] = 0;

}
