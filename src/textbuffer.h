#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include <string>
#include <vector>

// at some point, change 'char' to a special datatype
// will need to this to change when we do stuff like highlighting
// this also makes 'mod' more meaningful
class TextBuffer {
public:
    void put(char c, int x, int y);
    std::vector<char> getLineAt(int x);
    void remove(char c, int x, int y);
    void mod(char c, int x, int y);
private:
    std::vector< std::vector<char> > data;
};

#endif /* TEXT_BUFFER_H */
