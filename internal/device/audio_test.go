package device

import "testing"

func TestAudio(t *testing.T) {
	got := GetDefaultAudioInput()
	expected := "alsa_input.usb-Logitech_USB_Headset_Logitech_USB_Headset-00.mono-fallback"
	if got != expected {
		t.Errorf("error getting default input device\nexpected:\n%s\ngot:\n%s\n", expected, got)
	}

	got = GetDefaultAudioOutput()
	expected = "alsa_output.usb-Logitech_USB_Headset_Logitech_USB_Headset-00.analog-stereo"
	if got != expected {
		t.Errorf("error getting default output device\nexpected:\n%s\ngot:\n%s\n", expected, got)
	}
}
