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
            if (text[siguienteHijo->start + size_pivot] == text[index])
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
            cout<<"pos"<<i<<endl;
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

    
    for (auto& child : nodoInicial->children) {
        Node* nodoHijo = child.second;
        int size_siguienteHijo = nodoHijo->size();
        int i = 0;

        while (i < size_siguienteHijo && nodoPivot + i < pattern.size() && text[nodoHijo->start + i] == pattern[nodoPivot + i]) {
            i++;
        }

        if (nodoPivot + i == pattern.size()) {
            retornarHojas(nodoHijo, result);
            return;
        }
        else if (i == size_siguienteHijo) {
            searchOccurrences(pattern, result, nodoHijo, nodoPivot + i);
        }
    }
}


void SuffixTree::retornarHojas(Node* node, vector<int>& result) {
    if (!node) return;

    if (node->isLeaf()) {
        result.push_back( (node->start));
        return;
    }

    for (auto& child : node->children) {
        retornarHojas(child.second, result); //Todos los que empiezan con el pattern
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
        cout << " l -- " << text.substr(node->start, node->end - node->start + 1)
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
