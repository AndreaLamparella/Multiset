# ESAME DI PROGRAMMAZIONE C++

Il progetto richiede la progettazione e realizzazione di una classe che
implementa un **MultiSet ORDINATO** di elementi generici **T**. Un MultiSet è
come un insieme di dati che può contenere duplicati: es. S={1,4,4,4,7,10,12}.
Implementare il MultiSet in modo tale da minimizzare l’uso della memoria cioè
non dovete memorizzare i duplicati di un elemento. Facendo riferimento
all’esempio precedente, il '4' va memorizzato una sola volta sapendo però che
ci sono tre occorrenze di '4' in S.

A parte i metodi essenziali per la classe (tra cui conoscere il numero totale di
elementi, aggiunta/rimozione elementi, conteggio occorrenze di un elemento,
ecc...), devono essere implementate le seguenti funzionalità:

1. la costruzione di un **MultiSet** anche a partire da una sequenza di dati
    generici **Q** identificata da una coppia di iteratori generici. Questo
    costruttore prende in input: l’iteratore di inizio sequenza, l’iteratore di
    fine sequenza. Lasciate al compilatore la gestione della conversione di
    dati tra **Q** e **T**.
2. Un iteratore di sola lettura (scegliere la categoria). L’iteratore deve
    ritornare tutti gli elementi del MultiSet. Cioè, i duplicati vanno ritornati
    in numero corretto. Nel caso d’esempio di S, è la sequenza di valori
    tipo: 1 4 4 4 7 10 12

 3. Implementare l’operatore di confronto operator== tra due MultiSet
    che ritorna true sse i due MultiSet (dello stesso tipo) contengono gli
    stessi elementi con lo stesso numero di occorrenze dei duplicati.
 4. Implementate un metodo contains che, dato un elemento di tipo T,
    ritorna true se l'elemento esiste nel MultiSet.

 5. Implementare la funzione globale operator<< per inviare su
    std::ostream il contenuto del MultiSet nella forma:
    {<X1, occorrenzeX1>, <X2, occorrenzeX2>,...,<XN, occorrenzeXN>}

Tenete anche conto che:

- La rimozione completa di un elemento X avviene quando il numero di
    occorrenze di tale elemento diventa zero.
- Gli elementi del MultiSet sono immutabili. Una volta inseriti, non
    cambiano valore.
- Non è necessario considerare questioni di efficienza del codice (a parte il
    requisito sulla memoria).

Utilizzare dove opportuno la gestione delle eccezioni.

**Nota 1:** Se non indicato diversamente, nella progettazione della classe, e'
vietato l'uso di librerie esterne e strutture dati container della std library come
std::vector, std::list e simili. E’ consentito il loro uso nel codice di test nel
main.

**Nota 2** : A parte nullptr, non potete utilizzare altri costrutti C++11 e oltre.

**Nota 3:** Nella classe, è consentito l’uso della gerarchia di eccezioni standard,
delle asserzioni, la gerarchia degli stream e la funzione std::swap.

**Nota 4:** Per vostra sicurezza, tutti i metodi dell’interfaccia pubblica che
implementate devono essere esplicitamente testati nel main anche su tipi
custom.

**Nota 5:** Non dimenticate di usare Valgrind per testare problemi di memoria

**Nota 6:** Evitate di usare "test" come nome dell'eseguibile. Potrebbe dare dei
problemi sotto msys.

## Alcune note sulla valutazione del Progetto C++

- Se in seguito a dei test effettuati dai docenti in fase di valutazione (es.
chiamate a funzioni non testate da voi), il codice non compila, l’esame NON
è superato.
- Implementazione di codice non richiesto non dà punti aggiuntivi ma se non
corretto penalizza il voto finale.
- Gli errori riguardanti la gestione della memoria sono considerati GRAVI.
- La valutazione del progetto non dipende dalla quantità del codice scritto.
- NON usate funzionalità C di basso livello come memcpy, printf, FILE ecc...
Se c'e' una alternativa C++ DOVETE usare quella.
- NON chiedete ai docenti se una VOSTRA scelta implementativa va bene o
meno. Fà parte della valutazione del progetto.
- PRIMA DI SCRIVERE CODICE LEGGETE ACCURATAMENTE TUTTO IL TESTO
DEL PROGETTO.
