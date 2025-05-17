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

## Schema electrica:
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
![flappybird_pozacircuit](https://github.com/user-attachments/assets/5aa83140-0784-44a8-92f8-1f7e8dad79ea)

