package device

import (
	"log"
	"os/exec"
	"strings"
)

func GetDefaultAudioOutput() string {
	out, err := exec.Command("pactl", "get-default-sink").Output()
	if err != nil {
		log.Fatal(err)
	}
	outStr := string(out)
	return strings.TrimSpace(outStr)
}

func GetDefaultAudioInput() string {
	out, err := exec.Command("pactl", "get-default-source").Output()
	if err != nil {
		log.Fatal(err)
	}
	outStr := string(out)
	return strings.TrimSpace(outStr)
}
