from graphviz import Digraph

def parse_suffix_tree(input_text):
    """Parse the suffix tree input into a nested dictionary."""
    head = {"head": {"label": "head", "indices": [], "children": {}}}
    stack = [(head["head"], 0)]

    for line in input_text.strip().splitlines():
        parts = line.split('lNivel = ')
        if len(parts) < 2:
            continue
        depth_label, line_content = parts[1].split('--', 1)
        depth = int(depth_label.strip())
        while stack and stack[-1][1] >= depth:
            stack.pop()

        parent, _ = stack[-1]
        label, *indices = line_content.split('[')
        label = label.strip().strip()
        indices = [int(x) for x in indices[0].strip(']').split(', ')] if indices else []

        node = {'label': label, 'indices': indices, 'children': {}, 'unique_id': id(label)}
        parent['children'][f"{label}_{len(parent['children'])}"] = node
        stack.append((node, depth))

    return head

def add_nodes(graph, tree, parent="head_0"):
    """Recursively add nodes and edges to the graph."""
    for label, node in tree.items():
        unique_id = f"{node['label']}_{id(node)}"
        node_id = f"{label}_{unique_id}"
        graph.node(node_id, f"{node['label']} [{', '.join(map(str, node['indices']))}]")
        if parent:
            graph.edge(parent, node_id)
        add_nodes(graph, node['children'], node_id)

def visualize_suffix_tree(input_text, output_file='suffix_tree'):  
    """Visualize the suffix tree using Graphviz."""
    tree = parse_suffix_tree(input_text)
    graph = Digraph(format='png')
    graph.node("head_0", "head")
    add_nodes(graph, tree['head']['children'], 'head_0')
    graph.render(output_file, view=True)

# Input structure
tree_input = """
      lNivel = 1 -- $ [9, 9]

      lNivel = 1 -- 81$ [7, 9]

      lNivel = 1 -- 781$ [6, 9]

      lNivel = 1 -- 6781$ [5, 9]

      lNivel = 1 -- 56781$ [4, 9]

      lNivel = 1 -- 1 [0, 0]

           lNivel = 2 -- 23456781$ [1, 9]

           lNivel = 2 -- $ [9, 9]

      lNivel = 1 -- 23456781$ [1, 9]

      lNivel = 1 -- 3456781$ [2, 9]

      lNivel = 1 -- 456781$ [3, 9]
"""

# Generate and visualize the suffix tree
visualize_suffix_tree(tree_input)
