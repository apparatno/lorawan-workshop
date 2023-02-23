# MQTT Client

Lag en MQTT klient som kan lytte på events fra The Things Network.
Dette eksemplet er skrevet i Go
men du kan bruke et annet språk
hvis du er mer komfortabel med det.

[The Things Network dokumentasjon på MQTT](https://www.thethingsindustries.com/docs/integrations/mqtt/)

**Tips**

👉 Hent ut connection info fra TTN Console 
under _Integrations -> MQTT_

👉 Lytt på alle topics med `#`.
Senere kan du evt utvide med flere subscribers
som kan lytte på forskjellige eventer.

👉 Meldingene inneholder mye mer data 
enn bare din payload fra Arduinoen.
Trykk på en melding i TTN Console
for å se hva den inneholder.
`data` er hva du er ute etter.

## ⭐ Stretch goal ⭐

Send en melding til din Arduino 
ved å publisere via MQTT til TTN brokeren.
