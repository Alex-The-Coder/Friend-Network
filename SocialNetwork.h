#include <vector>
#include <fstream>
using namespace std;

class SocialNetwork
{
private:
    ifstream infile;
    vector<int>* network_data;
    int** similarity_matrix;
    int size;
public:
    SocialNetwork();
    ~SocialNetwork();
    
    int getSize();

    void readFile();
    void display();
    void init_matrix();
    void calc_similarity_scores();
    int num_in_common_between_vectors(vector<int>& vector1, vector<int>& vector2);
    int recommend(int user_id);
};
