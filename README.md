# CSS-Parser / Procesor CSS


Celem zadania jest napisanie prostego silnika przetwarzającego CSS-y. W ramach zadania należy wczytać ze standardowego wejścia sekcje CSS przeplatane sekcjami komend. Sekcje CSS należy sparsować i umieścić w odpowiednich strukturach, sekcje komend należy sparsować i wykonać wypisując na standardowe wyjście ew. rezultaty (po ==).

=================================================================

CSS

Przetwarzanie rozpoczyna się wczytania deklaracji CSS. CSS jest syntaktycznie poprawny i składa się bloku atrybutów ew. poprzedzonych selektorami. Brak selektorów jest legalny (oznaczałby atrybuty aplikowane do wszystkiego).
Selektory (selectors) są separowane przecinkami. Dopuszczalne są selektory legalne dla CSS, ale można założyć, że nie zawierają znaków przecinka ani nawiasów klamrowych.
Blok atrybutów ujęty jest w nawiasy klamrowe.
Atrybuty są oddzielone średnikami i składają się z nazwy (property) i wartości (value) oddzielonych dwukropkiem. Po ostatnim atrybucie w bloku może, ale nie musi nastąpić średnik.
Jako wartości atrybutów mogą występować legalne dla CSS konstrukcje, jednak dla uproszczenia można bezpiecznie założyć, że ew. napisy nie są złośliwe tj. nie zawierają escapowanych znaków cudzysłowu, nawiasów klamrowych lub średników.
Jeśli konkretny atrybut (nazwa) w bloku występuje więcej niż raz należy potraktować to jako jedno wystąpienie, przy czym znacząca jest ostatnia wartość).
Zarówno selektory, nazwy atrybutów jak i wartości atrybutów nie wymagają interpretacji semantycznej tj. traktujemy je (po odrzuceniu skrajnych białych znaków, jako wartość. Tj. np.: 'margin-left : 8px', 'margin: 4px 7px 4px 7px' traktujemy jako oddzielne, niezwiązane atrybuty o nazwach odpowiednio 'margin-left' i 'margin' i wartościach '8px' oraz '4px 7px 4px 7px' Podobnie, selektory są traktowane jako wartość i nie wymagają interpretacji tj. np.: 'h1' i 'h1.theme' traktujemy jako oddzielne, niepowiązane selektory.
Uproszczenie: CSS nie zawiera komentarzy, ani selektorów typu @, bloki nie mogą się zagnieżdżać.
Dla potrzeb testów można założyć, że żaden selektor ani atrybut nie jest podzielony na kilka linii (ciągle w jednej linii może być kilka separatorów/ i lub atrybutów).

=================================================================


Komendy


W poniższych komendach i oraz j to dodatnie liczby całkowite (mieszczą się w int), natomiast n to legalna nazwa atrybutu. ???? – początek sekcji komend;

**** - wznów czytanie CSS;

? – wypisz liczbę bloków CSS;

i,S,? – wypisz liczbę selektorów dla bloku nr i (numery zaczynają się od 1), jeśli nie ma takiego bloku pomiń;

i,A,? - wypisz liczbę atrybutów dla bloku nr i, jeśli nie ma takiego bloku lub bloku pomiń;

i,S,j – wypisz j-ty selector dla i-tego bloku (numery bloków oraz atrybutów zaczynają się od 1) jeśli nie ma bloku lub selektora pomiń;

i,A,n – wypisz dla i-tego bloku wartość atrybutu o nazwie n, jeśli nie ma takiego pomiń;

n,A,? – wypisz łączną (dla wszystkich bloków) liczbę wystąpień atrybutu nazwie n. (W ramach pojedynczego bloku duplikaty powinny zostać usunięte na etapie wczytywania). Możliwe jest 0;

z,S,? – wypisz łączną (dla wszystkich bloków) liczbę wystąpień selektora z. Możliwe jest 0;

z,E,n – wypisz wartość atrybutu o nazwie n dla selektora z, w przypadku wielu wystąpień selektora z bierzemy ostatnie. W przypadku braku pomiń;

i,D,* - usuń cały blok nr i (tj. separatory+atrybuty), po poprawnym wykonaniu wypisz deleted;

i,D,n – usuń z i-tego bloku atrybut o nazwie n, jeśli w wyniku operacji pozostaje pusty blok powinien zostać również usunięty (wraz z ew. selektorami), po poprawnym wykonaniu wypisz deleted.

=================================================================


Uwagi implementacyjne

Selektory oraz atrybuty powinny być przechowywane jako listy. Poszczególne bloki CSS powinny być zorganizowane jako lista dwustronna (aby efektywnie realizować komendę E – ostatnie wystąpienie atrybutu). Aby lepiej wykorzystać pamięć lista powinna obejmować tablicę T=8 struktur reprezentujących blok (gdzie T jest stałą możliwą do zmiany w czasie kompilacji) oraz licznik zajętych aktualnie struktur (z uwagi na ew. kasowanie elementów). Liczniki warto wykorzystać dla przyśpieszenia operacji parametryzowanych numerem komórki tj. i.

Przy alokowaniu nowego węzła tworzona jest tablica T elementowa. Przy dodawaniu elementów, o ile jest wolne miejsce w węźle listy, należy je wykorzystać zanim alokowane zostaną nowe węzły. Jeżeli w przypadku usuwania elementów pozostanie pusta tablica należy węzeł usunąć. Nie trzeba przesuwać elementów miedzy węzłami, łączyć węzłów itd.


=================================================================



The aim of the task is to write a simple CSS processing engine. The task is to load CSS sections interspersed with command sections from the standard input. The CSS sections should be parsed and placed in appropriate structures, the command sections should be parsed and executed by writing out the results (after ==) to the standard output.

=================================================================

CSS

The processing starts with loading the CSS declaration. CSS is syntactically correct and consists of a block of attributes possibly preceded by selectors. The absence of selectors is legal (it would mean attributes applied to everything).
Selectors are separated by commas. CSS-legal selectors are allowed, but it can be assumed that they do not contain comma characters or curly brackets.
The attribute block is enclosed in curly brackets.
Attributes are separated by semicolons and consist of a name (property) and a value (value) separated by a colon. The last attribute in the block may or may not be followed by a semicolon.
There may be CSS-legal constructs as attribute values, but for simplicity's sake it is safe to assume that any subtitles are not malicious, i.e. do not contain escaped inverted commas, curly brackets or semicolons.
If a particular attribute (name) in a block occurs more than once it should be treated as one occurrence, with the last value being significant).
Both selectors, attribute names and attribute values do not require semantic interpretation, i.e. we treat them (after discarding extreme whitespace characters, as a value. I.e. e.g.: 'margin-left : 8px', 'margin: 4px 7px 4px 7px' are treated as separate, unrelated attributes with names 'margin-left' and 'margin' and values '8px' and '4px 7px 4px 7px' respectively Similarly, selectors are treated as a value and do not require interpretation i.e. e.g..: 'h1' and 'h1.theme' are treated as separate, unrelated selectors.
Simplification: CSS does not contain comments or selectors of type @, blocks cannot be nested.
For testing purposes, it can be assumed that no selector or attribute is split over several lines (there can still be several separators/and or attributes on one line).

=================================================================


Commands


In the following commands, i and j are positive integers (they fit into int), while n is the legal name of the attribute. ???? - beginning of the commands section;

**** - resume reading CSS;

? - print the number of CSS blocks;

i,S,? - print the number of selectors for block number i (numbers start with 1), if there is no such block skip;

i,A,? - print the number of attributes for block i, if there is no such block or block skip;

i,S,j - output the j-th selector for the i-th block (block and attribute numbers start with 1) if there is no such block or selector skip;

i,A,n - output for the i-th block the value of the attribute named n, if there is no such skip;

n,A,? - print the total (for all blocks) number of occurrences of the attribute named n. (Within a single block, duplicates should be removed at the loading stage). 0 is possible;

z,S,? - print the total (for all blocks) number of occurrences of the selector z. 0 is possible;

z,E,n - print the value of the attribute named n for selector z, in case of multiple occurrences of selector z we take the last one. If none, skip;

i,D,* - delete the whole block i (i.e. separators+attributes), when done correctly write out deleted;

i,D,n - remove the attribute named n from the i-th block, if the operation leaves the block empty it should also be removed (along with any selectors), when done correctly write deleted.

=================================================================


Implementation notes

Selectors and attributes should be stored as lists. Individual CSS blocks should be organised as a two-sided list (to effectively implement the E command - last occurrence of an attribute). To make better use of memory, the list should include an array of T=8 structures representing the block (where T is a compile-time constant) and a counter of currently occupied structures (due to possible deletion of elements). It is useful to use counters to speed up operations parameterised by the cell number, i.e. i.

When allocating a new node, a T element array is created. When adding elements, as long as there is free space in the list node, it should be used before new nodes are allocated. When deleting elements, if an empty array remains, the node must be deleted. There is no need to move elements between nodes, merge nodes, etc.
 
