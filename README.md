# Flappy Bird
## Introducere
**Flappy Bird** este un joc arcade simplu, dar captivant, în care jucătorul controlează o pasăre ce trebuie să zboare printre obstacole (de obicei, tuburi verticale). Jocul este cunoscut pentru mecanica sa simplă: pasărea se ridică atunci când utilizatorul apasă un buton și coboară automat din cauza gravitației simulate. Scopul este să se evite coliziunea cu obstacolele, în timp ce jucătorul adună puncte.

Acest proiect constă în dezvoltarea unei versiuni mai simplificate a preacunoscutului joc **Flappy Bird** folosind concepte învățate în cadrul cursurilor și laboratoarelor de **Proiectare cu Microprocesoare (PM)**, având la bază o plăcuță de **Arduino** și diverse **componente electronice** care vor forma dispozitivul final.

**Comparativ cu versiunea originală**, varianta mea a jocului nu se va folosi de gravitație în cazul în care jucătorul nu va mai apăsa pentru a face pasărea să zboare, ci poziția acesteia va rămâne pe loc. **Controlul** păsării se va baza pe folosirea unui **joystick** unde, pentru a ridica pasărea, maneta se va da în sus, iar pentru a coborî pasărea, maneta se va da în jos. Mai mult, jucătorul va putea apăsa un **buton** pentru **a opri și reporni** jocul, iar în cazul în care jucătorul pierde și are un scor destul de mare, poate să îl păstreze prin **introducerea de la tastatură** a numelui său, care o să apară apoi în meniul de **"high score"**, pe care îl putem accesa prin apăsarea altui **buton**.

Acest proiect îmi oferă oportunitatea de a aplica ceea ce am învățat până acum, îmbinând **concepte de hardware și noțiuni de software**, creând astfel o **experiență interesantă și educativă** pentru mine și **distractivă** pentru ceilalți sau chiar un **punct de plecare** pentru amatorii din domeniul electronicii.

## Descriere generală
### Rolul componentelor și interacțiunile între acestea:
  * Elementul central al proiectului îl reprezintă o plăcuță de **Arduino UNO** ce are rolul de **a comunica** cu celelalte componente
  * Pentru **a vizualiza** jocul, prin intermediul plăcuței de Arduino, se vor transmite către un **ecran LCD** date prin intermediul **protocolului SPI**
  * Pentru a face jocul mai **dinamic**, la acțiuni precum **mișcarea păsării** în sus sau în jos, dar și atunci când se lovește, o să se audă anumite **efecte sonore**, acestea fiind transmise către un **amplificator cu potențiometru** (modularea volumului), iar apoi către **speaker**
  * Cât timp jocul se derulează, un **LED verde** se va aprinde încet-încet, iar apoi se va stinge încet-încet, iar când jucătorul e în meniu sau a pierdut, un **LED rosu** se va aprinde și stinge în același mod
  * Pentru **a începe** jocul, se va apăsa un **buton**, care va fi folosit și pentru a-l opri și reporni 
  * Pentru **a deplasa** pasărea, se folosește un **joystick**, iar poziția acestuia va fi transmisă către plăcuță, unde va fi interpretată cu ajutorul **convertorului analog-digital (ADC)**
  * Jocul permite vizualizarea **scorului** (de câte tuburi a trecut pasărea), dar și a **timpului** trecut în încercarea actuală **(timer)**
  * După ce jucătorul se lovește de un tub și astfel își încheie tura, acesta, dacă are un scor destul de mare, îl poate păstra salvându-l în **clasament**, introducându-și numele de la **tastatura laptop-ului (UART)**
  * Când jucătorul se află în **meniul principal**, pe lângă funcția de a începe jocul, poate vizualiza și clasamentul global prin apăsarea altui **buton** decât cel de start

**Schema bloc a dispozitivului:**

![schbloc](https://github.com/user-attachments/assets/c50cc914-41ef-49d4-97b2-af08b49f58a8)

## Hardware Design
### Lista de componente ale proiectului:
  * **Arduino UNO** cu ATMega328P
  * Modul **LCD** SPI de 2.8” (240×320) cu driver ILI9341
  * 1 **speaker** 4 ohm, 3 W
  * Modul **amplificator** audio PAM8403 cu potențiometru
  * Modul **joystick** cu două axe XY HW-504
  * breadboards, butoane, LED-uri, cabluri, rezistențe


## **Bill Of Materials (BOM)**

|**Denumire componentă**|**Link**|**Nr. bucăți**|
|-------|-----|-----|
|Arduino UNO R3|https://cleste.ro/kit-inva-are-arduino.html|1|
|Butoane|https://cleste.ro/kit-inva-are-arduino.html|2|
|Rezistență 220 ohm|https://cleste.ro/kit-inva-are-arduino.html|2|
|Rezistență 10K ohm|https://cleste.ro/kit-inva-are-arduino.html|5|
|LED roșu|https://cleste.ro/kit-inva-are-arduino.html|1|
|LED verde|https://cleste.ro/kit-inva-are-arduino.html|1|
|Joystick|https://sigmanortec.ro/Modul-joystick-doua-axe-XY-p126458908|1|
|Amplificator Audio PAM8403|https://sigmanortec.ro/Modul-amplificator-audio-PAM8403-cu-potentiometru-3W-2CH-p166125746|1|
|Boxa 40mm 3W|https://sigmanortec.ro/Speaker-40mm-3W-p134573662|1|
|Modul LCD 2.8'' cu SPI|https://www.optimusdigital.ro/en/lcds/3544-modul-lcd-spi-de-28-cu-touchscreen-controller-ili9341-i-xpt2046-240x320-px.html?search_query=Modul+LCD+de+2.8%27%27+cu+SPI+%C8%99i+Controller+ILI9341+%28240x320+px%29&results=3|1|

(Plăcuța, butoanele, rezistențele și LED-urile provin din același set și au același link)

## Schema electrică:
![schemaelectrica](https://github.com/user-attachments/assets/d0e753bc-31a2-4a77-a277-78dffa2cdc95)


## Funcționalitatea hardware și pinii folosiți:

Toate componentele sunt conectate la **Arduino UNO**:

- **LCD**:
  - comunică cu plăcuța prin intermediul protocolului **SPI** pentru **a afișa** jocul
  - pinii ecranului au nevoie la intrare de 3.3V, dar pinii Arduino dau 5V, așa că am introdus **rezistențe de 10K** pentru a limita tensiunea care va ajunge la LCD
  - pentru protocolul SPI este nevoie de pinii **D10, D11, D13**, aceștia fiind **CS, MOSI, respectiv SCK**
  - nu avem nevoie de pinul **D12** (MISO) întrucât nu trebuie să trimitem nimic de la LCD la plăcuță
  - pinul **D9** este folosit ca **D/C** care indică dacă datele primite prin SPI sunt comenzi sau date
  - pinul **D8** este folosit ca **RESET** pentru a reseta LCD-ul la pornire
- **Joystick**:
  - comunică cu plăcuța prin pinii de **ADC** (**A0** -  pentru Rx, **A1** - pentru Ry)
  - **controlează** pasărea în timpul jocului 
- **Butoane**:
  - un buton **pornește** jocul, iar în timpul acestuia poate să-l **oprească** și să-l **repornească** prin intermediul unei **întreruperi hardware** (**D2** - pin pentru întreruperi hardware)
  - alt buton poate să **afișeze** clasamentul de highscore (**D4** - pin de intrare)
  - pentru a nu avea cazuri de fire în aer activez **rezistențele de pull-up** pentru fiecare buton
- **Amplificator + Speaker**:
  - redă **efecte sonore** în cadrul jocului
  - sunetul este transmis către **amplificator**, unde va fi modulat cu ajutorul unui **potențiometru**, iar apoi va ajunge mai departe la **speaker** (**D3** - funcția tone() pe care o folosesc ca să redau sunete are nevoie de timer2, care este valabil prin acest pin)
- **LED-uri**:
  - un **LED verde** se va aprinde și stinge continuu semnalizând că jocul este în **desfășurare** (**D6** - pin cu PWM pentru variația intensității luminii) 
  - un **LED roșu** se va aprinde și stinge continuu semnalizând că jocul ori nu a început, ori s-a terminat (**D5** - pin cu PWM pentru variația intensității luminii) 
  - aprinderea și stingerea LED-urilor va fi controlată prin **PWM**
  - pentru a nu se arde am adăugat în serie câte o **rezistență de 220Ω**
- **Laptop**:
  - utilizat pentru a **transfera codul** către plăcuța Arduino
  - prin intermediul protocolului **UART** se va citi de la **tastatura** acestuia numele nou prin care se va salva highscore-ul (**D0, D1** - sunt deja conectați la cablul de date)

## Asamblarea întregului circuit + testare funcționare piese (LCD):
(Click pe poză pentru video)

[![flappybird_pozacircuit](https://github.com/user-attachments/assets/5aa83140-0784-44a8-92f8-1f7e8dad79ea)](https://youtube.com/shorts/IP-DghO4OIs?feature=share)

## Software Design

**Biblioteci folosite:**

  * **"SPI.h", "Adafruit_GFX.h", "Adafruit_ILI9341.h"** - aceste biblioteci îmi oferă posibilitatea de a comunica cu LCD-ul, dar îmi și facilitează modalitățile prin care pot scrie cuvinte (meniul principal, meniul de highscore) sau să afișez jocul (pasărea, tuburile) așa cum îmi doresc

**Funcții folosite din bibliotecile menționate:**
  * **fillScreen()**: umple ecranul în întregime cu o culoare specificată
  * **fillRect()**: pornind de la o poziție specificată, umple un dreptunghi de lungime width și înălțime height cu o anumită culoare aleasă
  * **setTextColor()**: setează culoarea textului
  * **setTextSize()**: setează mărimea textului
  * **setCursor()**: mută cursorul la o poziție specificată
  * **print()/println()**: afișează textul pe LCD

**Meniul principal**

![functie_main_menu](https://github.com/user-attachments/assets/c31327d9-846d-4a07-af2a-ee39f90e48de)

![poza_meniuprincipal](https://github.com/user-attachments/assets/84c92b49-ffca-4cdb-99fe-98cf0aeab61e)


**Pasărea**

![functie_desenare_pasare](https://github.com/user-attachments/assets/35f351f6-2db3-493f-a423-7bfc5ab8b0e2)

![poza_pasare](https://github.com/user-attachments/assets/6404eecc-dcf1-4d6d-ae32-0125851f8770)


**Elemente de noutate**

Față de versiunea originală a jocului, proiectul meu are câteva elemente în plus:
  * **mișcarea păsării** - în jocul de bază, ca să ții pasărea într-o anumită poziție trebuia să apeși continuu pe ecran, aplicându-se legile gravitației, însă în versiunea mea, prin mișcarea joystick-ului în sus și în jos, nu doar că se duce în acea poziție, dar și rămâne acolo, fără a mai fi nevoie de interacțiunea jucătorului
  * **oprirea/repornirea jocului** - în versiunea originală, odată ce ai început jocul nu te mai poți opri decât dacă pierzi, în schimb jocul meu oferă opțiunea de a-l pune pe pauză și de a-l reporni prin apăsarea unui simplu buton
  * **LED-uri** - în implementarea proiectului am adăugat două LED-uri care îi arată jucătorului dacă este în timpul jocului (un LED verde se aprinde și stinge continuu) sau în afara lui (un LED roșu se aprinde și stinge continuu)

### Funcționalități laborator

   * **Întreruperi**
     
Am configurat butoanele conectate la pinul PD2, respectiv PD4, ca intrări și le-am activat rezistențele de pull-up. În cazul butonului de pe pinul PD2, i-am activat întreruperea externă care va avea loc pe falling edge pentru a gestiona schimbările de stare în joc:
* dacă game_state este 0, jocul începe, resetând scorul și fundalul
* dacă game_state este 4, trece la actualizarea tabelului de highscore
* în alte cazuri, schimbă între start și pauză
* de asemenea, resetează starea LED-urilor și valorile PWM asociate.

![setup_butoane](https://github.com/user-attachments/assets/534e9483-faf0-4212-8800-91dbbdabab76)

![ISR](https://github.com/user-attachments/assets/26f8b735-34d8-4505-968b-51d625c4f87c)


   * **PWM**
     
Am configurat pinii PD5 și PD6 ca ieșiri PWM pentru controlul LED-urilor, utilizând modul Fast PWM cu un prescaler de 64.

Funcția **fade_leds**:
 * controlează luminozitatea LED-urilor roșu (PD5) și verde (PD6) prin variarea graduală a valorii de umplere (duty cycle) între 0 și 255
 * cât timp jocul rulează (game_state = 1) LED-ul verde este activ, iar în restul de cazuri (în meniul principal, în meniul de highscore, când jocul este pe pauză, când jocul s-a încheiat) LED-ul roșu este activ
 * creșterea și descreșterea valorilor din OCR0A și OCR0B simulează un efect de fade (aprindere/stingere graduală)

![setup_leduri](https://github.com/user-attachments/assets/e270e599-3c99-4286-bd83-d762601da760)

![functie_leduri](https://github.com/user-attachments/assets/e800b2f0-5365-4615-adb3-f3bd5e1d3cf3)


**Alte funcționalități:**

  * **UART**
    
În cod, folosesc UART pentru a primi un nume de la utilizator printr-o conexiune serială.

Procesul se desfășoară astfel:
* atunci când jocul este în starea game_state = 5 (salvare highscore), programul intră într-o buclă în care așteaptă date de la tastatură prin portul serial
* după ce datele sunt disponibile, folosesc funcția Serial.readStringUntil() pentru a citi numele jucătorului introdus de la tastatura laptop-ului
* numele citit îl utilizez pentru a actualiza tabela de highscore (names[] și scores[]), apelând funcția update_highscore()
* funcția update_highscore() caută poziția unde trebuie adăugat noul scor, apoi mută celelalte scoruri pentru a-i face loc astfel încât să fie în ordine descrescătoare

![uart](https://github.com/user-attachments/assets/cb6e538c-be8a-4d87-aa39-e33b363d68d8)

![update_highscore](https://github.com/user-attachments/assets/581218bb-d160-45f8-92a1-d9d032eed7c6)

  * **ADC**
    
Folosesc Convertorul Analog-Digital pentru a citi poziția joystick-ului, astfel modificând poziția păsării:
- am configurat pinul A1 ca intrare pentru a citi semnalul analogic de la joystick
- utilizez funcția analogRead(A1) pentru a converti tensiunea de pe pinul A1 într-o valoare între 0 și 1023 (această valoare reprezintă poziția joystick-ului pe axa Y)
- după câteva încercări, am constatat că atunci când dau în jos joystick-ul primesc valori apropiate de 0 (mai mici decât 10), iar când îl dau în sus primesc valori apropiate de 1023 (mai mari decât 1010)
- cu aceste valori am reușit să creez o mișcare decentă pentru pasăre, limitându-i înălțimea când aceasta ar fi putut ieși din ecran

  ![input_joystick](https://github.com/user-attachments/assets/a1984cc9-1866-42c1-8418-7d380d3c41c9)

  ![miscarea_pasarii](https://github.com/user-attachments/assets/71147885-8989-4a3c-adc9-a42b50313945)


 * **Sunete**
    
Am folosit funcția tone() pentru a genera semnale audio atunci când am trecut cu bine de turnuri (am generat un semnal cu o frecvență ridicată timp de 100ms), dar și atunci când m-am lovit de acestea (am generat un semnal cu o frecvență mai scăzută timp de 100ms).

![sunete](https://github.com/user-attachments/assets/4ce6d670-5139-4aec-a26e-772d91c7d2f6)

  
  * **SPI**
    
Am folosit în majoritatea codului protocolul SPI fiind necesar în afișarea întregului joc pe ecranul LCD.

De la afișarea meniurilor și până la desenarea pieselor jocului, anume pasărea și turnurile, toate acestea le-am realizat utilizând funcții legate de acest protocol.

Prin utilizarea variabilei **game_state**, în funcție de valoarea acesteia, pot să determin ce stare din joc să afișez în acel moment.

### Optimizări:
* creare de funcții pentru evitarea codului repetitiv (show_main_menu(), show_highscore_menu(), etc.)
* micșorarea size-ului variabilelor (int8_t sau int16_t în loc de int pentru a micșora memoria totală a programului)
* logica PWM pentru controlul LED-urilor (în loc să folosesc cicluri software pentru controlul intensității, care ar fi blocat loop-ul, am utilizat hardware PWM: OCR0A, OCR0B)
* manipularea eficientă a întreruperilor (prin utilizarea întreruperii hardware de la butonul roșu am evitat blocarea buclei principale)

## Concluzii

Proiectul a reprezentat o oportunitate excelentă de a îmbina cunoștințele teoretice și practice dobândite în timpul orelor de curs și laboratoarelor, punându-mi în valoare atât abilitățile software, cât și cele hardware. Realizarea efectivă a jocului a fost o experiență unică și captivantă, care mi-a permis să explorez interacțiunea dintre componentele fizice și software, ducând la un rezultat funcțional de care m-am putut bucura.

## Bibliografie/Resurse
 * optimusdigital.ro
 * sigmanortec.ro
 * cleste.ro
 * ATmega328P Datasheet
