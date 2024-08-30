# Progetto 2 smart-room

Il programma rappresenta una smart-room in Arduino composta da 3 task:

## 1. Climatask
*2 led per riscaldamento e 2 per raffreddamento, 1 sensore di temperatura*

Gestisce gli output del sensore di temperatura, accendendo di conseguenza i led del riscaldamento o del raffreddamento (1 led metà potenza, 2 led piena potenza)

## 2. DoorTask
*1 servo, 1 sensore di movimento a ultrasuoni*

Rileva la presenza di movimenti sotto i 50cm, aprendo la porta per 30 secondi dall'ultimo movimento rilevato.

## 3. SmartLampTask
*1 bottone, 1 led, 1 fotoresistore LDR*

Composta di due modalità:

**Automatica**  --> *attivabile digitando 'a' nella porta seriale:*

Rileva la presenza di luce nella stanza e accende la lampada sotto i 100 lux, per poi spegnerla sopra i 500 lux.

**Manuale** --> *attivabile digitando 'm' nella porta seriale:*

Permette di accendere o spegnere manualmente la lampada premendo il bottone.

---

Diagramma presente in /smart-room/smart-room.plantuml

### di Broccoli Gabriele