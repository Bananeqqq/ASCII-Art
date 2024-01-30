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

## Jak například spustit tento nástroj:
make clean  
make (compile)  
./app --conf cfg.config img_path1 --output_type possible_anotherImg1 possible_anotherImg2  

./app --screen --fancy examples2/space/5.jpg


### Upřesnění:
Filtry (operace) zadané jako args nebo jako config je možné definovat globálně (pro všechny obrázky) a nebo pro každý obrázek zvlášť. Pokud chceme definovat filtry/config globálně, je nutné, aby byly definovány před prvním obrázkem.  


#### Je možné načítat obrázky PNG a JPG, kde uživatel může:
1) Změnit velikost obrázku pomocí parametru "scale" (tedy 1 default, 0-1 zmenšení a 1-10 zvětšení, 10 je limit) 
2) Změnit "jas" obrázku pomocí parametru "brightness" (2 default v kódu, minimum je 0, s menší hodnotou je obrázek světlejší a s větší hodnotou je obrázek tmavší) 
3) Invertovat obrázek pomocí parametru "invert" (false default, true invert) 
4) Rotovat obrázek pomocí parametru "rotate" (0 default, 90, 180, 270) 
5) Vertical/horizonotal flip obrázeku pomocí parametru "flip"  

Tyto filtry je možné aplikovat libovolně mnohokrát, v libovolném pořadí a libovolně na jednotlivé obrázky či na všechny najednou. 

#### Obrázky je možné zobrazit 4 způsoby:
1) Všechny vykreslit do terminálu v ascii artu (--console) 
2) Uložit všechny do jednoho textového souboru (--file file_name) 
3) Zobrazit je v okně, kde je možné mezi nimi procházet šipkama, zoomovat a "pohybovat se", a pomocí mezerníku spustit/zastavit "prezentaci" (--screen) 
4) Uložit je do obrázku, který se uloží tam, odkud byl obrázek načten (--image)  

**Je možné zvolit pouze jednu metodu výstupu**, je nutné ji zadat jako argument (tedy ne v config souboru) 

Následně u --screen a --image je možné použít argument --fancy, aby se obrázek vykreslil s co největším písmem.
Mimo tyto filtry je možné definovat ascii přechod (**musí** být v souboru), který se použije pro vykreslení obrázku.   

**Syntaxe argumentů je:**  
--ascii file_with_ascii_chars  
--conf file_name  
--brightness number  (funguje naopak, vyšší číslo -> tmavší obrázek, default hodnota je 2, minimální 0)
--invert  
--scale number  
--rotate number  
--flip-horizontal  
--flip-vertical  
--fancy   

**Syntaxe configu je:**  
ascii=custom.ascii  
scale=1   
invert=false  
brightness=0  
flip=horizontal  
flip=vertical  
rotate=90  
fancy=true  
