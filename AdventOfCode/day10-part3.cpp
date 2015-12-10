#include <iostream>

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

void init_table(struct table[ELEMENTS]);

int main()
{
	// We make a table of 93 to keep the numbering
	// consistant with the table
	element table[ELEMENTS];

	init_table(table);

	return 0;
}

/*
 * We hard code Conway's table and relationships
 * From: http://www.se16.info/js/lands2.htm
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
	table[29].length = 6;
	table[29].evolves[0] = 28;
	table[29].evolves[1] = 0;
	table[29].evolves[2] = 0;
	table[29].evolves[3] = 0;
	table[29].evolves[4] = 0;
	table[29].evolves[5] = 0;
	
	// Zn "312" -> Cu
	table[30].length = 3;
	table[30].evolves[0] = 29;
	table[30].evolves[1] = 0;
	table[30].evolves[2] = 0;
	table[30].evolves[3] = 0;
	table[30].evolves[4] = 0;
	table[30].evolves[5] = 0;

	// Ga "13221133122211332" -> Eu Ca Ac H Ca Zn
	table[31].length = 17;
	table[31].evolves[0] = 63;
	table[31].evolves[1] = 20;
	table[31].evolves[2] = 89;
	table[31].evolves[3] = 1;
	table[31].evolves[4] = 20;
	table[31].evolves[5] = 30;

	// Ge "31131122211311122113222" -> Ho Ga
	table[32].length = 23;
	table[32].evolves[0] = 67;
	table[32].evolves[1] = 31]
	table[32].evolves[2] = 0;
	table[32].evolves[3] = 0;
	table[32].evolves[4] = 0;
	table[32].evolves[5] = 0;

	// As "11131221131211322113322112" -> Ge Na
	table[33].length = 26;
	table[33].evolves[0] = 32;
	table[33].evolves[1] = 11;
	table[33].evolves[2] = 0;
	table[33].evolves[3] = 0;
	table[33].evolves[4] = 0;
	table[33].evolves[5] = 0;

	// Se "13211321222113222112" -> As
	table[34].length = 20;
	table[34].evolves[0] = 33;
	table[34].evolves[1] = 0;
	table[34].evolves[2] = 0;
	table[34].evolves[3] = 0;
	table[34].evolves[4] = 0;
	table[34].evolves[5] = 0;

	// Br "3113112211322112" -> Se
	table[35].length = 16;
	table[35].evolves[0] = 34;
	table[35].evolves[1] = 0;
	table[35].evolves[2] = 0;
	table[35].evolves[3] = 0;
	table[35].evolves[4] = 0;
	table[35].evolves[5] = 0;

	// Kr "11131221222112" -> Br
	table[36].length = 14;
	table[36].evolves[0] = 35;
	table[36].evolves[1] = 0;
	table[36].evolves[2] = 0;
	table[36].evolves[3] = 0;
	table[36].evolves[4] = 0;
	table[36].evolves[5] = 0;

	// Rb "1321122112" -> Kr
	table[37].length = 10;
	table[37].evolves[0] = 36;
	table[37].evolves[1] = 0;
	table[37].evolves[2] = 0;
	table[37].evolves[3] = 0;
	table[37].evolves[4] = 0;
	table[37].evolves[5] = 0;

	// Sr "3112112" -> Rb
	table[38].length = 7;
	table[38].evolves[0] = 37;
	table[38].evolves[1] = 0;
	table[38].evolves[2] = 0;
	table[38].evolves[3] = 0;
	table[38].evolves[4] = 0;
	table[38].evolves[5] = 0;

	// Y "1112133" -> Sr U
	table[39].length = 7;
	table[39].evolves[0] = 38;
	table[39].evolves[1] = 92;
	table[39].evolves[2] = 0;
	table[39].evolves[3] = 0;
	table[39].evolves[4] = 0;
	table[39].evolves[5] = 0;

	// Zr "12322211331222113112211" -> Y H Ca Tc
	table[40].length = 23;
	table[40].evolves[0] = 39;
	table[40].evolves[1] = 1;
	table[40].evolves[2] = 20;
	table[40].evolves[3] = 43;
	table[40].evolves[4] = 0;
	table[40].evolves[5] = 0;

	// Nb "1113122113322113111221131221" -> Er Zr
	table[41].length = 28;
	table[41].evolves[0] = 68;
	table[41].evolves[1] = 40;
	table[41].evolves[2] = 0;
	table[41].evolves[3] = 0;
	table[41].evolves[4] = 0;
	table[41].evolves[5] = 0;

	// Mo "13211322211312113211" -> Nb
	table[42].length = 20;
	table[42].evolves[0] = 41;
	table[42].evolves[1] = 0;
	table[42].evolves[2] = 0;
	table[42].evolves[3] = 0;
	table[42].evolves[4] = 0;
	table[42].evolves[5] = 0;

	// Tc "311322113212221" -> Mo
	table[43].length = 15;
	table[43].evolves[0] = 42;
	table[43].evolves[1] = 0;
	table[43].evolves[2] = 0;
	table[43].evolves[3] = 0;
	table[43].evolves[4] = 0;
	table[43].evolves[5] = 0;

	// Ru "132211331222113112211" Eu Ca Tc
	table[44].length = 21;
	table[44].evolves[0] = 63;
	table[44].evolves[1] = 20;
	table[44].evolves[2] = 43;
	table[44].evolves[3] = 0;
	table[44].evolves[4] = 0;
	table[44].evolves[5] = 0;

	// Rh "311311222113111221131221" -> Ho Ru
	table[45].length = 24;
	table[45].evolves[0] = 67;;
	table[45].evolves[1] = 44;
	table[45].evolves[2] = 0;
	table[45].evolves[3] = 0;
	table[45].evolves[4] = 0;
	table[45].evolves[5] = 0;

	// Pd "111312211312113211" -> Rh
	table[46].length = 18;
	table[46].evolves[0] = 45;
	table[46].evolves[1] = 0;
	table[46].evolves[2] = 0;
	table[46].evolves[3] = 0;
	table[46].evolves[4] = 0;
	table[46].evolves[5] = 0;

	// Ag "132113212221" -> Pd
	table[47].length = 12;
	table[47].evolves[0] = 46;
	table[47].evolves[1] = 0;
	table[47].evolves[2] = 0;
	table[47].evolves[3] = 0;
	table[47].evolves[4] = 0;
	table[47].evolves[5] = 0;
	
	// Cd "3113112211" -> Ag
	table[48].length = 10;
	table[48].evolves[0] = 47;
	table[48].evolves[1] = 0;
	table[48].evolves[2] = 0;
	table[48].evolves[3] = 0;
	table[48].evolves[4] = 0;
	table[48].evolves[5] = 0;
	
	// In "11131221" -> Cd
	table[49].length = 8;
	table[49].evolves[0] = 48;
	table[49].evolves[1] = 0;
	table[49].evolves[2] = 0;
	table[49].evolves[3] = 0;
	table[49].evolves[4] = 0;
	table[49].evolves[5] = 0;
	
	// Sn "13211" -> In
	table[50].length = 5;
	table[50].evolves[0] = 49;
	table[50].evolves[1] = 0;
	table[50].evolves[2] = 0;
	table[50].evolves[3] = 0;
	table[50].evolves[4] = 0;
	table[50].evolves[5] = 0;
	
	// Sb "3112221" -> Pm Sn
	table[51].length = 7;
	table[51].evolves[0] = 61;
	table[51].evolves[1] = 50;
	table[51].evolves[2] = 0;
	table[51].evolves[3] = 0;
	table[51].evolves[4] = 0;
	table[51].evolves[5] = 0;
	
	// Te "1322113312211" -> Eu Ca Sb
	table[52].length = 13;
	table[52].evolves[0] = 63;
	table[52].evolves[1] = 20;
	table[52].evolves[2] = 51;
	table[52].evolves[3] = 0;
	table[52].evolves[4] = 0;
	table[52].evolves[5] = 0;
	
	// I "311311222113111221" -> Ho Te
	table[53].length = 18;
	table[53].evolves[0] = 67;
	table[53].evolves[1] = 52;
	table[53].evolves[2] = 0;
	table[53].evolves[3] = 0;
	table[53].evolves[4] = 0;
	table[53].evolves[5] = 0;

	// Xe "11131221131211" -> I
	table[54].length = 14;
	table[54].evolves[0] = 53;
	table[54].evolves[1] = 0;
	table[54].evolves[2] = 0;
	table[54].evolves[3] = 0;
	table[54].evolves[4] = 0;
	table[54].evolves[5] = 0;

	// Cs "13211321" -> Xe
	table[55].length = 8;
	table[55].evolves[0] = 54;
	table[55].evolves[1] = 0;
	table[55].evolves[2] = 0;
	table[55].evolves[3] = 0;
	table[55].evolves[4] = 0;
	table[55].evolves[5] = 0;

	// Ba "311311" -> Ca
	table[56].length = 6;
	table[56].evolves[0] = 55;
	table[56].evolves[1] = 0;
	table[56].evolves[2] = 0;
	table[56].evolves[3] = 0;
	table[56].evolves[4] = 0;
	table[56].evolves[5] = 0;

	// La "11131" -> Ba
	table[57].length = 5;
	table[57].evolves[0] = 56;
	table[57].evolves[1] = 0;
	table[57].evolves[2] = 0;
	table[57].evolves[3] = 0;
	table[57].evolves[4] = 0;
	table[57].evolves[5] = 0;

	// Ce "1321133112" -> La H Ca Co
	table[58].length = 10;
	table[58].evolves[0] = 57;
	table[58].evolves[1] = 1;
	table[58].evolves[2] = 20;
	table[58].evolves[3] = 27;
	table[58].evolves[4] = 0;
	table[58].evolves[5] = 0;

	// Pr "31131112" -> Ce
	table[59].length = 8;
	table[59].evolves[0] = 58;
	table[59].evolves[1] = 0;
	table[59].evolves[2] = 0;
	table[59].evolves[3] = 0;
	table[59].evolves[4] = 0;
	table[59].evolves[5] = 0;

	// Nd "111312" -> Pr
	table[60].length = 6;
	table[60].evolves[0] = 59;
	table[60].evolves[1] = 0;
	table[60].evolves[2] = 0;
	table[60].evolves[3] = 0;
	table[60].evolves[4] = 0;
	table[60].evolves[5] = 0;

	// Pm "132" -> Nd
	table[61].length = 3;
	table[61].evolves[0] = 60;
	table[61].evolves[1] = 0;
	table[61].evolves[2] = 0;
	table[61].evolves[3] = 0;
	table[61].evolves[4] = 0;
	table[61].evolves[5] = 0;

	// Sm "311332" -> Pm Ca Zn
	table[16].length = 6;
	table[16].evolves[0] = 61;
	table[16].evolves[1] = 20;
	table[16].evolves[2] = 30;
	table[16].evolves[3] = 0;
	table[16].evolves[4] = 0;
	table[16].evolves[5] = 0;

	// Cl "132112" -> S
	table[17].length = 6;
	table[17].evolves[0] = 16;
	table[17].evolves[1] = 0;
	table[17].evolves[2] = 0;
	table[17].evolves[3] = 0;
	table[17].evolves[4] = 0;
	table[17].evolves[5] = 0;

	// Ar "3112" -> Cl
	table[18].length = 4;
	table[18].evolves[0] = 17;
	table[18].evolves[1] = 0;
	table[18].evolves[2] = 0;
	table[18].evolves[3] = 0;
	table[18].evolves[4] = 0;
	table[18].evolves[5] = 0;

	// K "1112" -> Ar
	table[19].length = 4;
	table[19].evolves[0] = 18;
	table[19].evolves[1] = 0;
	table[19].evolves[2] = 0;
	table[19].evolves[3] = 0;
	table[19].evolves[4] = 0;
	table[19].evolves[5] = 0;

	// Ca "12" -> K
	table[20].length = 2;
	table[20].evolves[0] = 19;
	table[20].evolves[1] = 0;
	table[20].evolves[2] = 0;
	table[20].evolves[3] = 0;
	table[20].evolves[4] = 0;
	table[20].evolves[5] = 0;

	// Sc "3113112221133112" -> Ho Pa H Ca Co
	table[21].length = 16;
	table[21].evolves[0] = 67;
	table[21].evolves[1] = 91;
	table[21].evolves[2] = 1;
	table[21].evolves[3] = 20;
	table[21].evolves[4] = 27;
	table[21].evolves[5] = 0;

	// Ti "11131221131112" -> Sc
	table[22].length = 14;
	table[22].evolves[0] = 21;
	table[22].evolves[1] = 0;
	table[22].evolves[2] = 0;
	table[22].evolves[3] = 0;
	table[22].evolves[4] = 0;
	table[22].evolves[5] = 0;

	// V "13211312" -> Ti
	table[23].length = 8;
	table[23].evolves[0] = 22;
	table[23].evolves[1] = 0;
	table[23].evolves[2] = 0;
	table[23].evolves[3] = 0;
	table[23].evolves[4] = 0;
	table[23].evolves[5] = 0;

}	// H "22" -> H (does not evolve)
	table[1].length = 2;
	table[1].evolves[0] = 1;
	table[1].evolves[1] = 0;
	table[1].evolves[2] = 0;
	table[1].evolves[3] = 0;
	table[1].evolves[4] = 0;
	table[1].evolves[5] = 0;
	
	// He "13112221133211322112211213322112" -> Hf Pa H Ca Li
	table[2].length = 32;
	table[2].evolves[0] = 72;
	table[2].evolves[1] = 91;
	table[2].evolves[2] = 1;
	table[2].evolves[3] = 20;
	table[2].evolves[4] = 3;
	table[2].evolves[5] = 0;
	
	// Li "312211322212221121123222112" -> He
	table[3].length = 27;
	table[3].evolves[0] = 2;
	table[3].evolves[1] = 0;
	table[3].evolves[2] = 0;
	table[3].evolves[3] = 0;
	table[3].evolves[4] = 0;
	table[3].evolves[5] = 0;
	
	// Be "111312211312113221133211322112211213322112" -> Ge Ca Li
	table[4].length = 42;
	table[4].evolves[0] = 32;
	table[4].evolves[1] = 20;
	table[4].evolves[2] = 3;;
	table[4].evolves[3] = 0;
	table[4].evolves[4] = 0;
	table[4].evolves[5] = 0;
	
	// B "1321132122211322212221121123222112" -> Be
	table[5].length = 34;
	table[5].evolves[0] = 4;
	table[5].evolves[1] = 0;
	table[5].evolves[2] = 0;
	table[5].evolves[3] = 0;
	table[5].evolves[4] = 0;
	table[5].evolves[5] = 0;
	
	// C "3113112211322112211213322112" -> B
	table[6].length = 28;
	table[6].evolves[0] = 5;
	table[6].evolves[1] = 0;
	table[6].evolves[2] = 0;
	table[6].evolves[3] = 0;
	table[6].evolves[4] = 0;
	table[6].evolves[5] = 0;
	
	// N "111312212221121123222112" -> C
	table[7].length = 24;
	table[7].evolves[0] = 6;
	table[7].evolves[1] = 0;
	table[7].evolves[2] = 0;
	table[7].evolves[3] = 0;
	table[7].evolves[4] = 0;
	table[7].evolves[5] = 0;

	// O "132112211213322112" -> N
	table[8].length = 18;
	table[8].evolves[0] = 7;
	table[8].evolves[1] = 0;
	table[8].evolves[2] = 0;
	table[8].evolves[3] = 0;
	table[8].evolves[4] = 0;
	table[8].evolves[5] = 0;

	// F "31121123222112" -> O
	table[9].length = 14;
	table[9].evolves[0] = 8;
	table[9].evolves[1] = 0;
	table[9].evolves[2] = 0;
	table[9].evolves[3] = 0;
	table[9].evolves[4] = 0;
	table[9].evolves[5] = 0;

	// Ne "111213322112" -> F
	table[10].length = 12;
	table[10].evolves[0] = 9;
	table[10].evolves[1] = 0;
	table[10].evolves[2] = 0;
	table[10].evolves[3] = 0;
	table[10].evolves[4] = 0;
	table[10].evolves[5] = 0;

	// Na "123222112" -> Ne
	table[11].length = 9;
	table[11].evolves[0] = 10;
	table[11].evolves[1] = 0;
	table[11].evolves[2] = 0;
	table[11].evolves[3] = 0;
	table[11].evolves[4] = 0;
	table[11].evolves[5] = 0;

	// Mg "3113322112" -> Pm Na
	table[12].length = 10;
	table[12].evolves[0] = 61;
	table[12].evolves[1] = 11;
	table[12].evolves[2] = 0;
	table[12].evolves[3] = 0;
	table[12].evolves[4] = 0;
	table[12].evolves[5] = 0;

	// Al "1113222112" -> Mg
	table[13].length = 10;
	table[13].evolves[0] = 12;
	table[13].evolves[1] = 0;
	table[13].evolves[2] = 0;
	table[13].evolves[3] = 0;
	table[13].evolves[4] = 0;
	table[13].evolves[5] = 0;

	// Si "1322112" -> Al
	table[14].length = 7;
	table[14].evolves[0] = 13;
	table[14].evolves[1] = 0;
	table[14].evolves[2] = 0;
	table[14].evolves[3] = 0;
	table[14].evolves[4] = 0;
	table[14].evolves[5] = 0;

	// P "311311222112" -> Ho Si
	table[15].length = 12;
	table[15].evolves[0] = 67;
	table[15].evolves[1] = 14;
	table[15].evolves[2] = 0;
	table[15].evolves[3] = 0;
	table[15].evolves[4] = 0;
	table[15].evolves[5] = 0;

	// S "1113122112" -> P
	table[16].length = 10;
	table[16].evolves[0] = 15;
	table[16].evolves[1] = 0;
	table[16].evolves[2] = 0;
	table[16].evolves[3] = 0;
	table[16].evolves[4] = 0;
	table[16].evolves[5] = 0;

	// Cl "132112" -> S
	table[17].length = 6;
	table[17].evolves[0] = 16;
	table[17].evolves[1] = 0;
	table[17].evolves[2] = 0;
	table[17].evolves[3] = 0;
	table[17].evolves[4] = 0;
	table[17].evolves[5] = 0;

	// Ar "3112" -> Cl
	table[18].length = 4;
	table[18].evolves[0] = 17;
	table[18].evolves[1] = 0;
	table[18].evolves[2] = 0;
	table[18].evolves[3] = 0;
	table[18].evolves[4] = 0;
	table[18].evolves[5] = 0;

	// K "1112" -> Ar
	table[19].length = 4;
	table[19].evolves[0] = 18;
	table[19].evolves[1] = 0;
	table[19].evolves[2] = 0;
	table[19].evolves[3] = 0;
	table[19].evolves[4] = 0;
	table[19].evolves[5] = 0;

	// Ca "12" -> K
	table[20].length = 2;
	table[20].evolves[0] = 19;
	table[20].evolves[1] = 0;
	table[20].evolves[2] = 0;
	table[20].evolves[3] = 0;
	table[20].evolves[4] = 0;
	table[20].evolves[5] = 0;

	// Sc "3113112221133112" -> Ho Pa H Ca Co
	table[21].length = 16;
	table[21].evolves[0] = 67;
	table[21].evolves[1] = 91;
	table[21].evolves[2] = 1;
	table[21].evolves[3] = 20;
	table[21].evolves[4] = 27;
	table[21].evolves[5] = 0;

	// Ti "11131221131112" -> Sc
	table[22].length = 14;
	table[22].evolves[0] = 21;
	table[22].evolves[1] = 0;
	table[22].evolves[2] = 0;
	table[22].evolves[3] = 0;
	table[22].evolves[4] = 0;
	table[22].evolves[5] = 0;

	// V "13211312" -> Ti
	table[23].length = 8;
	table[23].evolves[0] = 22;
	table[23].evolves[1] = 0;
	table[23].evolves[2] = 0;
	table[23].evolves[3] = 0;
	table[23].evolves[4] = 0;
	table[23].evolves[5] = 0;

}
