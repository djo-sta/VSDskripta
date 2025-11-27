UPUTSTVO ZA INSTALIRANJE PROGRAMA glasacka_kutija:

Potrudio sam se da program napravim tako da mogu filozofi da ga koriste i fonovci da mu čitaju kod. Sve 
je spakovano u jedan fajl kako bi se olakšalo manje stručnim kolegama.

- Kako biste pokrenuli program, prvo morate kompajlovati kod (preporučujem g++ kompajler). Kako biste
proverili da li je g++ već instaliran otvorite ComandPrompt ili Powershell na Windows sistemima ili u
terminalu na Linux i MacOS sistemima i ukucajte: 

g++ --version

Ukoliko nije instaliran ispisaće grešku, a vi potražite na internetu kako se g++ instalira.
Ako jeste instaliran, otvorite odabrani terminal emulator i prebacite se u folder u kojem se nalazi
glasacka_kutija.cpp i ukucajte: 

g++ glasacka_kutija.cpp -o glasacka_kutija

Nakon što ste uneli ovu liniju u folderu će nastati novi fajl (na Windows je glasacka_kutija.exe, a na
Linux i MacOS je glasacka_kutija ili glasacka_kutija.out). Pokrenite taj novi fajl. Ako se otvorio terminal
na kom piše Почетни мени i lista opcija koje se mogu odabrati, čestitam! Uspeli ste da kompajlujete c++ kod!
Ako niste dobili očekivani rezultat, pokušajte da pokrenete kao administrator, a ako ni to ne pomaže pitajte
ChatGPT :)


UPUTSTVO ZA KORIŠĆENJE PROGRAMA glasacka_kutija:

- Fajlovi za uspešan rad programa:

	Obavezni:
		1) spisak.txt je fajl u kome se nalazi spisak svih članica VSDa. Sintaksa je sledeća: prve 52
		   linije su puna imena všu, narednih 52 njihove latinične skraćenice i poslednjih 52 ćirilične
		   skraćenice.
	Poželjni:
		1) glasoviddmm.txt je fajl u kojem se cuvaju sve informacije sa jedne sednice potrebne za obradu
		   podataka. Sintaksa ovog fajla je objašnjena u delu 1. Učitavanje prošlog fajla. Program može
		   da funkcioniše i bez ovog fajla, ali su onemogućene opcije 4 i 6 na početnom meniju.
		2) labeleddmm.txt je fajl u kojem se cuvaju nazivi tačaka koje se glasaju tog dana. Tačke treba
		   da budu ispisane respektivno po pravilu jedan red - jedna tačka. Program će raditi i bez ovog
		   fajla, ali će prilikom ispisa umesto imena tačke samo napisati njen redni broj.
	Nepotrebni:
		1) rezultati_glasanjaddmm.txt je našminkani fajl koji je napravljen da se u svojoj celosti samo
		   prekopira u izveštaj/zapisnik sa sednice. Program ne čita ovaj fajl.

POSTARATI SE DA SE OBAVEZNI I POŽELJNI FAJLOVI NALAZE U ISTOM FOLDERU GDE JE I PROGRAM
jer u suprotnom neće biti moguće njihovo čitanje.


- Početni meni:

Prilikom ulaska u program (susrećete se sa početnim menijem u kojem se bira jedna od operacija koja 
izvršava određenu funkciju dnevnog reda. Validni unos su cifre od 0 do 6, bilo kakav drugi unos dovodi do 
ispisa greške i ponovnog unosa. Opcije su poređane tako da bi idealno bilo da ih radite po redu.

1. Učitavanje prošlog glasanja:

U ovom delu se radi učitavanje fajla koji čuva vrednosti potrebne za operacije 4 i 6. Ime fajla koji se 
učitava je: glasoviddmm.txt, gde dd označava dan, a mm mesec održanog sastanka za koji želimo da 
obrađujemo podatke (najčešće će to biti datum poslednjeg održanog VSDa). Sintaksa kojom je ispisan fajl je 
sledeća: prva 3 reda su prisutnost na poslednja 3 održana sastanka (od kasnijeg ka skorijem), 4. red je 
niz rezultata glasanja, narednih 52 reda su glasovi pojedinačnih všu na tom sastanku i na kraju su 
ispisani nazivi tačaka koje su se glasale. Ukoliko se ova sintaksa ne poštuje, program neće funkcionisati 
kako treba. Ako navedeni fajl ne postoji biće ispisano: "Fajl nije pronadjen", ako jeste biće ispisano:
"Fajl uspesno ucitan".

2. Prisutnost:

U ovom delu se radi početna prisutnost delegata všu. Ukoliko je delegat određene všu prisutan: uneti 1,
ukoliko neko prenosi glas te všu: uneti 2, i ako nije tu i niko ne prenosi njihov glas: uneti 0. Ako dođe
do greške prilikom unosa, postoji opcija izmene u koju se ulazi unošenjem "izmeni" umesto 0, 1 ili 2,
nakon čega se traži šifra (skraćenica na okrnjenoj latinici) všu kojoj je pogrešno unet status prisutnosti i pitanje koji je 
novi status prisutnosti. Posle unošenja oba podatka se program vraća u petlju i nastavlja tamo gde je bio
pre unosa "izmeni". Pored izmene postoji i specijalni ulaz za napuštanje petlje unošenjem "izlaz" koji se
koristi ako ste greškom ušli u ovu operaciju tako što vas vraća na početni meni. Ako se neka všu pojavi
nakon završenog početnog unosa, nema potrebe pokretati petlju ispočetka jer postoji opcija 3 na početnom
meniju. Svi unosi pored 0, 1, 2, "izmeni" i "izlaz" dovode do ispisivanja greške.

3. Izmena prisutnosti

U ovom delu se menja prisutnost všu kojoj se promenio status prisutnosti od kako je odrađena početna
prisutnost. Nakon izbora opcije će se tražiti šifra všu kojoj se menja status prisutnosti i zatim novi
status prisutnosti (0, 1 ili 2). Ukoliko se makar jedan od ova dva unosa pogršno odradi, program će 
ispisati grešku, vratiće se na početni meni i neće biti unete izmene. Ukoliko su oba odrađena kako treba
ispisaće se "Izmena je odrađena uspesno" i program će se vratiti na početni meni. Obratiti pažnju prilikom
unosa šifre za Šumarski fakultet čija je skracenica SHF jer je SF već zauzeto od strane Saobraćajnog
fakulteta.

4. Potvrda/izmena glasova

Ova opcija nije moguća ako opcija 1 nije uspešno odrađena. U ovom delu se radi potvrđivanje glasova koji
su bili prenešeni od strane delegata druge všu na poslednjoj sednici. Program će prvo ispisati sve všu
čiji je glas prenešen i zatim pitati da li je svaka od njih pojedinačno prisutna. Ukoliko jeste, 
treba uneti 1 kako bi svi glasovi ostali isti i prisutnost na prošlom vsd se promenila sa 2 na 1. Ako všu 
nije tu ili nepotvrđuje glasove iz bilo kog drugog razloga, treba uneti 0 kako bi se svi glasovi sa prošle
sednice promenili na 3 i prisutnost na 0. Kada se prođe kroz sve všu koje treba da potvrde glas, biće
postavljeno pitanje da li neko menja glas sa prošle sednice? Ukoliko je odgovor da: uneti 1, ako je
odgovor ne: uneti 0. Ukoliko postoji potreba za menjanjem glasova, uneti šifru všu kojoj se menja glas
nakon čega će biti ispisan niz glasova od prošle sednice. Sada treba uneti sve glasove sa izmenom.
Ukoliko unešena všu nije prisutna, biće ispisano "vsu nije prisutna", a ako se neki od unosa pogreši,
biće ispisana greška. Nakon ispisane greške ili uspešno odrađene izmene će se ponovo postaviti pitanje
da li postoji všu koja menja glas. Nakon završetka potvrđivanja i izmene glasova će se ispisati novi
rezultati glasanja i izmeniće se izlazni fajlovi rezultati_glasanjaddmm.txt i glasoviddmm.txt. Ukoliko
ni jedna všu ne mora da potvrdi glas i niko ne menja glas o prošle sednice, neće biti ponovne obrade i
ispisa.

5. Glasanje

U ovom delu se radi unos, obrada i ispis novih glasova. Ako je opcija 1 odrađena uspešno, kvorum će biti
izračunat automatski, ali ako nije, biće zatraženo da se kvorum unese ručno. Sledeći korak je unošenje
broja tačaka za glasanje gde su validne vrednosti brojevi između 1 i 27, bilo šta drugo će da ispiše 
grešku i zatraži ponovni unos. Nakon ovoga kreće unos glasova pojedinačnih všu. Glasovi su cifre
0 (uzdržani), 1 (za), 2(protiv) i 3(neizjašnjen). Sve glasove treba ispisati odjednom bez razmaka. Ako
broj unetih cifara ne odgovara malo pre unetom broju glasova, biće ispisana greška i zatražiće se 
ponovni upis za tu všu. Fakultetima koji nisu prisutni na sednici se automatski pišu sve trojke i neće
biti moguće uneti im išta drugo. U ovom delu programa takođe postoje opcije izmene i izlaza koje su 
objašnjene u delu 2. Prisutnost. Nakon završetka unosa će biti ispisan rezultat obrade podataka za svako 
pojedinačno glasanje i biće napravljeni/izmenjeni fajlovi glasoviddmm.txt i rezultat_glasanjaddmm.txt gde 
ddmm predstavlja datum održavanja sednice. Za razliku od prisutnosti, glasovi sa ove sednice se ne mogu 
menjati automatski nakon završetka zato molim pajtonaša (ili kako god se zove ta funkcija sada) da 
proveri sa svima da li su lepo izdiktirali glasove pre nego što unese poslednji glas. Nakon ispisa se
program vraća na početni meni.

6. Doglašavanje

Ova opcija nije moguća ako opcija 1 nije uspešno odrađena. U ovom delu se radi doglašavanje predloga sa
prošle sednice koji nisu skupili kvorum za donošenje odluke. Tačke će ići jedna po jedna i prvo će biti
ispisane sve všu koje nisu donele glas za tu tačku, zatim će se zatražiti unos šifre všu koja jeste
donela glas, zatim glas i onda da li postoji još všu koje su donele glas. Na sledeću tačku se prelazi kada
se na poslednje pitanje odgovori sa 0. Kada se prođu sve tačke odradiće se obrada i ispis tih tačaka.
Ukoliko ne postoje tačke za doglašavanje, program će se samo vratiti na početni meni. Bilo kakav nevalidan
unos će dovesti do ispisa greške i pitanja da li još neka všu donosi glas za ovu tačku.

0. Izlaz

Ova opcija zatvara program. Ne radi nikakvu obradu ili ispis tako da je isto kao da kliknete na X da 
zatvorite prozor.




- fajlovi koji su produkt ovog programa su glasoviddmm.txt, rezultati_glasanjaddmm.txt, 
glasacka_kutija.exe, glasacka_kutija.out, glasacka_kutija.cpp. Bilo koji drugi fajl koji se nađe u ovom 
folderu je unet od strane drugih korisnika i nije potekao od programa glasacka_kutija.



Nadam se da sam objasnio sve :)

Za bilo kakva pitanja se obratiti Đurađu sa ETFa.
