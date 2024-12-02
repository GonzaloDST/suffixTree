#include "suffixTree.h"
// #include <QApplication>
// #include "mainwindow.h"

int main(){
    SuffixTree tree("ABAB$0BABA$1");
    tree.printSuffixTree(tree);
    cout<<endl;
    vector<int> result;
    cout<<"TRUEORFALSE  "<<tree.search("A")<<endl;
    result = tree.searchOccurrences("A");
    for(auto x: result){
        cout<<x<<endl;
    }
    return 0;
}

// int main(int argc, char *argv[]) {
//     QApplication a(argc, argv);
//     MainWindow w;
//     w.show();
//     return a.exec();
// }