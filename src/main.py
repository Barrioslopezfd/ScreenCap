from datetime import datetime
from tkinter import BOTH, Canvas, Tk
import pyautogui as pg
from PIL.ImageGrab import grab


class Window:
    def __init__(self) -> None:
        self.root = Tk()
        self.root.wait_visibility()
        self.width, self.height = pg.size()
        self.root.wm_geometry(f"{self.width}x{self.height}+0+0")
        self.root.attributes('-alpha', 0.5)
        self.root.config(cursor="cross")
        self.start_x = 0
        self.start_y = 0
        self.end_x = 0
        self.end_y = 0
        self.selection_rect = None
        self.canvas = Canvas(self.root,bg="white", highlightthickness=0)
        self.canvas.pack(fill=BOTH, expand=True)
        self.root.bind("<ButtonPress-1>", self.on_click)
        self.root.bind("<B1-Motion>", self.on_drag)
        self.root.bind('<ButtonRelease-1>', self.on_release)
        self.root.bind('<Escape>', self.close_window)
        self.root.mainloop()

    def close_window(self, _):
        self.root.destroy()

    def on_click(self, event):
        self.start_x = event.x
        self.start_y = event.y
        self.canvas.delete("selection")
        self.selection_rect = self.canvas.create_rectangle(self.start_x, self.start_y, self.start_x, self.start_y, outline="red", width=2)

    def on_drag(self, event):
        self.end_x = event.x
        self.end_y = event.y
        if self.selection_rect != None:
            self.canvas.coords(self.selection_rect, self.start_x, self.start_y, self.end_x, self.end_y)
        self.canvas.create_rectangle(self.start_x, self.start_y, self.end_x, self.end_y, fill='', outline='', tags="transparent")

    def on_release(self, event):
        self.end_x = event.x
        self.end_y = event.y
        if self.start_x > event.x:
            tmp=self.start_x
            self.start_x = event.x
            self.end_x = tmp
        if self.start_y > event.y:
            tmp=self.start_y
            self.start_y = event.y
            self.end_y = tmp
        self.root.attributes('-alpha', 0)
        self.root.after(100, self.take_screenshot)

    def take_screenshot(self):
        if self.start_y != self.end_y and self.start_x != self.end_x:
            box = (self.start_x, self.start_y, self.end_x, self.end_y)
            screenshot = grab(bbox=box)
            timestamp = datetime.now().strftime("%Y_%m_%d_%H_%M_%S")
            filename = f"screenshots/{timestamp}.png"
            screenshot.save(filename) #TODO: CHANGE SAVE FOLDER 
            self.root.destroy()

def main():
    Window()

main()

