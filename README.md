Cílem projektu bylo s využitím vývojového kitu Espressif ESP32, snímačem srdečního tepu PulseSensor, grafického OLED displeje a vývojového prostředi Arduino zrealizovat systém pro měření srdečního tepu. 

Použitý senzor srdečního tepu generuje analogový výstup, který je konvertován na digitální podobu pomocí analogově-digitálního převodníku uvnitř mikrokontroléru ESP32. 

Projekt byl vyvíjen ve Visual Studio Code ve spojení s PlatformIO, jenž zajišťovalo správu knihoven, nahrávání kódu na hardware a integraci s mikrokontrolérem ESP32.

Dokumentace (až 4 b): 4\
Funkčnost (až 5 b): 5\
Prezentace (až 1 b): 1\
Kvalita implementace (až 4 b): 2\
Celkem (až 14 b): 12.0\
Komentář: Dle demonstračního videa se zdá, že měření tepu je na programové úrovní zvládnuté docela slušně. Ocenil bych však nějaké uživatelské rozhraní na displeji, když už bylo dovoleno použití existujících knihoven, a využití doplňkového ovladače pro pohyb mezi položkami menu. Zajímavá by rovněž byla detekce nepřiloženého prstu.
