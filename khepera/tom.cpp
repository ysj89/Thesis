//#include <vector>
//#include <unordered_map>

//using namespace std;

//class StateVector {

//private:

//    vector<double> _state;

//public:

//    StateVector(double a, double b, double c, double d);
//    StateVector(int bitMask);

//    int getBitmask() {
//        return _state[0] | _state[1] << 1 | _state[2] << 2 | _state[3] << 4;
//    }


//};


//enum Action {
//    left,
//    right
//};




//unordered_map<int, ActionList> M;

//// iterate over states
//for (int i=0; i<2; ++i) {

//    StateVector s(a,b,c,i);

//    ActionList a(a1, s1, a2, s2, a3, s3, a4, s4);

//    M[s.getBitmask()] = a;


//}

//// Get actions
//ActionList& b = M[s.getBitmask()];

//// Update
//b.at(2).second = 5;

//// Update 2
//M[s.getBitmask()].at(2).second = 5;




//////
///// \brief score
/////




//typedef double score;

//typedef pair<Action, score> actionScorePair;

//typedef vector<actionScorePair> ActionList;

//typedef unordered_map<Action,Score> ActionMap

//unordered_map<std::string, ActionList> Qtable; // C - tom

//// iterate over states
//for (int i=0; i<2; ++i)
//{
//    int index = 20;
//    int aa = 0;
//    int bb = 0;
//    int cc = 1;

//    StateVector s(index, aa, bb, cc);

//    ActionList a(a1, s1, a2, s2, a3, s3, a4, s4);

//    Qtable[s.getBitmask()] = a;
//}

//// unique identifieren for state
//for(int j = 0; j < 3; j++)
//{
//    for(int k = 0; k < 3; k++)
//    {
//        for(int i = 0; i < 60000; i++)
//        {
//            s(i, j, k, s3, s3)
//        }
//    }
//}

//ActionList& b = Qtable[s.begin()]



//// Get actions
//ActionList& b = M[s.getBitmask()];

//// Update
//b.at(2).second = 5;

//// Update 2
//M[s.getBitmask()].at(2).second = 5;

