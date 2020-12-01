
#include <string>
#include <memory>
#include <stack>
#include "player.h"
#include "card.h"


Card(const std::string &name) {


}
std::string getName() const {
return name;

}
std::string getType() const {
return type;
}
std::string getDescription() const {
return description;
}
int getCost() const {
return cost;
}
Player getOwner() const {
return owner;
}
