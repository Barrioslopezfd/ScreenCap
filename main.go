package main

import (
	"fmt"
	"time"

	"github.com/go-vgo/robotgo"
	"github.com/go-vgo/robotgo/event"
)

func main() {
	fmt.Println("Escuchando clicks del mouse...")

	evChan := event.Start()
	defer event.End()

	var downX, downY, upX, upY int

	for e := range evChan {
		if e.Kind == event.MouseDown && e.Button == robotgo.MouseMap["left"] {
			downX, downY = e.X, e.Y
			fmt.Printf("Mouse PRESIONADO en: (%d, %d)\n", downX, downY)
		}
		if e.Kind == event.MouseUp && e.Button == robotgo.MouseMap["left"] {
			upX, upY = e.X, e.Y
			fmt.Printf("Mouse SOLTADO en: (%d, %d)\n", upX, upY)
			break
		}
		time.Sleep(10 * time.Millisecond)
	}

	fmt.Printf("\nResumen:\n- Presionado: (%d, %d)\n- Soltado:   (%d, %d)\n", downX, downY, upX, upY)
}
