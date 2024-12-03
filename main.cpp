#include "suffixTree.h"
// #include <QApplication>
// #include "mainwindow.h"


void test1(){
    SuffixTree tree("banana");
    tree.printSuffixTree(tree);
    cout<<endl;
    vector<int> result;
    string find = "A";
    cout<<"Buscando caracter: " <<find <<endl;
    if(tree.search(find)== true){
        cout<<"El caracter si se encuentra en el texto!"<<endl;
    }
    else{
        cout<<"El caracter no se encuentra en el texto :("<<endl;
    }
    // result = tree.searchOccurrences("a");
    // for(auto x: result){
    //     cout<<x<<endl;
    // }
}

void test2(){
    SuffixTree tree("EricBiagioli");
    tree.printSuffixTree(tree);
    cout<<endl;
    vector<int> result;
    string find = "A";
    cout<<"Buscando caracter: " <<find <<endl;
    if(tree.search(find)== true){
        cout<<"El caracter si se encuentra en el texto!"<<endl;
    }
    else{
        cout<<"El caracter no se encuentra en el texto :("<<endl;
    }
}

void test3(){
    SuffixTree tree("123456781");
    tree.printSuffixTree(tree);
    cout<<endl;
    vector<int> result;
    string find = "A";
    cout<<"Buscando caracter: " <<find <<endl;
    if(tree.search(find)== true){
        cout<<"El caracter si se encuentra en el texto!"<<endl;
    }
    else{
        cout<<"El caracter no se encuentra en el texto :("<<endl;
    }
}

int main(){
    int opcion;

    cout << "Seleccione un test para ejecutar:" << std::endl;
    cout << "1. Test 1" << std::endl;
    cout << "2. Test 2" << std::endl;
    cout << "3. Test 3" << std::endl;
    cout << "Ingrese el número correspondiente: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            test1();
            break;
        case 2:
            test2();
            break;
        case 3:
            test3();
            break;
        default:
            cout << "Opción inválida. Por favor seleccione 1, 2 o 3." << std::endl;
            break;
    }

    return 0;
}

// int main(int argc, char *argv[]) {
//     QApplication a(argc, argv);
//     MainWindow w;
//     w.show();
//     return a.exec();
// }