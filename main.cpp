#include "suffixTree.h"
// #include <QApplication>
// #include "mainwindow.h"

int main(){
    SuffixTree tree("126366");
    tree.printSuffixTree(tree);
    cout<<endl;
    vector<int> result;
    cout<<"TRUEORFALSE"<<tree.search("a")<<endl;
    result = tree.searchOccurrences("6");
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