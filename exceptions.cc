#include "exceptions.h"

GameException::GameException(const std::string &err, const bool &doExit)
    : err{err},
    doExit{doExit}
{}

std::string GameException::getErr() const{
    return err;
}

bool GameException::getDoExit() const {
    return doExit;
}

InvalidTarget::InvalidTarget()
    : GameException{"Invalid target."}
{}

InvalidPlayer::InvalidPlayer()
    : GameException{"Invalid player selected."}
{}

InvalidSelection::InvalidSelection()
    : GameException{"Invalid selection."}
{}

InvalidPlay::InvalidPlay()
    : GameException{"Invalid way to play card."}
{}

InvalidCommand::InvalidCommand()
    : GameException{"Invalid command. (type \"help\" for commands and usage)"}
{}

InvalidCard::InvalidCard(const std::string &name)
    : GameException{"Card " + name + " not found."}
{}

GameOver::GameOver(const int &winner)
    : GameException{"Game over!", true},
    winner{winner}
{}

int GameOver::getWinner() const{
    return winner;
}

InsufficientMagic::InsufficientMagic()
    : GameException{"Not enough magic."}
{}

InsufficientActions::InsufficientActions()
    : GameException{"Minion cannot act yet."}
{}

HandIsFull::HandIsFull()
    : GameException{"Hand is too full!"}
{}

BoardIsFull::BoardIsFull()
    : GameException{"Board is too full!"}
{}

DeckError::DeckError()
    : GameException{"Problem loading deck.", true}
{}

IllegalAction::IllegalAction(const std::string &act)
    : GameException{"Illegal action: "+act, true}
{}