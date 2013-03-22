#include <string>

// at some point, change 'char' to a special datatype
// will need to this to change when we do stuff like highlighting
// this also makes 'mod' more meaningful
class buffer{
private:
    std::vector< std::vector<char> > bufferData;
public:
    void put(char c, int x, int y);
    std::string getLineAt(int x);
    void remove(char c, int x, int y);
    void mod(char c, int x, int y);
};