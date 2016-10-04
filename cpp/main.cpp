#include <iostream>
#include <memory>
#include <sstream>
#include <algorithm>

#include "photo.h"
#include "video.h"
#include "film.h"
#include "group.h"
#include "table.h"
#include "TCPServer.h"

using namespace std;

const int DEFAULT_PORT = 3331;

class MyApp {
private:
    Table_p * table_ref;
    vector<string> commands = {"find","play"};
public:
    MyApp(Table_p * _table) {
        table_ref = _table;
    }

    /// Cette fonction est appelée chaque fois qu'il y a une requête à traiter.
    /// - 'request' contient la requête
    /// - 'response' sert à indiquer la réponse qui sera renvoyée au client
    /// - si la fonction renvoie false la connexion est close.
    //
    // Cette fonction peut etre appelée en parallele par plusieurs threads (il y a
    // un thread par client).
    // Si le verrou 'lock' est bloqué en mode WRITE, les autres appels sont bloqués
    // jusqu'à la fin l'appel qui a bloqué le verrou.
    //

    bool processRequest(TCPServer::Cnx& cnx, const string& request, string& response) {
        stringstream ss, ss_response;
        ss << request;
        string command, name;
        ss >> command >> name;

        bool changeData = false;

        try {
            if (find(commands.begin(), commands.end(),command) == commands.end()) {
                response = command+" is not a command.";
                throw runtime_error("(processRequest) "+command+" is not a command.");
            } else if (table_ref->is_in_table(name)) {
                if (command.compare("find") == 0) {
                    TCPServer::Lock lock(cnx, changeData);
                    table_ref->find_obj(name,ss_response);
                    response = ss_response.str();
                    cerr << "request: '" << request << "'" << endl;
                    cerr << "response: '" << response << "'" << endl;

                    return true;
                } else if (command.compare("play") == 0) {
                    TCPServer::Lock lock(cnx, changeData);
                    table_ref->play_obj(name);
                    response = name + " being played.";
                    cerr << "request: '" << request << "'" << endl;
                    cerr << "response: '" << response << "'" << endl;

                    return true;
                }
            } else {
                response = name+" is not in the table.";
                throw runtime_error("(processRequest)"+name+" is not in the table.");
            }
        } catch (exception& e) {
            cerr << "exception caught: " << e.what() << '\n';
            return true;
        }

        return true;
    }
};

int main(int argc, char* argv[]) {
    // Initialisation de la table
    Table_p * table = new Table_p();
    table->load("initial_table.txt");
    //table->load("test.txt");

    Group_ptr group = table->create_group("group");

    table->save("final_table.txt");

    // Lancement du serveur
    TCPServer * server = new TCPServer();
    MyApp * app = new MyApp(table);
    server->setCallback(app, &MyApp::processRequest);

    int port = (argc >= 2) ? atoi(argv[1]) : DEFAULT_PORT;
    cout << "Starting Server on port " << port << endl;
    int status = server->run(port);

    if (status < 0) {
        cerr << "Could not start Server on port " << port << endl;
        return 1;
    } else {
        return 0;
    }
}
