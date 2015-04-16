#Siegbedingung
##Zwei Wege
* entweder nach jedem gelegten Tile den roten und weißen Pfad
zurückverfolgen und wenn man einen Loop macht oder 8 Spalten/Reihen nur rot
oder nur weiß is Sieg.
* Oder jedem Tile eine ID geben und jedem Pfad eine ID geben und wenn sich zwei
Pfade treffen wieder IDs kombinieren und neue ID geben.

Erste Methode ist einfacher, aber kann proportionell weniger effizient sein.

#Punkteabzug
Man kriegt Punkteabzug, wenn man in der Game-Klasse mit einer if Abfrage die
Commands abfragt, weil wenn man in Zukunft neuen Commad einfügen würde müsste
man eine neue if Abfrage screiben. Besser wäre ein Vector mit allen Befehlen,
wo man neuen hinzufügen kann, und man fragt dann nur Vector mit if Abfrage in
der Game Klasse ab.
