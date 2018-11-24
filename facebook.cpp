#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include "SocialNetwork.h"
using namespace std;

int main()
{
    SocialNetwork n;
    n.readFile();
    n.calc_similarity_scores();

    bool cont = true;
    while (cont)
    {
        int requested;
        cout << "Enter an integer in the range 0 to " << n.getSize() - 1 << ": ";
        cin >> requested;
        while (cin.fail() || (requested < 0 || requested >= n.getSize()))
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Error: input must be an int between 0 and " << n.getSize() - 1 << endl;
            cout << "Enter an integer in the range 0 to " << n.getSize() << ": ";
            cin >> requested;
        }

        cout << "The suggested friend for " << requested << " is " << n.recommend(requested) << endl << endl;

        cout << "Do you want to continue (yes/no)? ";
        string response;
        cin.ignore();
        getline(cin, response);
        for (int i = 0; i < response.length(); i++)
        {
            response.at(i) = tolower(response.at(i));
        }
        if (response == "no")
        {
            cont = false;
        }
    }

    return 0;
}
