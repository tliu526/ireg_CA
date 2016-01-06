/*
Implementation of the Rule Table class.

(c) 2016 Tony Liu.
*/

#include "RuleTable.h"

using namespace std;

RuleTable::RuleTable(Stencil& s){
    stencil = s;
}

void RuleTable::transition(Graph<std::string,Cell>* graph) {

}

void RuleTable::apply_rule(std::string label, Graph<std::string,Cell>* graph) {

}

void RuleTable::initialize() {

}