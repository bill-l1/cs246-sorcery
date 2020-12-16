#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <string>

class GameException {
	std::string err; // error message
    bool doExit;
	public:
		GameException(const std::string &err, const bool &doExit=false);
		std::string getErr() const;
        bool getDoExit() const;
};

class InvalidTarget : public GameException {
    public: InvalidTarget();
};

class InvalidPlayer : public GameException {
    public: InvalidPlayer();
};

class InvalidSelection : public GameException {
    public: InvalidSelection();
};

class InvalidPlay : public GameException {
    public: InvalidPlay();
};

class InvalidCommand : public GameException {
    public: InvalidCommand();
};

class InvalidCard : public GameException {
    public: InvalidCard(const std::string &name);
};

class GameOver : public GameException {
    int winner;
    public:
        GameOver(const int &winner=-1);
        int getWinner() const;
};

class InsufficientMagic : public GameException {
    public: InsufficientMagic();
};

class InsufficientActions : public GameException {
    public: InsufficientActions();
};

class HandIsFull : public GameException {
    public: HandIsFull();
};

class BoardIsFull : public GameException {
    public: BoardIsFull();
};

class DeckError : public GameException {
    public: DeckError();
};

class IllegalAction : public GameException {
    public: IllegalAction(const std::string &act);
};

#endif