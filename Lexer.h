#if ! defined ( LEXER_H )
#define LEXER_H

using namespace std;



class Lexer {

    public:
        Lexer(string expression) : inputStream(expression) {}
        virtual ~Lexer();

    protected:
        string inputStream;

};

#endif // LEXER_H