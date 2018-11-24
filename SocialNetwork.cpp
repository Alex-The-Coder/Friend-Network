#include <iostream>
#include <string>
#include "SocialNetwork.h"
using namespace std;

SocialNetwork::SocialNetwork()
{
    string fileName;
    do
    {
        cout << "Enter a file name: ";
        getline(cin, fileName);
        infile.open(fileName);
        if (!infile.good())
        {
            cout << "An error occurred while attempting to load that file!" << endl;
        }
        else
        {
            infile >> size;
            network_data = new vector<int>[size];
            init_matrix();
        }
    }
    while (!infile.good());
}

SocialNetwork::~SocialNetwork()
{
    infile.close();
    delete[] network_data;
    for (int i = 0; i < size; i++)
    {
        delete[] similarity_matrix[i];
    }
    delete[] similarity_matrix;
}

int SocialNetwork::getSize()
{
    return size;
}

void SocialNetwork::readFile()
{
    while (infile.good())
    {
        int u;
        int v;
        infile >> u;
        infile >> v;

        network_data[u].push_back(v);
        network_data[v].push_back(u);
    }
}

void SocialNetwork::display()
{
    for (int id = 0; id < size; id++)
    {
        cout << id << " : [";
        for (int j = 0; j < network_data[id].size(); j++)
        {
            cout << network_data[id].at(j);
            if (j != network_data[id].size() - 1)
            {
                cout << ", ";
            }
        }
        cout << ']' << endl;
    }
    cout << endl;
    for (int id = 0; id < size; id++)
    {
        cout << id << " : [";
        for (int j = 0; j < size; j++)
        {
            cout << similarity_matrix[id][j];
            if (j != size - 1)
            {
                cout << ", ";
            }
        }
        cout << ']' << endl;
    }
}

void SocialNetwork::init_matrix()
{
    similarity_matrix = new int*[size];
    for (int i = 0; i < size; i++)
    {
        similarity_matrix[i] = new int[size];
        for (int j = 0; j < size; j++)
        {
            similarity_matrix[i][j] = 0;
        }
    }
}

void SocialNetwork::calc_similarity_scores()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            vector<int> iv = network_data[i];
            vector<int> jv = network_data[j];
            int similarity = num_in_common_between_vectors(iv, jv);
            similarity_matrix[i][j] = similarity;
            similarity_matrix[j][i] = similarity;
        }
    }
}

int SocialNetwork::num_in_common_between_vectors(vector<int>& vector1, vector<int>& vector2)
{
    int common = 0;
    for (int i = 0; i < vector1.size(); i++)
    {
        for (int j = 0; j < vector2.size(); j++)
        {
            if (vector1.at(i) == vector2.at(j))
            {
                common++;
            }
        }
    }

    return common;
}

bool found(vector<int>& vector, int lookup)
{
    for (int i = 0; i < vector.size(); i++)
    {
        if (vector.at(i) == lookup)
        {
            return true;
        }
    }

    return false;
}

int SocialNetwork::recommend(int user_id)
{
    int max = -1;
    vector<int> userFriends = network_data[user_id];
    for (int i = 0; i < size; i++)
    {
        if (i == user_id)
        {
            continue;
        }
        if (found(userFriends, i))
        {
            continue;
        }
        int common = similarity_matrix[user_id][i];
        if (max == -1 || common > similarity_matrix[user_id][max])
        {
            max = i;
        }
    }

    return max;
}
