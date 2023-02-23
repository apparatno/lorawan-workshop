package main

import (
	"context"
	"encoding/json"
	"log"
	"os"
	"os/signal"

	mqtt "github.com/eclipse/paho.mqtt.golang"
)

type Payload struct {
	ReceivedAt    string `json:"received_at"`
	UplinkMessage struct {
		DecodedPayload struct {
			Temperature float32 `json:"temperature"`
		} `json:"decoded_payload"`
	} `json:"uplink_message"`
}

var onConnect = func(c mqtt.Client) {
	log.Println("Client connected")
}

var onConnectionLost = func(c mqtt.Client, err error) {
	log.Fatal(err)
}

var onMessageReceived = func(c mqtt.Client, m mqtt.Message) {
	var p Payload // map[string]interface{}
	if err := json.Unmarshal(m.Payload(), &p); err != nil {
		log.Fatalf("failed to unmarshal payload: %v", err)
		return
	}

	log.Printf("%v: %v", m.Topic(), p)
}

func main() {
	opts := mqtt.NewClientOptions().
		AddBroker("tcp://eu1.cloud.thethings.network:1883").
		SetUsername("ilder-test@ttn").
		SetPassword(os.Getenv("MQTT_PASSWORD")).
		SetOnConnectHandler(onConnect).
		SetConnectionLostHandler(onConnectionLost)

	client := mqtt.NewClient(opts)

	if token := client.Connect(); token.Wait() && token.Error() != nil {
		log.Fatal(token.Error())
	}

	ctx, cancel := context.WithCancel(context.Background())

	subscribe(ctx, client)

	sigs := make(chan os.Signal)
	signal.Notify(sigs, os.Kill, os.Interrupt)

	<-sigs

	cancel()

	log.Println("Done")
}

func subscribe(ctx context.Context, c mqtt.Client) {
	token := c.Subscribe("#", 0, onMessageReceived)
	token.Wait()
	log.Println("Subscribed")
	<-ctx.Done()
}
