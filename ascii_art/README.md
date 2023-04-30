# ASCII Art Generator

Nástroj, který na vstupu získá obrázek nebo sadu několika obrázků a překonvertuje je do ASCII art vizualizace.

## Zadání

1) Nástroj načítá obrázky v alespoň jednom běžném souborovém formátu. (př. BMP, PNG, JPEG, SVG, …)
2) Implementujte alespoň 5 druhů různých operací (př. změna jasu, negativ, konvoluce, změna velikosti obrázku, …)
3) Výstupem nástroje je ASCII art (textové odstíny šedi) vytvořený z obrázků, který umí zobrazit a uložit do souboru.
4) Nástroj musí být konfigurovatelný ze souboru:
    - Definice ASCII přechodů (př. název, znaky seřazené dle hustoty, …)
    - Definice aplikovaných filtrů (jeden filtr může být aplikován víckrát s různými parametry)
5) V případě více předaných obrázků:
    - Nástroj spustí prezentaci jednotlivých snímků, kterou lze ovládat (alespoň změna snímku, zastavení prezentace, spuštění prezentace).
    - Lze definovat filtry pro jednotlivé obrázky i pro celou množinu.

### Kde lze využít polymorfismus?

- Filtry: změna jasu, negativ, konvoluce, změna velikosti obrázku, …
- Různé styly ASCII vykreslení
- Formáty vstupu: BMP, SVG, RAW, …
- Druh výstupu: zobrazení, soubor, prezentace, …
- Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), …


                                              _.oo.
                      _.u[[/;:,.         .odMMMMMM'
                   .o888UU[[[/;:-.  .o@P^    MMM^
                  oN88888UU[[[/;::-.        dP^
                 dNMMNN888UU[[[/;:--.   .o@P^
               ,MMMMMMN888UU[[/;::-. o@^
                NNMMMNN888UU[[[/~.o@P^
                888888888UU[[[/o@^-..
               oI8888UU[[[/o@P^:--..
            .@^  YUU[[[/o@^;::---..
          oMP     ^/o@P^;:::---..
       .dMMM    .o@^ ^;::---…
      dMMMMMMM@^`       `^^^^
     YMMMUP^
      ^^

