#include <fstream>
#include "suffixTree.cpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void exportTree(Node* node, json& output, const string& text) {
    if (!node) return;
    if (node->start != -1) {
        json child;
        child["label"] = text.substr(node->start, node->end - node->start + 1);
        child["start"] = node->start;
        child["end"] = node->end;
        output["children"].push_back(child);
    }
    for (auto& child : node->children) {
        exportTree(child.second, output["children"].back(), text);
    }
}

void exportSuffixTree(const SuffixTree& tree, const string& filename) {
    json output;
    exportTree(tree.root, output, tree.text);
    std::ofstream file(filename);
    file << output.dump(4); // Export JSON with indentation
}
