# Progetto Intermedio
## Informazioni Generali
- Membri del gruppo: Pietro Ballarin, Elisa Chiarel, Diego Chiesurin.
- Elementi di codice sviluppati per componente:
    - Pietro Ballarin: 
        - new_scan
        - get_distance
        - LidarDriver constructor
        - test_new_scan
        - test_get_distance
        - main
    - Elisa Chiarel:
        - clear_buffer
        - get_latest
        - operator<<
        - test_clear_buffer
        - test_get_latest
        - test_stream_operator
    - Diego Chiesurin: 
        - LidarDriver copy constructor
        - get_scan
        - empty
        - rand_double
        - test_get_scan
        - main
    
## Relazione
Il gruppo si riunisce il giorno Giovedì 21 per ricevere la consegna del progetto intermedio.
Letta la specifica il gruppo ha ragionato sulle scelte progettuali della classe LidarDriver, in
particolare indaga le seguenti possibili scelte implementative con rispettivi vantaggi e svantagggi:
- Utilizzo della memoria dinamica:
    - **PRO**:
        - Memoria fissata -> la dimensione fissa del buffer è garantita.
    - **CONTRO**:
        - Necessità di reimplementare le funzioni utili per la gestione di inserimenti, accessi e rimozioni
        - Necessità di gestire la memoria -> codice aggiuntivo legato al distruttore, propensione ai memory leak
        - Difficile risoluzione degli errori
- Utilizzo degli standard vector:
    - **PRO**:
        - Semplice gestione delle entry attraverso le funzioni già implementate
        - Facile gestione degli errori in quanto isolati alla sola logica del programma
    - **CONTRO**:
        - E' una struttura dinamica -> bisogna garantire la lunghezza fissa del buffer
- Posizionamento della costante BUFFER_DIM in lidardriver.h:
    - **PRO**:
        - La distribuzione della libreria lidardriver consente di modificare la costante
        - I driver hanno tutti buffer della stessa dimensione -> il costruttore per copia
            è più semplice.
    - **CONTRO**:
        - L'utente deve accedere all'headerfile della libreria per modificarlo
- Posizionamento della costante BUFFER_DIM in main.cpp
    - **PRO**:
        - La costante è modificabile direttamente nel main
    - **CONTRO**:
        - La dimensione del buffer nel lidardriver non è specifata a priori -> la dimensione deve essere
            passata all'interno del costruttore -> possono esistere istanze di lidardriver con buffer di
            dimensione diversa.
        - L'utente deve preoccuparsi di un'informazione aggiuntiva

Delle scelte progettuali, valutati i pro e i contro, si è scelto di procedere con le seguenti:
    - Utilizzo degli standard vector
    - Posizionamento della costante BUFFER_DIM in lidardriver.h
si sono quindi formalizzate le scelte in un diagramma UML della classe.

Dopodiché le componenti si sono concentrate nella scrittura del codice come descritto dalla specifica.
Durante questa fase, appena implementata una nuova funzione in lidardriver.cpp, viene 
subito provata tramite un'apposita funzione in main.cpp.
Le funzioni di test sono state create in modo da verificare un vasto numero di casi
e garantire quindi la generalità delle funzioni di lidardriver.
Terminata la scrittura del codice, ogni membro del gruppo ha effettuato la revisione del codice 
degli altri membri, eventualmente discutendone di possibili cambiamenti.

## Strumenti utilizzati
    - git
    - GitHub
    - CMake
    - VSCode LiveShare