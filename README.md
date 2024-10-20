ScreenCap, as the name may imply, lets you record the screen or simple take a screenshot

Videos will be saved in /home/$USER/Video/Recorded
Screenshots will be saved in /home/%USER/Pictures/Screenshots

This project is being developed for the i3WM because i dont have this features and found myself needing the way too often

You'll need a compositor for some of the features, i used Picom.

sudo apt install picom

add exec --no-startup-id picom -b to your i3 config to start picom on boot.
