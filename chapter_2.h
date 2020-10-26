const int NODE_COUNT = 10;

extern bool adjacentNodes[NODE_COUNT][NODE_COUNT];
extern bool visitedNodes[NODE_COUNT];

void initializeMatrices();
void makeEdge(int startNode, int endNode);
void initializeStack();
void push(int element);
int pop();
bool isEmpty();
void depthFirstSearch(int start, int goal);
int test_2_2();
int test_2_3();
