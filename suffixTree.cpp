#include "suffixTree.h"


SuffixTree::~SuffixTree(){
    deleteTrees(root);
}
void SuffixTree::deleteTrees(Node* node){
    if(!node){return;}
    for(auto &child: node->children){
        deleteTrees(child.second);
    }
    delete node;
}
void SuffixTree::build(int index) {

    suffix_restantes++;
    Node* aux = nullptr;
    
    while (suffix_restantes > 0) {
        
        if (size_pivot == 0)
            pivot = index;
        
        char currentChar = text[pivot];

        if(nodoActual->children.find(currentChar) != nodoActual->children.end())
        // Encontró un hijo con el mismo caracter, recorre ese subárbol 
        { 
            Node* siguienteHijo = nodoActual->children[currentChar];
            int size_siguienteHijo =  siguienteHijo->size();

            // Siguientes 2 condicionales propios del algoritmo que optimizan
            // significativamente la construcción, evita redundancia
            if (size_pivot >= size_siguienteHijo)
            // Si el pivot es del mismo tamaño o mayor que el hijo
            { 
                // puede que exista más caracteres que coincidan, se avanza
                pivot += size_siguienteHijo;
                size_pivot -= size_siguienteHijo;
                nodoActual = siguienteHijo;
                continue;
            }
            if (size_pivot < size_siguienteHijo && text[siguienteHijo->start + size_pivot] == text[index])
            { 
                size_pivot++;
                if (aux && nodoActual != root) {
                    aux->parent = nodoActual;
                }
                break;
            }

            // Se crea un nodo de separación, este tiene la mayor cantidad de caracteres coincidentes
            Node* nodoComun = new Node(siguienteHijo->start, siguienteHijo->start + size_pivot - 1);
            nodoActual->children[currentChar] = nodoComun;  //Nodo actual ahora tiene que tener a este nodoComún como hijo
                                                            //Se sobreescribe sobre el nodo antiguo
            nodoComun->children[text[index]] = new Node(index, text.size() - 1); 
            siguienteHijo->start += size_pivot; // Se desplaza el start del hijo para actualizar el nuevo rango
            nodoComun->children[text[siguienteHijo->start]] = siguienteHijo; //El nuevo nodo debe tener como hijo el nodo hijo antiguo actualizado

            if (aux) {
                aux->parent = nodoComun;
            }
            aux = nodoComun;
        }
        else //No existe el hijo, hay que crearlo
        { 
            nodoActual->children[currentChar] = new Node(index, text.size() - 1);
            if (aux) {
                aux->parent = nodoActual;
                aux = nullptr;
            }
        }
        
        suffix_restantes--; //Solo se disminuye cuando todo el arbol se encuentra actualizado, es decir se acabo de insertar este sufijo
        if (nodoActual == root && size_pivot > 0) {
            size_pivot--;
            pivot = index - suffix_restantes + 1;
        } else if (nodoActual != root) {
            nodoActual = nodoActual->parent;
        }
    }
}


SuffixTree::SuffixTree(const string& input) : text(input + "$"), position(-1) {
    root = new Node(-1, -1);
    root->parent = root;
    nodoActual = root;

    suffix_restantes = 0;

    pivot = -1;
    size_pivot = 0;

    //Un build por cada sufijo
    for (int i = 0; i < text.size(); ++i) {
        build(i);
    }
}

bool SuffixTree::search(const string& pattern) {
    Node* current = root;
    int i = 0;

    while (i < pattern.size()) {
        if (current->children.find(pattern[i]) == current->children.end()) {
            return false; //No encontró un hijo con ese caracter
        }

        Node* siguienteHijo = current->children[pattern[i]];
        int size_siguienteHijo = siguienteHijo->size();
        int j = 0;

        while (j < size_siguienteHijo && i < pattern.size()  && pattern[i] == text[siguienteHijo->start + j]) 
        // Se avanza todas las coincidencias, sin pasarse el tamaño del pattern o del nodoHijo
        { 
            i++;
            j++;
        }

        if (j != size_siguienteHijo && i != pattern.size() )
        // No se encontró coincidencias
        {  
            return false;
        }

        current = siguienteHijo;
    }

    return true;
}


void SuffixTree::searchOccurrences(const string& pattern, vector<int>& result, Node* nodoInicial, int nodoPivot) {
    if (!nodoInicial) return;

    int i = nodoPivot;
    Node* current = nodoInicial;
    
    while (i < pattern.size()) {
        cout << "Visitando nodo: " << current << " con caracter: " << pattern[i] << endl;
        if (current->children.find(pattern[i]) == current->children.end()) {
            cout << "No se encontró un hijo con el caracter: " << pattern[i] << endl;
            return; // No se encontró un hijo con ese caracter
        }

        Node* child = current->children[pattern[i]];
        int j = 0;
        while (j < child->size() && i < pattern.size() && pattern[i] == text[child->start + j]) {
            cout << "Coincidencia encontrada: " << pattern[i] << " en posición " << i << " en nodo " << child << endl;
            result.push_back(i);
            i++;
            j++;
        }

        if (i == pattern.size()) {
            cout << "Patrón completo encontrado, llamando a retornarHojas para el nodo: " << child << endl;
            retornarHojas(child, result);
            return;
        } else if (j == child->size()) {
            cout << "Avanzando al siguiente nodo: " << child << endl;
            current = child;
            nodoPivot += j;
        } else {
            cout << "No se encontró coincidencias en nodo: " << child << endl;
            return; // No se encontró coincidencias
        }
    }

    retornarHojas(current, result);
}



void SuffixTree::retornarHojas(Node* node, vector<int>& result) {
    if (!node) return;

    if (node->isLeaf()) {
        // Ajustamos la posición para reflejar la posición original en el texto
        int adjusted_position = node->start - (text.size() - node->end);
        result.push_back(adjusted_position);
        cout << "Hoja encontrada en posición ajustada: " << adjusted_position << " para nodo: " << node << endl;
        return;
    }

    for (auto& child : node->children) {
        cout << "Recorriendo hijo: " << child.second << " del nodo: " << node << endl;
        retornarHojas(child.second, result); // Buscar en todos los nodos hijos
    }
}



vector<int> SuffixTree::searchOccurrences(const string& pattern) {
    vector<int> result;
    searchOccurrences(pattern, result, root, 0);
    return result;
}



void SuffixTree::printTree(Node* node, const string& text,int level) {
    if (!node) return;

    if (node->start != -1) { 
        for (int i = 0; i < level; ++i) cout << "     ";
        cout << " l" <<"Nivel = "<<level<<" -- " << text.substr(node->start, node->end - node->start + 1)
            << " [" << node->start << ", " << node->end << "]" << endl;
    }

    
    for (auto& child : node->children) {
        cout<<endl;
        printTree(child.second, text, level + 1);
    }
}


void SuffixTree::printSuffixTree(const SuffixTree& tree) {
    cout << "Suffix Tree:" << endl;
    printTree(tree.root, tree.text);
    }
