import json
import tkinter as tk
from tkinter import Canvas


class SuffixTreeGUI:
    def __init__(self, root):
        self.root = root
        self.canvas = Canvas(root, width=800, height=600, bg="white")
        self.canvas.pack(fill="both", expand=True)
        self.node_radius = 20
        self.margin = 50
        self.level_height = 100
        self.node_positions = {}

    def draw_tree(self, tree_data, x, y, level=0):
        label = tree_data.get("label", "")
        start = tree_data.get("start", -1)
        end = tree_data.get("end", -1)
        node_id = (x, y)

        # Draw the current node
        self.canvas.create_oval(
            x - self.node_radius,
            y - self.node_radius,
            x + self.node_radius,
            y + self.node_radius,
            fill="lightblue",
        )
        self.canvas.create_text(x, y, text=f"[{start},{end}]", font=("Arial", 8))
        if label:
            self.canvas.create_text(
                x, y + self.node_radius + 10, text=label, font=("Arial", 10)
            )

        # Draw children
        children = tree_data.get("children", [])
        child_x = x - (len(children) - 1) * self.margin // 2
        for child in children:
            self.canvas.create_line(x, y + self.node_radius, child_x, y + self.level_height - self.node_radius, arrow=tk.LAST)
            self.draw_tree(child, child_x, y + self.level_height, level + 1)
            child_x += self.margin

    def load_tree(self, json_file):
        with open(json_file, "r") as f:
            tree_data = json.load(f)
        self.draw_tree(tree_data, 400, 50)


if __name__ == "__main__":
    root = tk.Tk()
    root.title("Suffix Tree Visualization")
    gui = SuffixTreeGUI(root)
    gui.load_tree("suffix_tree.json")
    root.mainloop()
